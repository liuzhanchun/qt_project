#pragma once
#ifndef WRWATERFALLDATASOURCET
#define WRWATERFALLDATASOURCET

#include <WRCharting/WRWaterfallDataSource.h>
#include <WRCharting/WRWaterfallInitParams.h>

//表示瀑布图数据源模板。
template <class T> class WRWaterfallDataSourceT : public WRWaterfallDataSource
{
private:
	T* m_specBuffer1;	//频谱缓存1
	T* m_specBuffer2;	//频谱缓存2
	long long* m_timeBuffer1;	//时间缓存1
	long long* m_timeBuffer2;	//时间缓存2
	int m_dataCount1;		//数据缓存1数量
	int m_dataStart1;		//数据缓存1起始
	int m_dataCount2;		//数据缓存2数量
    int m_dataStart2;		//数据缓存2起始

	//表示循环缓存。
	class LoopBuffer
	{
	private:	
		T* m_specArray;			//频谱数组
		long long* m_timeArray;	//时间数组
		int& m_dataCount;		//数据数量
		int& m_dataStart;		//数据起始
		const int m_dataTotal;	//缓存总量
		const int m_specFrame;	//频谱帧长

	public:
		//初始化瀑布图循环缓存。
		LoopBuffer(T* specArray, long long* timeArray, int &dataCount, int &dataStart, int specFrame, int dataTotal)
			: m_dataCount(dataCount), m_dataStart(dataStart), m_dataTotal(dataTotal), m_specFrame(specFrame)
		{
			m_specArray = specArray;
			m_timeArray = timeArray;
		}

		//获取当前数据和时间。
		void fetch(T** pSpec1, long long** pTime1, int* nCnt1, T** pSpec2, long long** pTime2, int* nCnt2)
		{
			*pSpec1 = m_specArray + m_dataStart * m_specFrame;
			*pTime1 = m_timeArray + m_dataStart;
			int count = m_dataTotal - m_dataStart;
			if (count < m_dataCount)
			{
				*nCnt1 = count;
				*pSpec2 = m_specArray;
				*pTime2 = m_timeArray;
				*nCnt2 = m_dataCount - count;
			}
			else
			{
				*nCnt1 = m_dataCount;
				*pSpec2 = 0;
				*pTime2 = 0;
				*nCnt2 = 0;
			}
		}

        //写入指定的数据。
		void write(const T* specBuffer, const long long *timeBuffer, int dataCount)
		{
			if (dataCount >= m_dataTotal)
			{
				//写入数据超过数据总量，则直接从0开始复制并设置数据量为数据总量
				memcpy(m_specArray, specBuffer + (dataCount - m_dataTotal) * m_specFrame, m_dataTotal * m_specFrame * sizeof(T));
				memcpy(m_timeArray, timeBuffer + dataCount - m_dataTotal, sizeof(long long) * m_dataTotal);
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
					memcpy(m_specArray + write * m_specFrame, specBuffer, count * m_specFrame * sizeof(T));
					memcpy(m_timeArray + write, timeBuffer, sizeof(long long) * count);
					memcpy(m_specArray, specBuffer + count * m_specFrame, (dataCount - count) * m_specFrame * sizeof(T));
					memcpy(m_timeArray, timeBuffer + count, sizeof(long long) * (dataCount - count));
				}
				else
				{
					//尾部空间足够，则直接写入
					memcpy(m_specArray + write * m_specFrame, specBuffer, dataCount * m_specFrame * sizeof(T));
					memcpy(m_timeArray + write, timeBuffer, sizeof(long long) * dataCount);
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
			T *pSpec1, *pSpec2;
			long long *pTime1, *pTime2;
			int nCnt1, nCnt2;
			other.fetch(&pSpec1, &pTime1, &nCnt1, &pSpec2, &pTime2, &nCnt2);
			//将源缓存数据写入当前缓存中
			this->write(pSpec1, pTime1, nCnt1);
			if (nCnt2 > 0)
			{
				this->write(pSpec2, pTime2, nCnt2);
			}
			//清除源缓存数据
			other.m_dataStart = 0;
			other.m_dataCount = 0;

			return nCnt1 + nCnt2;
		}
        //重置当前缓存并将目标缓存数据复制到当前缓存中，清空目标缓存。
        int reset(LoopBuffer& other, T defValue)
        {
            //源缓存中的数据量大于当前缓存中新的数据总量，则源缓存中只保留新的数据总量
            if (other.m_dataCount > m_dataTotal)
            {
                other.m_dataStart += other.m_dataCount - m_dataTotal;
                if (other.m_dataStart >= other.m_dataTotal) other.m_dataStart -= other.m_dataTotal;
                other.m_dataCount = m_dataTotal;
            }
            //取出源缓存数据信息
            T *pSpec1, *pSpec2;
            long long *pTime1, *pTime2;
            int nCnt1, nCnt2;
            other.fetch(&pSpec1, &pTime1, &nCnt1, &pSpec2, &pTime2, &nCnt2);
            int nSize1 = nCnt1 * m_specFrame;
            int nSize2 = nCnt2 * m_specFrame;

            memcpy(m_specArray, pSpec1, sizeof(T) * nSize1);
            memcpy(m_timeArray, pTime1, sizeof(long long) * nCnt1);
            memcpy(m_specArray + nSize1, pSpec2, sizeof(T) * nSize2);
            memcpy(m_timeArray + nCnt1, pTime2, sizeof(long long) * nCnt2);
            m_dataStart = nCnt1 + nCnt2;
            if (m_dataStart == m_dataTotal)
            {
                m_dataStart = 0;
            }
            else
            {
                for(T* p = m_specArray + m_dataStart * m_specFrame, *e = m_specArray + m_dataTotal * m_specFrame; p < e; ++p)
                {
                    *p = defValue;
                }
                memset(m_timeArray + m_dataStart, 0, (m_dataTotal - m_dataStart) * sizeof(long long));
            }
            //清除源缓存数据
            other.m_dataStart = 0;
            other.m_dataCount = 0;
            //
            return nCnt1 + nCnt2;
        }
	};

protected:
	//清理当前对象所占用的相关资源。
	~WRWaterfallDataSourceT()
	{
		delete[] m_specBuffer1; 
		delete[] m_specBuffer2;
		delete[] m_timeBuffer1; 
		delete[] m_timeBuffer2;
	}

public:
	//初始化瀑布图实时数据源。
	explicit WRWaterfallDataSourceT(const WRWaterfallInitParams<T>& initArgs)
	{
		m_minValue = initArgs.minValue();
		m_maxValue = initArgs.maxValue();
		m_offValue = initArgs.offValue();
		m_difValue = m_maxValue - m_minValue;
		m_points = initArgs.points();
		m_isClosed = initArgs.isClosed();
		m_freqBegin = initArgs.freqBegin();
		m_freqEnd = initArgs.freqEnd();
		m_buffers = initArgs.buffers();
		m_capacity = initArgs.capacity();

		m_specBuffer1 = new T[m_points * m_buffers];
		m_specBuffer2 = new T[m_points * m_capacity];		
		m_timeBuffer1 = new long long[m_buffers];
		m_timeBuffer2 = new long long[m_capacity];
		m_dataStart1 = 0;
		m_dataCount1 = 0;
		m_dataStart2 = 0;
		m_dataCount2 = m_capacity;

		T defValue = initArgs.minValue();
		for(int i = 0, l = m_points * m_capacity; i < l; ++i)
		{
			m_specBuffer2[i] = defValue;
		}
		for(int i = 0; i < m_capacity; ++i)
		{
			m_timeBuffer2[i] = 0;
		}
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
	void append(const void* specBuffer, const long long* timeBuffer, int dataFrames)
	{
		LoopBuffer loopBuffer(m_specBuffer1, m_timeBuffer1, m_dataCount1, m_dataStart1, m_points, m_buffers);
		loopBuffer.write((T*)specBuffer, timeBuffer, dataFrames);
        m_changed = true;
	}

    //检查如果，如果数据改变，则将改变的数据生效，返回数据版本。
    long validate(void)
	{
        if (m_changed)
		{
			LoopBuffer srcBuf(m_specBuffer1, m_timeBuffer1, m_dataCount1, m_dataStart1, m_points, m_buffers);
            LoopBuffer dstBuf(m_specBuffer2, m_timeBuffer2, m_dataCount2, m_dataStart2, m_points, m_capacity);
            if (m_isClear)
            {
                m_frames = dstBuf.reset(srcBuf, (T)m_minValue);
                m_isClear = false;
            }
            else
            {
                m_frames += dstBuf.merge(srcBuf);
            }
            m_changed = false;
            ++m_version;
        }
        return m_version;
	}

	//取出从指定起始位置开始的指定数量的数据。
	void retrieve(double* pBuf, int pBeg, int pCnt, int fBeg, int fCnt) const
	{
        for(int f = 0; f < fCnt; ++f)
		{
			int nSrcIdx = m_dataStart2 + fBeg + f;
			if (nSrcIdx >= m_capacity) nSrcIdx -= m_capacity;
			T *pSrcBuf = m_specBuffer2 + nSrcIdx * m_points + pBeg;

			double* pDstBuf = pBuf + pCnt * f;

			for(int p = 0; p < pCnt; ++p)
			{
				pDstBuf[p] = pSrcBuf[p];
			}
        }
	}
	//取出从指定起始位置开始的指定数量的数据。
	void retrieve(double* pBuf, int pBeg, int* pIdx, int pCnt, int fBeg, int fCnt) const
	{
        for(int f = 0; f < fCnt; ++f)
		{
			int nSrcIdx = m_dataStart2 + fBeg + f;
			if (nSrcIdx >= m_capacity) nSrcIdx -= m_capacity;
			T* pSrcBuf = m_specBuffer2 + nSrcIdx * m_points + pBeg;

			double* pDstBuf = pBuf + pCnt * f;

			int nIdxP = 0;
			int* pIdxP = pIdx;
			for(int p = 0; p < pCnt; ++p, ++pIdxP, ++pDstBuf)
			{
				*pDstBuf = *pSrcBuf;
				++pSrcBuf;
				++nIdxP;
				for(; nIdxP < *pIdxP; ++nIdxP, ++pSrcBuf)
				{
					if (*pDstBuf < *pSrcBuf)
					{
						*pDstBuf = *pSrcBuf;
					}
				}
			}
        }
	}
	//取出从指定起始位置开始的指定数量的数据。
	void retrieve(double* pBuf, int pBeg, int pCnt, int fBeg, int* fIdx, int fCnt) const
	{
        for(int f = 0; f < fCnt; ++f)
		{
			int fIdxBeg = f == 0 ? 0 : fIdx[f -1];
			int fIdxEnd = fIdx[f];

			int nSrcIdx = fBeg + m_dataStart2 + fIdxBeg;
			if (nSrcIdx >= m_capacity) nSrcIdx -= m_capacity;
			T* pSrcBuf = m_specBuffer2 + nSrcIdx * m_points + pBeg;

			double* pDstBuf = pBuf + f * pCnt;

			for(int p = 0; p < pCnt; ++p)
			{
				pDstBuf[p] = pSrcBuf[p];
			}

			++nSrcIdx;
			if (nSrcIdx == m_capacity)
			{
				nSrcIdx = 0;
				pSrcBuf = m_specBuffer2 + pBeg;
			}
			else
			{
				pSrcBuf += m_points;
			}

			++fIdxBeg;

			for(; fIdxBeg < fIdxEnd; ++fIdxBeg)
			{
				double *pDstBuf2 = pDstBuf;
				T* pSrcBuf2 = pSrcBuf;
				for(int p = 0; p < pCnt; ++p, ++pDstBuf2, ++pSrcBuf2)
				{
					if (*pDstBuf2 < *pSrcBuf2)
					{
						*pDstBuf2 = *pSrcBuf2;
					}
				}

				++nSrcIdx;
				if (nSrcIdx == m_capacity)
				{
					nSrcIdx = 0;
					pSrcBuf = m_specBuffer2 + pBeg;
				}
				else
				{
					pSrcBuf += m_points;
				}
			}
        }
	}
	//取出从指定起始位置开始的指定数量的数据。
	void retrieve(double* pBuf, int pBeg, int* pIdx, int pCnt, int fBeg, int* fIdx, int fCnt) const
	{
        for(int f = 0; f < fCnt; ++f)
		{
			int fIdxBeg = f == 0 ? 0 : fIdx[f -1];
			int fIdxEnd = fIdx[f];

			int nSrcIdx = fBeg + m_dataStart2 + fIdxBeg;
			if (nSrcIdx >= m_capacity) nSrcIdx -= m_capacity;
			T* pSrcBuf = m_specBuffer2 + nSrcIdx * m_points + pBeg;

			double* pDstBuf = pBuf + f * pCnt;

			int nIdxP = 0;
			int *pIdxP = pIdx;
			T *pSrcBuf2 = pSrcBuf;
			double *pDstBuf2 = pDstBuf;
			for(int p = 0; p < pCnt; ++p, ++pIdxP, ++pDstBuf2)
			{
				*pDstBuf2 = *pSrcBuf2;
				++nIdxP;
				++pSrcBuf2;
				for(; nIdxP < *pIdxP; ++nIdxP, ++pSrcBuf2)
				{
					if (*pDstBuf2 < *pSrcBuf2)
					{
						*pDstBuf2 = *pSrcBuf2;
					}
				}
			}

			++nSrcIdx;
			if (nSrcIdx == m_capacity)
			{
				nSrcIdx = 0;
				pSrcBuf = m_specBuffer2 + pBeg;
			}
			else
			{
				pSrcBuf += m_points;
			}

			++fIdxBeg;

			for(; fIdxBeg < fIdxEnd; ++fIdxBeg)
			{
				nIdxP = 0;
				pIdxP = pIdx;
				pDstBuf2 = pDstBuf;
				pSrcBuf2 = pSrcBuf;
				for(int p = 0; p < pCnt; ++p, ++pIdxP, ++pDstBuf2)
				{
					for(; nIdxP < *pIdxP; ++nIdxP, ++pSrcBuf2)
					{
						if (*pDstBuf2 < *pSrcBuf2)
						{
							*pDstBuf2 = *pSrcBuf2;
						}
					}
				}

				++nSrcIdx;
				if (nSrcIdx == m_capacity)
				{
					nSrcIdx = 0;
					pSrcBuf = m_specBuffer2 + pBeg;
				}
				else
				{
					pSrcBuf += m_points;
				}
			}			
        }
	}
	
	//获取指定位置的数据值。
	double getValue(int frameIndex, int pointIndex) const
	{
		frameIndex += m_dataStart2;
		if (frameIndex >= m_capacity) frameIndex -= m_capacity;
		return m_specBuffer2[frameIndex * m_points + pointIndex];
	}

	//获取指定索引的时间值。
	long long getTimeValue(int index) const
	{
		index += m_dataStart2;
		if (index >= m_capacity) index -= m_capacity;
		return m_timeBuffer2[index];
	}
};

#endif //WRWATERFALLDATASOURCET
