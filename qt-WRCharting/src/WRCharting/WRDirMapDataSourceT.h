#pragma once
#ifndef WRDIRMAPDATASOURCET
#define WRDIRMAPDATASOURCET

#include <WRCharting/WRDirMapDataSource.h>
#include <WRCharting/WRDirMapInitParams.h>

//表示向频图数据源模板。
template <class Ts, class Ta> class WRDirMapDataSourceT : public WRDirMapDataSource
{
private:
	Ts* m_specBuffer1;	//频谱缓存1
	Ts* m_specBuffer2;	//频谱缓存2
	Ta* m_angleBuffer1;	//角度缓存1
	Ta* m_angleBuffer2;	//角度缓存2
    int m_dataCount1;	//数据缓存1数量
    int m_dataStart1;	//数据缓存1起始
    int m_dataCount2;	//数据缓存2数量
    int m_dataStart2;	//数据缓存2起始

    //表示循环缓存。
    class LoopBuffer
    {
    private:
        Ts* m_specArray;		//频谱数组
        Ta* m_angleArray;		//角度数组
        int& m_dataCount;		//数据数量
        int& m_dataStart;		//数据起始
        int m_dataTotal;		//缓存总量
        int m_dataFrame;		//数据帧长

    public:
        //初始化向频图循环缓存。
        LoopBuffer(Ts* specArray, Ta* angleArray, int &dataCount, int &dataStart, int dataFrame, int dataTotal)
            : m_dataCount(dataCount), m_dataStart(dataStart)
        {
            m_specArray = specArray;
            m_angleArray = angleArray;
            m_dataFrame = dataFrame;
            m_dataTotal = dataTotal;
        }

        //获取当前数据和角度。
        void fetch(Ts** pSpec1, Ta** pDir1, int* nCnt1, Ts** pSpec2, Ta** pDir2, int* nCnt2)
        {
            int off = m_dataStart * m_dataFrame;
            *pSpec1 = m_specArray + off;
            *pDir1 = m_angleArray + off;
            int count = m_dataTotal - m_dataStart;
            if (count < m_dataCount)
            {
                *nCnt1 = count;
                *pSpec2 = m_specArray;
                *pDir2 = m_angleArray;
                *nCnt2 = m_dataCount - count;
            }
            else
            {
                *nCnt1 = m_dataCount;
                *pSpec2 = 0;
                *pDir2 = 0;
                *nCnt2 = 0;
            }
        }

        //写入指定的数据。
        void write(const Ts* specBuffer, const Ta *angleBuffer, int dataCount)
        {
            if (dataCount >= m_dataTotal)
            {
                //写入数据超过数据总量，则直接从0开始复制并设置数据量为数据总量
                int cnt = m_dataTotal * m_dataFrame;
                int off = (dataCount - m_dataTotal) * m_dataFrame;
                memcpy(m_specArray, specBuffer + off, cnt * sizeof(Ts));
                memcpy(m_angleArray, angleBuffer + off, cnt * sizeof(Ta));
                m_dataStart = 0;
                m_dataCount = m_dataTotal;
            }
            else
            {
                //计算写入位置
                int write = m_dataStart + m_dataCount;
                if (write >= m_dataTotal) write -= m_dataTotal;
                //计算尾部可写入的数据量
                int count = m_dataTotal - write;
                if (count < dataCount)
                {
                    //尾部可写入数据量小于要写入的数据量，则分两段进行写入
                    int cnt = count * m_dataFrame;
                    int off = write * m_dataFrame;
                    memcpy(m_specArray + off, specBuffer, cnt * sizeof(Ts));
                    memcpy(m_angleArray + off, angleBuffer, cnt * sizeof(Ta));

                    cnt = (dataCount - count) * m_dataFrame;
                    off = count * m_dataFrame;
                    memcpy(m_specArray, specBuffer + off, cnt * sizeof(Ts));
                    memcpy(m_angleArray, angleBuffer + off, cnt * sizeof(Ta));
                }
                else
                {
                    //尾部空间足够，则直接写入
                    int cnt = dataCount * m_dataFrame;
                    int off = write * m_dataFrame;
                    memcpy(m_specArray + off, specBuffer, cnt * sizeof(Ts));
                    memcpy(m_angleArray + off, angleBuffer, cnt * sizeof(Ta));
                }
                //计算数据长度
                count = m_dataCount + dataCount;
                if (count > m_dataTotal)
                {
                    //数据长度大小数据总量，则表示头部被覆盖，需移动头部为覆盖的数据量
                    m_dataStart += count - m_dataTotal;
                    if (m_dataStart >= m_dataTotal) m_dataStart -= m_dataTotal;
                    //设置设置数据量为数据总量
                    m_dataCount = m_dataTotal;
                }
                else
                {
                    //数据长度小于等于数据总量，则直接设置长度，不移动数据首位置
                    m_dataCount = count;
                }
            }
        }

        //将目标缓存数据复制到当前缓存中，并清空目标缓存。
        int merge(LoopBuffer& other)
        {
            //源缓存中的数据量大于当前缓存中新的数据总量，则源缓存中只保留新的数据总量
            if (other.m_dataCount > m_dataTotal)
            {
                other.m_dataStart += other.m_dataCount - m_dataTotal;
                if (other.m_dataStart >= other.m_dataTotal) other.m_dataStart -= other.m_dataTotal;
                other.m_dataCount = m_dataTotal;
            }
            //计算当前缓存中允许保留的数据量
            int saveCount = m_dataTotal - other.m_dataCount;
            //如果允许保留的数据量小于当前缓存数据量，则减小当前缓存数据量
            if (saveCount < m_dataCount)
            {
                m_dataStart += m_dataCount - saveCount;
                if (m_dataStart >= m_dataTotal) m_dataStart -= m_dataTotal;
                m_dataCount = saveCount;
            }
            //取出源缓存数据信息
            Ts *pSpec1, *pSpec2;
            Ta *pDir1, *pDir2;
            int nCnt1, nCnt2;
            other.fetch(&pSpec1, &pDir1, &nCnt1, &pSpec2, &pDir2, &nCnt2);
            //将源缓存数据写入当前缓存中
            this->write(pSpec1, pDir1, nCnt1);
            if (nCnt2 > 0)
            {
                this->write(pSpec2, pDir2, nCnt2);
            }
            //清除源缓存数据
            other.m_dataStart = 0;
            other.m_dataCount = 0;

            return nCnt1 + nCnt2;
        }
        //重置当前缓存并将目标缓存数据复制到当前缓存中，清空目标缓存。
        int reset(LoopBuffer& other)
        {
            //源缓存中的数据量大于当前缓存中新的数据总量，则源缓存中只保留新的数据总量
            if (other.m_dataCount > m_dataTotal)
            {
                other.m_dataStart += other.m_dataCount - m_dataTotal;
                if (other.m_dataStart >= other.m_dataTotal) other.m_dataStart -= other.m_dataTotal;
                other.m_dataCount = m_dataTotal;
            }
            //取出源缓存数据信息
            Ts *pSpec1, *pSpec2;
            Ta *pDir1, *pDir2;
            int nCnt1, nCnt2;
            other.fetch(&pSpec1, &pDir1, &nCnt1, &pSpec2, &pDir2, &nCnt2);
            int nSize1 = nCnt1 * m_dataFrame;
            int nSize2 = nCnt2 * m_dataFrame;
            memcpy(m_specArray, pSpec1, sizeof(Ts) * nSize1);
            memcpy(m_angleArray, pDir1, sizeof(Ta) * nSize1);
            memcpy(m_specArray + nSize1, pSpec2, sizeof(Ts) * nSize2);
            memcpy(m_angleArray + nSize1, pDir2, sizeof(Ta) * nSize2);
            m_dataStart = 0;
            m_dataCount = other.m_dataCount;
            //清除源缓存数据
            other.m_dataStart = 0;
            other.m_dataCount = 0;
            //
            return m_dataCount;
        }
    };

protected:
	//清理当前对象所占用的相关资源。
	~WRDirMapDataSourceT()
	{
		delete[] m_specBuffer1; 
		delete[] m_specBuffer2;
		delete[] m_angleBuffer1; 
		delete[] m_angleBuffer2;
	}

public:
	//初始化向频图实时数据源。
	explicit WRDirMapDataSourceT(const WRDirMapInitParams<Ts, Ta>& initArgs)
	{
		m_specMinValue = initArgs.specMinValue();
		m_specMaxValue = initArgs.specMaxValue();
		m_specOffValue = initArgs.specOffValue();
		m_specDifValue = m_specMaxValue - m_specMinValue;
		m_angleMeasure = initArgs.angleMeasure();
		m_angleMinValue = initArgs.angleMinValue() * initArgs.angleMeasure();
		m_angleMaxValue = initArgs.angleMaxValue() * initArgs.angleMeasure();
		m_points = initArgs.points();
		m_isClosed = initArgs.isClosed();
		m_freqBegin = initArgs.freqBegin();
		m_freqEnd = initArgs.freqEnd();
		m_buffers = initArgs.buffers();
		m_capacity = initArgs.capacity();

		int len1 = m_points * m_buffers;
		int len2 = m_points * m_capacity;

		m_specBuffer1 = new Ts[len1];
		m_specBuffer2 = new Ts[len2];		
		m_angleBuffer1 = new Ta[len1];
		m_angleBuffer2 = new Ta[len2];
		m_dataStart1 = 0;
		m_dataCount1 = 0;
		m_dataStart2 = 0;
		m_dataCount2 = 0;
	}
	
    //清除所有数据。
    void clear(void)
    {
        m_dataCount1 = 0;
        m_dataStart1 = 0;
        m_isClear = true;
        m_changed = true;
    }
	//添加指定的数据, 该数据将写入缓存中。
	void append(const void* specBuffer, const void* angleBuffer, int dataFrames)
	{
        LoopBuffer loopBuffer(m_specBuffer1, m_angleBuffer1, m_dataCount1, m_dataStart1, m_points, m_buffers);
		loopBuffer.write((Ts*)specBuffer, (Ta*)angleBuffer, dataFrames);
        m_changed = true;
	}

	//检查如果，如果数据改变，则将改变的数据生效。返回数据总帧数。
	long validate(void)
	{
        if (m_changed)
		{
            LoopBuffer srcBuf(m_specBuffer1, m_angleBuffer1, m_dataCount1, m_dataStart1, m_points, m_buffers);
            LoopBuffer dstBuf(m_specBuffer2, m_angleBuffer2, m_dataCount2, m_dataStart2, m_points, m_capacity);
            if (m_isClear)
            {
                dstBuf.reset(srcBuf);
                m_isClear = false;
            }
            else
            {
                dstBuf.merge(srcBuf);
            }
            m_changed = false;
			++m_version;
		}
		return m_version;
	}

	//取出从指定起始位置开始的指定数量的数据。
	void retrieve(double* pBuf, ProcMethod tWay, const WRChartSampleRange& pointRange, const WRChartDValueRange& angleRange, int height)
	{
		if (tWay == Average)
		{
			if (m_dataCount2 == 0)
			{
				for(int i = 0, l = pointRange.count() * height; i < l; ++i)
				{
					pBuf[i] = m_specMinValue;
				}
			}
			else
			{
				double specValue = m_specMinValue * m_dataCount2;
				for(int i = 0, l = pointRange.count() * height; i < l; ++i)
				{
					pBuf[i] = specValue;
				}
				int height1 = height - 1;
				int dataTotal = m_points * m_capacity;
				double angleSpan = angleRange.span();
                for(int column = 0; column < pointRange.count(); ++column)
				{
					int dataIndex = m_dataStart2 * m_points + pointRange.begin() + column;
					for(int row = 0; row < m_dataCount2; ++row)
					{
						double angle = m_angleBuffer2[dataIndex] * m_angleMeasure;
						if (angle >= angleRange.begin() && angle <= angleRange.end())
						{
							int y = height1 - (int)((angle - angleRange.begin()) * height1 / angleSpan + 0.5);
							int i = y * pointRange.count() + column;
							double* pBuf2 = pBuf + i;
							*pBuf2 += m_specBuffer2[dataIndex] - m_specMinValue;
						}

						dataIndex += m_points;
						if (dataIndex >= dataTotal)
						{
							dataIndex = pointRange.begin() + column;
						}
					}
                }
				double *pBuf2 = pBuf;
				for(int i = 0, l = pointRange.count() * height; i < l; ++i, ++pBuf2)
				{
					*pBuf2 /= m_dataCount2;
				}
			}
		}
		else
		{
			for(int i = 0, l = pointRange.count() * height; i < l; ++i)
			{
				pBuf[i] = m_specMinValue;
			}
			int height1 = height - 1;
			int dataTotal = m_points * m_capacity;
			double angleSpan = angleRange.span();
            for(int column = 0; column < pointRange.count(); ++column)
			{
				int dataIndex = m_dataStart2 * m_points + pointRange.begin() + column;
				for(int row = 0; row < m_dataCount2; ++row)
				{
					double angle = m_angleBuffer2[dataIndex] * m_angleMeasure;
					if (angle >= angleRange.begin() && angle <= angleRange.end())
					{
						int y = height1 - (int)((angle - angleRange.begin()) * height1 / angleSpan + 0.5);
						int i = y * pointRange.count() + column;
						double* pBuf2 = pBuf + i;
						double spec = m_specBuffer2[dataIndex];
						if (spec > *pBuf2)
						{
							*pBuf2 = spec;
						}
					}

					dataIndex += m_points;
					if (dataIndex >= dataTotal)
					{
						dataIndex = pointRange.begin() + column;
					}
				}
            }
		}
	}
	//取出从指定起始位置开始的指定数量的数据。
	void retrieve(double* pBuf, ProcMethod tWay, const WRChartSampleRange& pointRange, const WRChartDValueRange& angleRange, int* pointIndex, int pointCount,  int height)
	{
		if (tWay == Average)
		{
			if (m_dataCount2 == 0)
			{
				for(int i = 0, l = pointRange.count() * height; i < l; ++i)
				{
					pBuf[i] = m_specMinValue;
				}
			}
			else
			{
				double specValue = m_specMinValue * m_dataCount2;
				for(int i = 0, l = pointCount * height; i < l; ++i)
				{
					pBuf[i] = specValue;
				}
				int height1 = height - 1;
				int dataTotal = m_points * m_capacity;
				double angleSpan = angleRange.span();
                for(int column = 0; column < pointCount; ++column)
				{
					int pointBegin = (column == 0 ? pointRange.begin() : pointIndex[column - 1]);
					int pointEnd = pointIndex[column];
					int dataStart = m_dataStart2 * m_points + pointRange.begin() + pointBegin;
					for(int row = 0; row < m_dataCount2; ++row)
					{
						int dataIndex = dataStart;
						for(int p = pointBegin; p < pointEnd; ++p, ++dataIndex)
						{
							double angle = m_angleBuffer2[dataIndex] * m_angleMeasure;
							if (angle >= angleRange.begin() && angle <= angleRange.end())
							{
								int y = height1 - (int)((angle - angleRange.begin()) * height1 / angleSpan + 0.5);
								int i = y * pointCount + column;
								double* pBuf2 = pBuf + i;
								*pBuf2 += m_specBuffer2[dataIndex] - m_specMinValue;
							}
						}

						dataStart += m_points;
						if (dataStart >= dataTotal)
						{
							dataStart = pointRange.begin() + pointBegin;
						}
					}
                }
				double *pBuf2 = pBuf;
				for(int i = 0, l = pointCount * height; i < l; ++i, ++pBuf2)
				{
					*pBuf2 /= m_dataCount2;
				}
			}
		}
		else
		{
			for(int i = 0, l = pointCount * height; i < l; ++i)
			{
				pBuf[i] = m_specMinValue;
			}
			int height1 = height - 1;
			int dataTotal = m_points * m_capacity;
			double angleSpan = angleRange.span();
            for(int column = 0; column < pointCount; ++column)
			{
				int pointBegin = (column == 0 ? pointRange.begin() : pointIndex[column - 1]);
				int pointEnd = pointIndex[column];
				int dataStart = m_dataStart2 * m_points + pointRange.begin() + pointBegin;
				for(int row = 0; row < m_dataCount2; ++row)
				{
					int dataIndex = dataStart;
					for(int p = pointBegin; p < pointEnd; ++p, ++dataIndex)
					{
						double angle = m_angleBuffer2[dataIndex] * m_angleMeasure;
						if (angle >= angleRange.begin() && angle <= angleRange.end())
						{
							int y = height1 - (int)((angle - angleRange.begin()) * height1 / angleSpan + 0.5);
							int i = y * pointCount + column;
							double* pBuf2 = pBuf + i;
							double spec = m_specBuffer2[dataIndex];
							if (spec > *pBuf2)
							{
								*pBuf2 = spec;
							}
						}
					}

					dataStart += m_points;
					if (dataStart >= dataTotal)
					{
						dataStart = pointRange.begin() + pointBegin;
					}
				}
            }
		}
	}
};

#endif //WRDIRMAPDATASOURCE
