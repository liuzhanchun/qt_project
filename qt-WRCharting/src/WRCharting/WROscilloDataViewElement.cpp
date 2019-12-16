#include <WRCharting/WROscilloDataViewElement.h>
#include <WRCharting/WROscilloControl.h>
#include <WRCharting/WRText.h>

//表示数据值位置辅助类。
//height - 1 - (int)((value - showDataValueBegin) * (height - 1) / showDataValueSpan + 0.5);
class WROscilloDataValuePosition
{
private:
	int m_h1;	//height - 1
	double m_v1;//showDataValueBegin
	double m_v2;//showDataValueSpan

public:
	//初始化数据值位置辅助类。
	inline WROscilloDataValuePosition(WROscilloControl* chart)
	{
		WROscilloDataViewElement* dataView = chart->dataView();			
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

//初始化波形图对象。
WROscilloDataViewElement::WROscilloDataViewElement(void)
	: m_backColor(4, 0, 0),
    m_gridColor(0, 53, 0),
    m_zeroColor(174, 181, 190),
    m_lineColor(173, 255, 48)
{
    buffered(true);//设置具有缓存
    writeFlag(WRCHARTDATAVIEW_VSCALABLE, false);
	writeFlag(WROSCILLODATAVIEW_GRIDVISIBLE, false);
	writeFlag(WROSCILLODATAVIEW_ZEROVISIBLE, true);
	writeFlag(WROSCILLODATAVIEW_BUFFERINVALID, true);

	m_showBuffer = 0;
	m_showIndex = 0;
	m_pointBuffer = 0;
	m_pointLength = 0;
}
//清理当前对象所占用的相关资源。
WROscilloDataViewElement::~WROscilloDataViewElement(void)
{
	if (m_showIndex)
	{
		delete[] m_showIndex;
	}
	if (m_showBuffer)
	{
		delete[] m_showBuffer;
	}
	delPointBuffer();
}

//重建点缓存。
void WROscilloDataViewElement::createBuffer(void)
{
    WROscilloControl* chart = (WROscilloControl*)owner();
    WROscilloDataSource* dataSource = chart->dataSource();

    if (chart->showDataPointCount() >= width() * 2)
    {
        double* pData = m_showBuffer;
        dataSource->retrieve(pData, chart->showDataPointBegin(), m_showIndex, width());
        WROscilloDataValuePosition dataValuePos(chart);
        QPoint *p = getPointBuffer(width() * 2);
        for (int x = 0, l = width(); x < l; ++x)
        {
            p->setX(x);
            p->setY(dataValuePos.process(pData[0]));
            ++p;

            p->setX(x);
            p->setY(dataValuePos.process(pData[1]));
            ++p;

            pData += 2;
        }
    }
    else
    {
        double* pData = m_showBuffer;
        dataSource->retrieve(pData, chart->showDataPointBegin(), chart->showDataPointCount());
        WROscilloDataValuePosition dataValuePos(chart);
        if (chart->showDataPointCount() >= 2)
        {
            QPoint *p = getPointBuffer(chart->showDataPointCount());
            for (int i = 0, l = chart->showDataPointCount(); i < l; ++i, ++pData, ++p)
            {
                p->setX(m_showIndex[i]);
                p->setY(dataValuePos.process(*pData));
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
                p->setX(width() - 1);
                p->setY(y);
            }
        }
    }
}

//设置背景颜色。
void WROscilloDataViewElement::setBackColor(WRColor value)
{
    if (m_backColor.change(value.red(), value.green(), value.blue()))
    {
        invalidate();
        doUpdate();
        emit backColorChanged(m_backColor);
    }
}
//设置网格颜色。
void WROscilloDataViewElement::setGridColor(WRColor value)
{
    if (m_gridColor.change(value.red(), value.green(), value.blue()))
    {
        if (gridVisible())
        {
            invalidate();
            doUpdate();
        }
        emit gridColorChanged(m_gridColor);
    }
}
//设置网格是否显示。
void WROscilloDataViewElement::setGridVisible(bool value)
{
    if (readFlag(WROSCILLODATAVIEW_GRIDVISIBLE) != value)
    {
        writeFlag(WROSCILLODATAVIEW_GRIDVISIBLE, value);
        invalidate();
        doUpdate();
        emit gridVisibleChanged(value);
    }
}
//设置零值颜色。
void WROscilloDataViewElement::setZeroColor(WRColor value)
{
    if (m_zeroColor.change(value.red(), value.green(), value.blue()))
    {
        if (zeroVisible())
        {
            invalidate();
            doUpdate();
        }
        emit zeroColorChanged(m_zeroColor);
    }
}
//设置零值是否显示。
void WROscilloDataViewElement::setZeroVisible(bool value)
{
    if (readFlag(WROSCILLODATAVIEW_ZEROVISIBLE) != value)
    {
        writeFlag(WROSCILLODATAVIEW_ZEROVISIBLE, value);
        invalidate();
        doUpdate();
        emit zeroVisibleChanged(value);
    }
}
//设置线条颜色。
void WROscilloDataViewElement::setLineColor(WRColor value)
{
    if (m_lineColor.change(value.red(), value.green(), value.blue()))
    {
        invalidate();
        doUpdate();
        emit lineColorChanged(m_lineColor);
    }
}

//设置背景颜色。
bool WROscilloDataViewElement::backColor(WRColor value)
{
	if (m_backColor.change(value.red(), value.green(), value.blue()))
	{
		invalidate();
		doUpdate();
        emit backColorChanged(m_backColor);
		return true;
	}
	return false;
}
//设置网格颜色。
bool WROscilloDataViewElement::gridColor(WRColor value)
{
	if (m_gridColor.change(value.red(), value.green(), value.blue()))
	{
        if (gridVisible())
        {
            invalidate();
            doUpdate();
        }
        emit gridColorChanged(m_gridColor);
		return true;
	}
	return false;
}
//设置网格是否显示。
bool WROscilloDataViewElement::gridVisible(bool value)
{
	if (readFlag(WROSCILLODATAVIEW_GRIDVISIBLE) != value)
	{
		writeFlag(WROSCILLODATAVIEW_GRIDVISIBLE, value);
		invalidate();
		doUpdate();
        emit gridVisibleChanged(value);
		return true;
	}
	return false;
}
//设置零值颜色。
bool WROscilloDataViewElement::zeroColor(WRColor value)
{
	if (m_zeroColor.change(value.red(), value.green(), value.blue()))
	{
        if (zeroVisible())
        {
            invalidate();
            doUpdate();
        }
        emit zeroColorChanged(m_zeroColor);
		return true;
	}
	return false;
}
//设置零值是否显示。
bool WROscilloDataViewElement::zeroVisible(bool value)
{
	if (readFlag(WROSCILLODATAVIEW_ZEROVISIBLE) != value)
	{
		writeFlag(WROSCILLODATAVIEW_ZEROVISIBLE, value);
		invalidate();
		doUpdate();
        emit zeroVisibleChanged(value);
		return true;
	}
	return false;
}
//设置线条颜色。
bool WROscilloDataViewElement::lineColor(WRColor value)
{
	if (m_lineColor.change(value.red(), value.green(), value.blue()))
	{
		invalidate();
		doUpdate();
        emit lineColorChanged(m_lineColor);
		return true;
	}
	return false;
}

//当显示数据范围改变后调用此方法 。
void WROscilloDataViewElement::onShowDataRangeChanged(void)
{
	invalidateBuffer();
	invalidate();
}
//当显示数据点范围改变后调用此方法。
void WROscilloDataViewElement::onShowDataPointRangeChanged(void)
{
    if (m_showIndex)
    {
        delete[] m_showIndex;
        m_showIndex = 0;
    }
}
//当显示数据值范围改变后调用此方法。
void WROscilloDataViewElement::onShowDataValueRangeChanged(void)
{
	//add code here
}

//当大小改变后调用此方法。
void WROscilloDataViewElement::onSizeChanged(void)
{
	invalidateBuffer();
}
//当宽度改变后调用此方法。
void WROscilloDataViewElement::onWidthChanged(void)
{
    if (m_showIndex)
    {
        delete[] m_showIndex;
        m_showIndex = 0;
    }
    if (m_showBuffer)
    {
        delete[] m_showBuffer;
        m_showBuffer = 0;
    }
}
//当高度改变后调用此方法。
void WROscilloDataViewElement::onHeightChanged(void)
{
	//add code here
}

//执行缩放处理。
bool WROscilloDataViewElement::doZoom(const WRPoint& begPos, const WRPoint& endPos)
{
    WROscilloControl* chart = (WROscilloControl*)owner();
    WRChartSampleRange showPointRange(chart->showDataPointRange());
    WRChartDValueRange showValueRange(chart->showDataValueRange());
    if (hScalable())
    {
        chart->doMouseZoomH(showPointRange, begPos.x() - left(), endPos.x() - left(), width());
    }
    if (vScalable())
    {
        chart->doMouseZoomV(showValueRange, begPos.y() - top(), endPos.y() - top(), height());
    }
    return chart->changeShowDataRange(WROscilloDataRange(showPointRange, showValueRange));
}
//执行移动处理。
bool WROscilloDataViewElement::doMove(const WRPoint& begPos, const WRPoint& endPos)
{
    WROscilloControl* chart = (WROscilloControl*)owner();
    WRChartSampleRange showPointRange(chart->showDataPointRange());
    WRChartDValueRange showValueRange(chart->showDataValueRange());
    chart->doMouseMoveH(showPointRange, begPos.x(), endPos.x(), width());
    chart->doMouseMoveV(showValueRange, begPos.y(), endPos.y(), height());
    return chart->changeShowDataRange(WROscilloDataRange(showPointRange, showValueRange));
}

//鼠标滚动处理。
bool WROscilloDataViewElement::onMouseWheel(const QWheelEvent& e)
{
	WROscilloControl* chart = (WROscilloControl*)owner();
	WRChartSampleRange showPointRange(chart->showDataPointRange());
	WRChartDValueRange showValueRange(chart->showDataValueRange());
	if (hScalable())
	{
		chart->doMouseWheelH(showPointRange, e.x() - left(), e.delta(), width());
	}
	if (vScalable())
	{
		chart->doMouseWheelV(showValueRange, e.y() - top(), e.delta(), height());
	}
	return chart->changeShowDataRange(WROscilloDataRange(showPointRange, showValueRange));
}

//初始化数据点索引。
void WROscilloDataViewElement::initIndex(void)
{
	if (m_showIndex == 0)
	{
		WROscilloControl* chart = (WROscilloControl*)owner();

		int showCount = chart->showDataPointCount();
		int showLast = showCount - 1;
		long showLastL = showLast;
		double showLastF = showLast;
		int showRight = width() - 1;
		long long showRightL = showRight;
		double showRightF = showRight;

		if (showCount > width() * 2)
		{
			m_showIndex = new int[width()];
			for (int x = 0; x < showRight; ++x)
			{
				int i1 = (int)(x * showLastL / showRightF + 0.5);
				int x1 = (int)(i1 * showRightL / showLastF + 0.5);
				if (x1 > x)
				{
					for (int i = i1 - 1; i >= 0; --i)
					{
						x1 = (int)(i * showRightL / showLastF + 0.5);
						if (x1 == x)
						{
							m_showIndex[x] = i + 1;
							break;
						}
					}
				}
				else
				{
					int i2 = (int)((x + 1) * showLastL / showRightF + 0.5);
					int x2 = (int)(i2 * showRightL / showLastF + 0.5);
					if (x2 == x)
					{
						for (int i = i2 + 1; i < showCount; ++i)
						{
							x2 = (int)(i * showRightL / showLastF + 0.5);
							if (x2 > x)
							{
								m_showIndex[x] = i;
								break;
							}
						}
					}
					else
					{
						for (int i = i2 - 1; i >= 0; --i)
						{
							x2 = (int)(i * showRightL / showLastF + 0.5);
							if (x2 == x)
							{
								m_showIndex[x] = i + 1;
								break;
							}
						}
					}
				}
			}
			m_showIndex[showRight] = showCount;
		}
		else
		{
			m_showIndex = new int[showCount];
			for (int i = 1; i < showCount; ++i)
			{
				m_showIndex[i] = (int)(i * showRightL / showLastF + 0.5);
			}
			m_showIndex[0] = 0;
			m_showIndex[showLast] = (int)showRight;
		}
	}
}

//执行绘制处理。
void WROscilloDataViewElement::onPaint(QPainter& painter)
{
	WROscilloControl* chart = (WROscilloControl*)owner();
	WROscilloDataSource* dataSource = chart->dataSource();
	//初始化数据点索引
	initIndex();
	//初始化数据缓存
	if (!m_showBuffer)
	{
		m_showBuffer = new double[width() * 2];
	}
    //填充背景
    painter.fillRect(QRect(0, 0, width(), height()), backColor());
	//绘制网格线
	if (gridVisible())
    {
        painter.setPen(m_gridColor);

		int gridLeft = 0;
		int gridRight = width() - 1;
		int gridTop = 0;
		int gridBottom = height() - 1;
		//绘制横向网格
		long long valueMultiple = 1;
		double segValueSpan = chart->getDataValueSpan(height(), 20);
		while (segValueSpan < 1.0)
		{
			segValueSpan *= 10;
			valueMultiple *= 10;
		}
		long long segValueSpanL = (long long)(segValueSpan + 1);
		if (segValueSpanL > 10)
		{
			long long t1 = 100;
			long long t2 = 9;
			while (segValueSpanL > t1)
			{
				t1 *= 10;
				t2 = t2 * 10 + 9;
			}
			t1 /= 10;
			segValueSpanL = (segValueSpanL + t2) / t1 * t1;
		}
		double valueMultipleF = (double)valueMultiple;
		if (chart->showDataValueEnd() > 0)
		{
			long long showValueBeginL = chart->showDataValueBegin() > 0 ? (long long)(chart->showDataValueBegin() * valueMultiple + 0.5) : 0;
			long long segValueStartL = showValueBeginL % segValueSpanL;
			if (segValueStartL != 0)
			{
				showValueBeginL += segValueSpanL - segValueStartL;
			}
			long long showValueEndL = (long long)(chart->showDataValueEnd() * valueMultiple + 0.5);
			while (showValueBeginL < showValueEndL)
			{
				int yPos = chart->getDataValuePos(height(), showValueBeginL / valueMultipleF);
                painter.drawLine(gridLeft, yPos, gridRight, yPos);
				showValueBeginL += segValueSpanL;
			}
		}
		if (chart->showDataValueBegin() < 0)
		{
			long long showValueEndL = chart->showDataValueEnd() > 0 ? 0 : (long long)(chart->showDataValueEnd() * valueMultiple - 0.5);
			long long segValueStartL = showValueEndL % segValueSpanL;
			if (segValueStartL != 0)
			{
				showValueEndL -= segValueSpanL + segValueStartL;
			}
			long long showValueBeginL = (long long)(chart->showDataValueBegin() * valueMultiple - 0.5);
			while (showValueBeginL < showValueEndL)
			{
				int yPos = chart->getDataValuePos(height(), showValueEndL / valueMultipleF);
                painter.drawLine(gridLeft, yPos, gridRight, yPos);
				showValueEndL -= segValueSpanL;
			}
		}
		//绘制纵向网格
		int segPointCount = chart->getDataPointOffsetAt(width(), 20);
		if (segPointCount < 1)
		{
			segPointCount = 1;
		}
		else if (segPointCount < 10)
		{
			segPointCount = (segPointCount + 1) / 2 * 2;
		}
		else
		{
			int t1 = 100;
			int t2 = 9;
			while (segPointCount > t1)
			{
				t1 *= 10;
				t2 = t2 * 10 + 9;
			}
			t1 /= 10;
			segPointCount = (segPointCount + t2) / t1 * t1;
		}
		int showPointBegin;
		if (dataSource->points() < dataSource->capacity())
		{
			showPointBegin = (int)(dataSource->capacity() - dataSource->points());
			while (showPointBegin < chart->showDataPointBegin())
			{
				showPointBegin += segPointCount;
			}
		}
		else
		{
			showPointBegin = chart->showDataPointBegin();
			long long frameIndex = dataSource->points() - dataSource->capacity() + chart->showDataPointBegin();
			int segStart = (int)(frameIndex % segPointCount);
			if (segStart != 0)
			{
				showPointBegin += segPointCount - segStart;
			}
		}
		int showPointEnd = chart->showDataPointEnd();
		while (showPointBegin < showPointEnd)
		{
			int xPos = chart->getDataPointPos(width(), showPointBegin);
            painter.drawLine(xPos, gridTop, xPos, gridBottom);
			showPointBegin += segPointCount;
		}
	}
	//绘制零值线
	if (zeroVisible() && chart->showDataValueBegin() <= 0 && chart->showDataValueEnd() >= 0)
	{
        int yPos = chart->getDataValuePos(height(), 0);
        painter.setPen(m_zeroColor);
        painter.drawLine(0, yPos, width() - 1, yPos);
	}
	//执行线条绘制
	if (bufferInvalid())
	{
        createBuffer();
		bufferInvalid(false);
	}
	if (m_pointBuffer)
	{
        painter.setPen(m_lineColor);
        painter.drawPolyline(m_pointBuffer, m_pointLength);
    }
}
