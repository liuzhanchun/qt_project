#pragma once
#ifndef WROSCILLODATASOURCET
#define WROSCILLODATASOURCET

#include <WRCharting/WROscilloDataSource.h>
#include <WRCharting/WROscilloInitParams.h>

//表示瀑布图数据源模板。
template <class T> class WROscilloDataSourceT : public WROscilloDataSource
{
private:
	T* m_dataBuffer1;
	T* m_dataBuffer2;
	int m_dataCount1;	//数据缓存1数量
	int m_dataStart1;	//数据缓存1起始
	int m_dataCount2;	//数据缓存2数量
	int m_dataStart2;	//数据缓存2缓存

    //声明时间链表。
    class TimeList;
	//表示时间数据。
	class TimeData
	{
        friend class WROscilloDataSourceT<T>::TimeList;

	private:
		long long m_value;
		TimeData* m_next;
		int m_count;

		//禁用复制构造函数。
		TimeData(const TimeData& other);
		//禁用赋值操作符。
		TimeData& operator =(const TimeData& other);

	public:
		//初始化时间数据。
		inline TimeData(long long value, int count)
		{
			m_value = value;
			m_count = count;
			m_next = 0;
		}

		//获取起始时间值。
		inline long long value(void) const
		{
			return m_value;
		}
		//获取数据数量。
		inline int count(void) const
		{
			return m_count;
		}

		//获取下一个数据。
		inline TimeData* next(void)
		{
			return m_next;
		}

		//偏移指定个数。
		inline void offset(int count, int sampleRate)
		{
			m_value += 10000000LL * count / sampleRate;
			m_count -= count;
		}
		//更新数据内容。
		inline void update(long long value, int count)
		{
			m_value = value;
			m_count = count;
		}
	};
	//表示时间链表。
	class TimeList
	{
	private:
		TimeData* m_first;
		TimeData* m_last;

	public:
		//初始化时间链表。
		inline TimeList(void)
		{
			m_first = 0;
			m_last = 0;
		}
		//清理当前对象所占用的相关资源。
		~TimeList(void)
		{
			TimeData* data = m_first;
			while(data)
			{
				TimeData* data2 = data;
				data = data->next();
				delete data2;
			}
		}

		//初始化时间链表。
		inline void init(int count)
		{
			m_first = new TimeData(0, count);
			m_last = m_first;
		}

		//获取最开始的数据。
		inline TimeData* first(void) const
		{
			return m_first;
		}
		//获取最末的数据。
		inline TimeData* last(void) const
		{
			return m_last;
		}

		//将指定的数据添加到末尾。
		inline void add(TimeData* data)
		{
			if (m_last)
			{
				m_last->m_next = data;
				m_last = data;
			}
			else
			{
				m_first = data;
				m_last = data;
			}
		}
		//移除最开始的数据。
		inline TimeData* remove()
		{
			TimeData* data = m_first;
			if (data)
			{
				m_first = data->next();
				if (m_first == 0)
				{
					m_last = 0;
				}
				data->m_next = 0;
			}
			return data;
		}

		//偏移指定数量的数据。
		inline void offset(int count, int sampleRate)
		{
			while(count > 0)
			{
				TimeData* timeData = m_first;
				if (timeData->m_count <= count)
				{
					remove();
					count -= timeData->m_count;
					delete timeData;
				}
				else
				{
					timeData->offset(count, sampleRate);
					break;
				}
			}
		}

		//清理所有的数据。
		inline void clear(void)
		{
			TimeData* data = m_first;
			while(data)
			{
				TimeData* data2 = data;
				data = data->next();
				delete data2;
			}
			m_first = 0;
			m_last = 0;
		}
		
		//将其添加到末尾。
		inline void add(TimeList& other)
		{
			do
			{
				TimeData* data = other.remove();
				if (data)
				{
					add(data);
				}
				else
				{
					break;
				}
			}while(true);
		}
		//执行交换处理。
		inline void swap(TimeList& other)
		{
			TimeData* first = other.m_first;
			other.m_first = m_first;
			m_first = first;

			TimeData* last = other.m_last;
			other.m_last = m_last;
			m_last = last;
		}

		//获取指定数据索引的时间。
		inline long long getValue(int index, int sampleRate) const
		{
			TimeData* data = m_first;
			while(index >= data->count())
			{
				index -= data->count();
				data = data->next();
			}
			return data->value() + 10000000LL * index / sampleRate;
		}
	};
	
	TimeList m_timeList1;	//时间链表1
	TimeList m_timeList2;	//时间链表2

	//表示循环缓存。
	class LoopBuffer
	{
	private:
		T* m_dataArray;			//缓存数组
        const int& m_dataTotal;	//缓存总长
		int& m_dataCount;		//数据数量
		int& m_dataStart;		//数据起始
		TimeList& m_timeList;	//时间链表

		//写入指定的数据。
		void write(const T* pBuf, int nLen)
		{
			if (nLen >= m_dataTotal)
			{
				//写入数据超过数据总量，则直接从0开始复制并设置数据量为数据总量
				memcpy(m_dataArray, pBuf + nLen - m_dataTotal, sizeof(T)*m_dataTotal);
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
				if (count < nLen)
				{
					//尾部可写入数据量小于要写入的数据量，则分两段进行写入
					memcpy(m_dataArray + write, pBuf, sizeof(T) * count);
					memcpy(m_dataArray, pBuf + count, sizeof(T) * (nLen - count));
				}
				else
				{
					//尾部空间足够，则直接写入
					memcpy(m_dataArray + write, pBuf, sizeof(T) * nLen);
				}
				//计算数据长度
				count = m_dataCount + nLen;
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

	public:
		//初始化能力图循环缓存。
		LoopBuffer(T* dataArray, int &dataTotal, int &dataCount, int &dataStart, TimeList& timeList)
			: m_dataTotal(dataTotal), m_dataCount(dataCount), m_dataStart(dataStart), m_timeList(timeList)
		{
			m_dataArray = dataArray;
		}
		
		//获取当前数据。
		void fetch(T** pBuf1, int* nLen1, T** pBuf2, int* nLen2)
		{
			*pBuf1 = m_dataArray + m_dataStart;
			int count = m_dataTotal - m_dataStart;
			if (count < m_dataCount)
			{
				*nLen1 = count;
				*pBuf2 = m_dataArray;
				*nLen2 = m_dataCount - count;
			}
			else
			{
				*nLen1 = m_dataCount;
				*pBuf2 = 0;
				*nLen2 = 0;
			}
		}

		//写入指定的数据。
		void write(const T* pBuf, int nLen, long long time, int sampleRate)
		{
			if (nLen >= m_dataTotal)
			{
				//更新时间信息。
				TimeData* timeData = 0;
				do{
					TimeData* timeData2 = m_timeList.remove();
					if (timeData2 == 0)
					{
						if (timeData)
						{
							timeData->update(time, nLen);
						}
						else
						{
							timeData = new TimeData(time, nLen);
						}
						timeData->offset(nLen - m_dataTotal, sampleRate);
						m_timeList.add(timeData);
						break;
					}
					if (timeData)
					{
						delete timeData;
					}
					timeData = timeData2;
				}while(true);
				//写入数据超过数据总量，则直接从0开始复制并设置数据量为数据总量
				memcpy(m_dataArray, pBuf + nLen - m_dataTotal, sizeof(T)*m_dataTotal);
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
				if (count < nLen)
				{
					//尾部可写入数据量小于要写入的数据量，则分两段进行写入
					memcpy(m_dataArray + write, pBuf, sizeof(T) * count);
					memcpy(m_dataArray, pBuf + count, sizeof(T) * (nLen - count));
				}
				else
				{
					//尾部空间足够，则直接写入
					memcpy(m_dataArray + write, pBuf, sizeof(T) * nLen);
				}
				//计算数据长度
				count = m_dataCount + nLen;
				if (count > m_dataTotal)
				{
					//数据长度大小数据总量，则表示头部被覆盖，需移动头部为覆盖的数据量
					m_dataStart += count - m_dataTotal;
					if (m_dataStart >= m_dataTotal) m_dataStart -= m_dataTotal;
					//设置设置数据量为数据总量
					m_dataCount = m_dataTotal;
					//设置时间信息
					count -= m_dataTotal;
					TimeData* timeData = 0;
					do
					{
						TimeData* timeData2 = m_timeList.first();
						if (timeData2->count() < count)
						{
							if (timeData)
							{
								delete timeData;
							}
							timeData = m_timeList.remove();
							count -= timeData2->count();
						}
						else if (timeData2->count() == count)
						{
							if (timeData)
							{
								delete timeData;
							}
							timeData = m_timeList.remove();
							timeData->update(time, nLen);
							m_timeList.add(timeData);
							break;
						}
						else
						{
							m_timeList.first()->offset(count, sampleRate);
							if (timeData)
							{
								timeData->update(time, nLen);
							}
							else
							{
								timeData = new TimeData(time, nLen);
							}
							m_timeList.add(timeData);
							break;
						}

					}while(true);
				}
				else
				{
					//数据长度小于等于数据总量，则直接设置长度，不移动数据首位置
					m_dataCount = count;
					//添加时间信息
					m_timeList.add(new TimeData(time, nLen));
				}
			}
		}

		//将目标缓存数据复制到当前缓存中，并清空目标缓存。
        int merge(LoopBuffer& other, int sampleRate)
		{
			//合并时间信息
			if (other.m_dataCount >= m_dataTotal)
			{
				other.m_timeList.offset(other.m_dataCount - m_dataTotal, sampleRate);
				m_timeList.clear();
				m_timeList.swap(other.m_timeList);
			}
			else
			{
				m_timeList.offset(m_dataCount + other.m_dataCount - m_dataTotal, sampleRate);
				m_timeList.add(other.m_timeList);
			}
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
			T *pBuf1, *pBuf2;
			int nBuf1, nBuf2;
			other.fetch(&pBuf1, &nBuf1, &pBuf2, &nBuf2);
			//将源缓存数据写入当前缓存中
			this->write(pBuf1, nBuf1);
			if (nBuf2 > 0)
			{
				this->write(pBuf2, nBuf2);
			}
			//清除源缓存数据
			other.m_dataStart = 0;
			other.m_dataCount = 0;
			//
			return nBuf1 + nBuf2;
		}
        //重置当前缓存并将目录缓存数据复制到当前缓存中，并清除目标缓存。
        int reset(LoopBuffer& other, int sampleRate)
        {
            if (other.m_dataCount > m_dataTotal)
            {
                other.m_timeList.offset(other.m_dataCount - m_dataTotal, sampleRate);
                other.m_dataStart += other.m_dataCount - m_dataTotal;
                if (other.m_dataStart >= other.m_dataTotal) other.m_dataStart -= other.m_dataTotal;
                other.m_dataCount = m_dataTotal;
            }
            //时间
            m_timeList.clear();
            m_timeList.swap(other.m_timeList);
            //数据
            T *pBuf1, *pBuf2;
            int nBuf1, nBuf2;
            other.fetch(&pBuf1, &nBuf1, &pBuf2, &nBuf2);
            memcpy(m_dataArray, pBuf1, sizeof(T) * nBuf1);
            memcpy(m_dataArray + nBuf1, pBuf2, sizeof(T) * nBuf2);
            m_dataStart = nBuf1 + nBuf2;
            if (m_dataStart == m_dataTotal)
            {
                m_dataStart = 0;
            }
            else
            {
                memset(m_dataArray + m_dataStart, 0, (m_dataTotal - m_dataStart) * sizeof(T));
            }
            //清除源缓存数据
            other.m_dataStart = 0;
            other.m_dataCount = 0;
            //
            return nBuf1 + nBuf2;
        }
	};

protected:
	//清理当前对象所占用的相关资源。
	~WROscilloDataSourceT()
    {
        delete[] m_dataBuffer1;
        delete[] m_dataBuffer2;
	}

public:
	//初始化瀑布图实时数据源。
	explicit WROscilloDataSourceT(const WROscilloInitParams<T>& initArgs)
	{
		m_minValue = initArgs.minValue();
		m_maxValue = initArgs.maxValue();
		m_sampleRate = initArgs.sampleRate();
		m_buffers = initArgs.buffers();
		m_capacity = initArgs.capacity();

		m_dataBuffer1 = new T[m_buffers];
		m_dataBuffer2 = new T[m_capacity];
		m_dataCount1 = 0;
		m_dataStart1 = 0;
		m_dataCount2 = m_capacity;
		m_dataStart2 = 0;
		memset(m_dataBuffer2, 0, m_capacity * sizeof(T));
		m_timeList2.init(m_capacity);
	}

    //清除所有数据。
    void clear(void)
    {
        m_dataStart1 = 0;
        m_dataCount1 = 0;
        m_timeList1.clear();
        m_isClear = true;
        m_changed = true;
    }
	//更新指定的数据。
	void append(const void* data, int size, long long time)
	{
		LoopBuffer loopBuffer(m_dataBuffer1, m_buffers, m_dataCount1, m_dataStart1, m_timeList1);
		loopBuffer.write((T*)data, size, time, m_sampleRate);
		m_changed = true;
	}

	//使数据改变生效，并返回当前版本。
    long validate()
	{
		if (m_changed)
		{
			LoopBuffer srcBuf(m_dataBuffer1, m_buffers, m_dataCount1, m_dataStart1, m_timeList1);
			LoopBuffer dstBuf(m_dataBuffer2, m_capacity, m_dataCount2, m_dataStart2, m_timeList2);
            if (m_isClear)
            {
                m_points = dstBuf.reset(srcBuf, m_sampleRate);
                m_isClear = false;
            }
            else
            {
                m_points += dstBuf.merge(srcBuf, m_sampleRate);
            }
            m_changed = false;
			++m_version;
		}
		return m_version;
	}

	//取出从指定起始位置开始的指定数量的数据。
	void retrieve(double* pBuf, int nBeg, int nCnt)
	{
		T* pBuf1, *pBuf2;
		int nCnt1, nCnt2;
		LoopBuffer loopBuffer(m_dataBuffer2, m_capacity, m_dataCount2, m_dataStart2, m_timeList2);
		loopBuffer.fetch(&pBuf1, &nCnt1, &pBuf2, &nCnt2);

		if (nCnt1 <= nBeg)
		{
			pBuf1 = pBuf2 + nBeg - nCnt1;
			nCnt1 = nCnt;
			nCnt2 = 0;
		}
		else
		{
			pBuf1 += nBeg;
			nCnt1 -= nBeg;
			if (nCnt1 < nCnt)
			{
				nCnt2 = nCnt - nCnt1;
			}
			else
			{
				nCnt1 = nCnt;
				nCnt2 = 0;
			}
		}

		for(int i = 0; i < nCnt1; ++i, ++pBuf, ++pBuf1)
		{
			*pBuf = *pBuf1;
		}
		for(int i = 0; i < nCnt2; ++i, ++pBuf, ++pBuf2)
		{
			*pBuf = *pBuf2;
		}
	}
	//取出从指定起始位置开始的按指定范围和方法的数据。
	void retrieve(double* pBuf, int nBeg, int* pIdx, int nCnt)
	{
		T* pBuf1, *pBuf2;
		int nCnt1, nCnt2;
		LoopBuffer loopBuffer(m_dataBuffer2, m_capacity, m_dataCount2, m_dataStart2, m_timeList2);
		loopBuffer.fetch(&pBuf1, &nCnt1, &pBuf2, &nCnt2);

		if (nCnt1 <= nBeg)
		{
			int nOff = nBeg - nCnt1;
			pBuf1 = pBuf2 + nOff;
			nCnt1 = nCnt2 - nOff;
			nCnt2 = 0;
		}
		else
		{
			pBuf1 += nBeg;
			nCnt1 -= nBeg;
		}		
		T* pEnd = pBuf1 + nCnt1;

        for(int i = 0; i < nCnt; ++i)
		{
			int nDatBeg = i == 0 ? 0 : pIdx[i - 1];
			int nDatEnd = pIdx[i];
			T* pDat;
			if (nDatBeg < nCnt1) pDat = pBuf1 + nDatBeg;
			else pDat = pBuf2 + nDatBeg - nCnt1;

			int nMin = 0;
			int nMax = 0;
			double fMin = *pDat;
			double fMax = *pDat;
			++pDat;
			if (pDat == pEnd)
			{
				pDat = pBuf2;
			}
			for(int nDatIdx = nDatBeg + 1; nDatIdx < nDatEnd; ++nDatIdx)
			{
				if (fMin > *pDat)
				{
					fMin = *pDat;
					nMin = nDatIdx;
				}
				if (fMax < *pDat)
				{
					fMax = *pDat;
					nMax = nDatIdx;
				}
				
				++pDat;
				if (pDat == pEnd)
				{
					pDat = pBuf2;
				}
			}

			int nBufIdx = i * 2;
			if (nMin < nMax)
			{
				pBuf[nBufIdx] = fMin;
				pBuf[nBufIdx+ 1] = fMax;
			}
			else
			{
				pBuf[nBufIdx] = fMax;
				pBuf[nBufIdx + 1] = fMin;
			}
        }
	}

	//获取指定索引的数据值。
	double getValue(int index) const
	{
		index += m_dataStart2;
		if (index >= m_capacity) index -= m_capacity;
		return m_dataBuffer2[index];
	}

	//获取指定索引的时间值。
	long long getTimeValue(int index) const
	{
		return m_timeList2.getValue(index, m_sampleRate);
	}
};

#endif //WROSCILLODATASOURCET
