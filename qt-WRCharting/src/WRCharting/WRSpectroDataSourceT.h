#pragma once
#ifndef WRSPECTRODATASOURCET
#define WRSPECTRODATASOURCET

#include <WRCharting/WRSpectroChannel.h>
#include <WRCharting/WRSpectroDataSource.h>
#include <WRCharting/WRSpectroInitParams.h>

//表示频谱图数据通道。
template <class T> class WRSpectroDataChannelT : public WRSpectroDataChannel
{
	template <class Ty> friend class WRSpectroDataSourceT;

private:
	int m_points;
	bool m_changed;
	T* m_buffer1;
	T* m_buffer2;
	int* m_markBuffer1;		//标记缓存1
	int* m_markBuffer2;		//标记缓存2
	int m_markBuffer1Size;	//标记缓存1容量
	int m_markBuffer2Size;	//标记缓存2容量
	int m_markLength1;		//标记数量1
	int m_markLength2;		//标记数量2

protected:
	//清理当前对象所占用的相关资源。
	~WRSpectroDataChannelT(void)
	{
		if (m_buffer1) delete[] m_buffer1;
		if (m_buffer2) delete[] m_buffer2;
		if (m_markBuffer1) delete[] m_markBuffer1;
		if (m_markBuffer2) delete[] m_markBuffer2;
	}

public:
	//初始化频谱图数据通道。
	inline WRSpectroDataChannelT(void)
	{
		m_changed = false;
		m_buffer1 = 0;
		m_buffer2 = 0;
		m_markBuffer1 = 0;
		m_markBuffer2 = 0;
		m_markBuffer1Size = 0;
		m_markBuffer2Size = 0;
		m_markLength1 = -1;
		m_markLength2 = -1;
	}

	//更新指定的数据。
	void change(const void* data)
	{
		if (data == 0)
		{
			if (m_buffer1)
			{
				delete[] m_buffer1;
				m_buffer1 = 0;
				if (m_markBuffer1)
				{
					delete[] m_markBuffer1;
					m_markBuffer1 = 0;
					m_markLength1 = -1;
					m_markBuffer1Size = 0;
				}
				m_changed = true;
			}
		}
		else
		{
			if (m_buffer1 == 0)
			{
				m_buffer1 = new T[m_points];
			}			
			memcpy(m_buffer1, data, sizeof(T) * m_points);
			if (m_markBuffer1)
			{
				delete[] m_markBuffer1;
				m_markBuffer1 = 0;
				m_markLength1 = -1;
				m_markBuffer1Size = 0;
			}
			m_changed = true;
		}
	}
	//更新指定的数据。
	void change(const void* data, const int* markBuf, int markLen)
	{
		if (data == 0)
		{
			if (m_buffer1)
			{
				delete[] m_buffer1;
				m_buffer1 = 0;
				if (m_markBuffer1)
				{
					delete[] m_markBuffer1;
					m_markBuffer1 = 0;
					m_markLength1 = -1;
					m_markBuffer1Size = 0;
				}
				m_changed = true;
			}
		}
		else
		{
			if (m_buffer1 == 0)
			{
				m_buffer1 = new T[m_points];
			}			
			memcpy(m_buffer1, data, sizeof(T) * m_points);
			if (markLen < 0)
			{
				if (m_markBuffer1)
				{
					delete[] m_markBuffer1;
					m_markBuffer1 = 0;
					m_markLength1 = -1;
					m_markBuffer1Size = 0;
				}
			}
			else
			{
				if (m_markBuffer1Size < markLen)
				{
					if (m_markBuffer1)
					{
						delete[] m_markBuffer1;
					}
					int markSize = (markLen + 31) / 32 * 32;
					m_markBuffer1 = new int[markSize];
					m_markBuffer1Size = markSize;
				}
				if (markLen > 0)
				{
					memcpy(m_markBuffer1, markBuf, markLen * sizeof(int));
				}
				m_markLength1 = markLen;
			}
			m_changed = true;
		}
	}

	//使数据改变生效，并返回当前版本。
	long validate()
	{
		if (m_changed)
		{
			if (m_buffer1 == 0)
			{
				if (m_buffer2)
				{
					delete[] m_buffer2;
                    m_buffer2 = 0;
				}
				if (m_markBuffer2)
				{
					delete[] m_markBuffer2;
					m_markBuffer2 = 0;
					m_markLength2 = -1;
					m_markBuffer2Size = 0;
				}
			}
			else
			{
				if (m_buffer2 == 0)
				{
					m_buffer2 = new T[m_points];
				}			
				memcpy(m_buffer2, m_buffer1, sizeof(T) * m_points);
				if (m_markLength1 < 0)
				{
					if (m_markBuffer2)
					{
						delete[] m_markBuffer2;
						m_markBuffer2 = 0;
						m_markLength2 = -1;
						m_markBuffer2Size = 0;
					}
				}
				else
				{
					if (m_markBuffer2Size < m_markLength1)
					{
						if (m_markBuffer2)
						{
							delete[] m_markBuffer2;
						}
						m_markBuffer2 = new int[m_markBuffer1Size];
						m_markBuffer2Size = m_markBuffer1Size;
					}
					if (m_markLength1 > 0)
					{
						memcpy(m_markBuffer2, m_markBuffer1, m_markLength1 * sizeof(int));
					}
					m_markLength2 = m_markLength1;
				}
			}
			m_changed = false;
			++m_version;
		}
		return m_version;
	}

	//取出从指定起始位置开始的指定数量的数据。
	bool retrieve(double* pBuf, int nBeg, int nCnt)
	{
		if (m_buffer2 == 0)
		{
			return false;
		}
		T* pSrc = m_buffer2 + nBeg;
		double* pDst = pBuf;
		for(int i = 0; i < nCnt; ++i, ++pDst, ++pSrc)
		{
			*pDst = *pSrc;
		}
		return true;
	}
	//取出从指定起始位置开始的按指定范围和方法的数据。
	bool retrieve(double* pBuf, int nBeg, int* pIdx, int nCnt, ZoomMethod tWay)
	{
		if (m_buffer2 == 0)
		{
			return false;
		}
		switch(tWay)
		{
		case Range:
			{
				T* pSrc = m_buffer2 + nBeg;
                double* pDst = pBuf;
                for(int i = 0; i < nCnt; ++i)
				{
					int nDatBeg = i == 0 ? 0 : pIdx[i - 1];
					int nDatEnd = pIdx[i];
					T* pDat = pSrc + nDatBeg;
					
					int nMin = 0;
					int nMax = 0;
					double fMin = *pDat;
					double fMax = *pDat;
					++pDat;
					++nDatBeg;
					for(int nDatIdx = nDatBeg; nDatIdx < nDatEnd; ++nDatIdx, ++pDat)
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
					}

					int nBufIdx = i * 2;
					if (nMin < nMax)
					{
						pDst[nBufIdx] = fMin;
						pDst[nBufIdx+ 1] = fMax;
					}
					else
					{
						pDst[nBufIdx] = fMax;
						pDst[nBufIdx + 1] = fMin;
					}
                }
			}
			break;
		case MaxValue:
			{
				T* pSrc = m_buffer2 + nBeg;
                double* pDst = pBuf;
                for(int i = 0; i < nCnt; ++i)
				{
					int nDatBeg = i == 0 ? 0 : pIdx[i - 1];
					int nDatEnd = pIdx[i];
					T* pDat = pSrc + nDatBeg;

					double fMax = *pDat;
					++pDat;
					++nDatBeg;
					for(int nDatIdx = nDatBeg; nDatIdx < nDatEnd; ++nDatIdx, ++pDat)
					{
						if (fMax < *pDat)
						{
							fMax = *pDat;
						}
					}

					pDst[i] = fMax;
                }
			}
			break;
		case MinValue:
			{
				T* pSrc = m_buffer2 + nBeg;
				double* pDst = pBuf;
                for(int i = 0; i < nCnt; ++i)
				{
					int nDatBeg = i == 0 ? 0 : pIdx[i - 1];
					int nDatEnd = pIdx[i];
					T* pDat = pSrc + nDatBeg;

					double fMin = *pDat;
					++pDat;
					++nDatBeg;
					for(int nDatIdx = nDatBeg; nDatIdx < nDatEnd; ++nDatIdx, ++pDat)
					{
						if (fMin > *pDat)
						{
							fMin = *pDat;
						}
					}

					pDst[i] = fMin;
                }
			}
			break;
		default:
			return false;
		}
		return true;
	}

	//取出从指定起始位置开始的指定数量范围内的标记数据。
	int retrieve(int** pBuf, int nBeg, int nCnt)
	{
		if (m_markLength2 < 0)
		{
			return -1;
		}
		else
		{
			int *markBuffer = 0;
			int markLength = 0;
			if (m_markLength2 > 0)
			{
				markBuffer = m_markBuffer2;
				//寻找标记起始
				int markStart = 0;
				for (; markStart < m_markLength2; ++markStart, ++markBuffer)
				{
					if (*markBuffer >= nBeg) break;
				}
				//寻找标记结束
				int markEnd = markStart;
				int showEnd = nBeg + nCnt - 1;
				for (int i = 0; markEnd < m_markLength2; ++markEnd, ++i)
				{
					if (markBuffer[i] > showEnd) break;
				}
				//
				markLength = markEnd - markStart;
			}
			*pBuf = markBuffer;
			return markLength;
		}
	}

	//获取指定索引的数据值。
	bool getValue(int index, double* value) const
	{
		if (m_buffer2)
		{
			*value = m_buffer2[index];
			return true;
		}
		return false;
	}
};

//表示瀑布图数据源模板。
template <class T> class WRSpectroDataSourceT : public WRSpectroDataSource
{
private:
	WRSpectroDataChannelT<T> m_channels[WRSPECTROCHANNELS];

protected:
	//清理当前对象所占用的相关资源。
	~WRSpectroDataSourceT()
	{
		//add code here
	}

public:
	//初始化瀑布图实时数据源。
	explicit WRSpectroDataSourceT(const WRSpectroInitParams<T>& initArgs)
	{
		m_minValue = initArgs.minValue();
		m_maxValue = initArgs.maxValue();
		m_offValue = initArgs.offValue();
		m_points = initArgs.points();
		m_isClosed = initArgs.isClosed();
		m_freqBegin = initArgs.freqBegin();
		m_freqEnd = initArgs.freqEnd();

		for(int i = 0; i < WRSPECTROCHANNELS; ++i)
		{
			m_channels[i].m_points = m_points;
		}
	}
	
	//获取指定索引的通道。
	WRSpectroDataChannel* channel(int index)
	{
		return &m_channels[index];
	}
};

#endif //WRSPECTRODATASOURCET
