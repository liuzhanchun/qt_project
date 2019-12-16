#include <WRCharting/WRSpectroChannel.h>
#include <WRCharting/WRSpectroControl.h>
#include <WRCharting/WRSpectroDataSource.h>

//表示数据值位置辅助类。
//height - 1 - (int)((value - showDataValueBegin) * (height - 1) / showDataValueSpan + 0.5);
class WRSpectroDataValuePosition
{
private:
	int m_h1;	//height - 1
	double m_v1;//showDataValueBegin
	double m_v2;//showDataValueSpan

public:
	//初始化数据值位置辅助类。
	inline WRSpectroDataValuePosition(WRSpectroControl* chart)
	{
		WRSpectroDataViewElement* dataView = chart->dataView();			
		m_h1 = dataView->height() - 1;
		m_v1 = chart->showDataValueBegin();
		m_v2 = chart->showDataValueSpan();
	}
		
	//计算指定值的位置。
	inline int process(double value)
	{
		return m_h1 - (int)((value - m_v1) * m_h1 / m_v2 + 0.5);
	}
};

//重建点缓存。
void WRSpectroChannel::createBuffer(void)
{
	WRSpectroDataViewElement* dataView = m_owner->dataView();
	WRSpectroDataSource* dataSource = m_owner->dataSource();
	WRSpectroDataChannel* dataChannel = dataSource->channel(m_index);

	if (m_owner->showDataPointCount() >= dataView->width() * 2)
	{
		double* pData = dataView->m_showBuffer;
		if (dataChannel->retrieve(pData, m_owner->showDataPointBegin(), dataView->m_showIndex, dataView->width(), (WRSpectroDataChannel::ZoomMethod)m_dataZoomMethod))
        {
			WRSpectroDataValuePosition dataValuePos(m_owner);
			if (m_dataZoomMethod == ShowDataRange)
			{
				QPoint *p = getPointBuffer(dataView->width() * 2);
				for (int x = 0, l = dataView->width(); x < l; ++x)
				{
                    p->setX(x);
                    p->setY(dataValuePos.process(pData[0]));
					++p;

                    p->setX(x);
                    p->setY(dataValuePos.process(pData[1]));
					++p;

					pData += 2;
				}

				int* markBuf = 0;
				int markLen = dataChannel->retrieve(&markBuf, m_owner->showDataPointBegin(), m_owner->showDataPointCount());
				if (markLen < 0)
				{
					delMarkPointBuffer();
				}
				else
				{
					m_markPointCount = 0;
					getMarkPointBuffer(dataView->width());
					int markIdx = 0;
					for(int x = 0, l = dataView->width(); x < l; ++x)
					{
						int dataEnd = dataView->m_showIndex[x] + m_owner->showDataPointBegin();
						bool exists = false;
						for(; markIdx < markLen; ++markIdx, ++markBuf)
						{
							if(*markBuf < dataEnd)
							{
								exists = true;
							}
							else
							{
								break;
							}
						}
						if (exists)
						{
							QPoint* p1 = m_pointBuffer + x * 2;
							QPoint* p2 = p1 + 1;
                            m_markPointBuffer[m_markPointCount] = p1->y() < p2->y() ? *p1 : *p2;
							++m_markPointCount;
						}
					}
				}
			}
			else
			{
				QPoint *p = getPointBuffer(dataView->width());
				for (int x = 0, l = dataView->width(); x < l; ++x, ++pData, ++p)
				{
                    p->setX(x);
                    p->setY(dataValuePos.process(*pData));
				}
				
				int* markBuf = 0;
				int markLen = dataChannel->retrieve(&markBuf, m_owner->showDataPointBegin(), m_owner->showDataPointCount());
				if (markLen < 0)
				{
					delMarkPointBuffer();
				}
				else
				{
					m_markPointCount = 0;
					getMarkPointBuffer(dataView->width());
					int markIdx = 0;
					for(int x = 0, l = dataView->width(); x < l; ++x)
					{
						int dataEnd = dataView->m_showIndex[x] + m_owner->showDataPointBegin();
						bool exists = false;
						for(; markIdx < markLen; ++markIdx, ++markBuf)
						{
							if(*markBuf < dataEnd)
							{
								exists = true;
							}
							else
							{
								break;
							}
						}
						if (exists)
						{
							m_markPointBuffer[m_markPointCount] = m_pointBuffer[x];
							++m_markPointCount;
						}
					}
				}
			}
        }
		else
		{
			delPointBuffer();
			delMarkPointBuffer();
		}
	}
	else
	{
		double* pData = dataView->m_showBuffer;
		if (dataChannel->retrieve(pData, m_owner->showDataPointBegin(), m_owner->showDataPointCount()))
		{
			WRSpectroDataValuePosition dataValuePos(m_owner);
            if (m_owner->showDataPointCount() >= 2)
            {
                QPoint *p = getPointBuffer(m_owner->showDataPointCount());
                for (int i = 0, l = m_owner->showDataPointCount(); i < l; ++i, ++pData, ++p)
                {
                    p->setX(dataView->m_showIndex[i]);
                    p->setY(dataValuePos.process(*pData));
                }
				
				int* markBuf = 0;
				int markLen = dataChannel->retrieve(&markBuf, m_owner->showDataPointBegin(), m_owner->showDataPointCount());
				if (markLen < 0)
				{
					delMarkPointBuffer();
				}
				else
				{
					m_markPointCount = 0;
					getMarkPointBuffer(m_owner->showDataPointCount());
					for(int i = 0; i < markLen; ++i, ++m_markPointCount)
					{
						m_markPointBuffer[i] = m_pointBuffer[markBuf[i] - m_owner->showDataPointBegin()];
					}
				}
            }
            else
            {
				QPoint *p = getPointBuffer(2);
                int y = dataValuePos.process(*pData);
                {
                    p->setX(0);
                    p->setY(y);
                }
                ++p;
                {
                    p->setX(dataView->width() - 1);
                    p->setY(y);
				}
				delMarkPointBuffer();
			}
		}
		else
		{
			delPointBuffer();
			delMarkPointBuffer();
		}
	}
}

//执行绘制处理。
void WRSpectroChannel::onPaint(QPainter& painter)
{
	if (visible())
	{
		if (invalid())
		{
			createBuffer();
			invalid(false);
		}
		if (m_pointBuffer)
		{
            painter.setPen(m_lineColor);
            painter.drawPolyline(m_pointBuffer, m_pointLength);
            if (m_markPointCount > 0)
            {
                QBrush brush(m_markColor);
                painter.setBrush(brush);

                QPoint* p = m_markPointBuffer;
                for(int i = 0; i < m_markPointCount; ++i, ++p)
                {
                    painter.drawRect(p->x() - 3, p->y() - 3, 7, 7);
                }
            }
		}
	}
	else
	{
		delPointBuffer();
		delMarkPointBuffer();
	}
}

//设置是否可见。
void WRSpectroChannel::setVisible(bool value)
{
    if (readFlag(WRSPECTROCHANNEL_VISIBLE) != value)
    {
        writeFlag(WRSPECTROCHANNEL_VISIBLE, value);
        m_owner->dataView()->invalidate();
        m_owner->invalidate();
        invalidate();
        emit visibleChanged(value);
    }
}
//设置线条颜色。
void WRSpectroChannel::setLineColor(WRColor value)
{
    if (m_lineColor.change(value.red(), value.green(), value.blue()))
    {
        if (visible())
        {
            m_owner->dataView()->invalidate();
            m_owner->invalidate();
        }
        emit lineColorChanged(m_lineColor);
    }
}
//设置标记颜色。
void WRSpectroChannel::setMarkColor(WRColor value)
{
    if (m_markColor.change(value.red(), value.green(), value.blue()))
    {
        if (visible())
        {
            m_owner->dataView()->invalidate();
            m_owner->invalidate();
        }
        emit markColorChanged(m_markColor);
    }
}

//设置是否可见。
bool WRSpectroChannel::visible(bool value)
{
	if (readFlag(WRSPECTROCHANNEL_VISIBLE) != value)
	{
		writeFlag(WRSPECTROCHANNEL_VISIBLE, value);
		m_owner->dataView()->invalidate();
		m_owner->invalidate();
		invalidate();
        emit visibleChanged(value);
		return true;
	}
	return false;
}
//设置线条颜色。
bool WRSpectroChannel::lineColor(WRColor value)
{
	if (m_lineColor.change(value.red(), value.green(), value.blue()))
	{
		if (visible())
		{
			m_owner->dataView()->invalidate();
			m_owner->invalidate();
		}
        emit lineColorChanged(m_lineColor);
		return true;
	}
	return false;
}
//设置标记颜色。
bool WRSpectroChannel::markColor(WRColor value)
{
	if (m_markColor.change(value.red(), value.green(), value.blue()))
	{
		if (visible())
		{
			m_owner->dataView()->invalidate();
			m_owner->invalidate();
		}
        emit markColorChanged(m_markColor);
		return true;
	}
	return false;
}

//更改数据，如果数据为NULL，则表示清空数据。
void WRSpectroChannel::alterData(const void* data)
{
	m_owner->alterData(m_index, data);
}
//更改数据，如果数据为NULL，则表示清空数据, 如果。
void WRSpectroChannel::alterData(const void* data, const int* markBuf, int markLen)
{
	m_owner->alterData(m_index, data, markBuf, markLen);
}

//设置数据抽取方式。
void WRSpectroChannel::setDataZoomMethod(DataZoomMethod value)
{
    if (value != m_dataZoomMethod)
    {
        m_dataZoomMethod = value;
        invalidate();
        if (visible())
        {
            m_owner->dataView()->invalidate();
            m_owner->invalidate();
        }
        emit dataZoomMethodChanged(value);
    }
}
//设置数据抽取方式。
bool WRSpectroChannel::dataZoomMethod(DataZoomMethod value)
{
	if (value != m_dataZoomMethod)
	{
		m_dataZoomMethod = value;
        invalidate();
        if (visible())
        {
            m_owner->dataView()->invalidate();
            m_owner->invalidate();
        }
        emit dataZoomMethodChanged(value);
		return true;
	}
	return false;
}
