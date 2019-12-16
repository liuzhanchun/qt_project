#include <WRCharting/WRSpectroDataViewElement.h>
#include <WRCharting/WRSpectroControl.h>
#include <WRCharting/WRText.h>

//初始化频谱图对象。
WRSpectroDataViewElement::WRSpectroDataViewElement(void)
	: m_backColor(4, 0, 0),
    m_gridColor(0, 53, 0)
{
    buffered(true);//设置具有缓存
    writeFlag(WRCHARTDATAVIEW_VSCALABLE, false);
    writeFlag(WRSPECTRODATAVIEW_GRIDVISIBLE, false);

	m_showBuffer = 0;
	m_showIndex = 0;
}
//清理当前对象所占用的相关资源。
WRSpectroDataViewElement::~WRSpectroDataViewElement(void)
{
	if (m_showIndex)
	{
		delete[] m_showIndex;
	}
	if (m_showBuffer)
	{
		delete[] m_showBuffer;
	}
}

//设置背景颜色。
void WRSpectroDataViewElement::setBackColor(WRColor value)
{
    if (m_backColor.change(value.red(), value.green(), value.blue()))
    {
        invalidate();
        doUpdate();
        emit backColorChanged(m_backColor);
    }
}
//设置网格颜色。
void WRSpectroDataViewElement::setGridColor(WRColor value)
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
void WRSpectroDataViewElement::setGridVisible(bool value)
{
    if (readFlag(WRSPECTRODATAVIEW_GRIDVISIBLE) != value)
    {
        writeFlag(WRSPECTRODATAVIEW_GRIDVISIBLE, value);
        invalidate();
        doUpdate();
        emit gridVisibleChanged(value);
    }
}

//设置背景颜色。
bool WRSpectroDataViewElement::backColor(WRColor value)
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
bool WRSpectroDataViewElement::gridColor(WRColor value)
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
bool WRSpectroDataViewElement::gridVisible(bool value)
{
	if (readFlag(WRSPECTRODATAVIEW_GRIDVISIBLE) != value)
	{
		writeFlag(WRSPECTRODATAVIEW_GRIDVISIBLE, value);
		invalidate();
		doUpdate();
        emit gridVisibleChanged(value);
		return true;
	}
	return false;
}

//当显示数据范围改变后调用此方法 。
void WRSpectroDataViewElement::onShowDataRangeChanged(void)
{
	invalidate();
}
//当显示数据点范围改变后调用此方法。
void WRSpectroDataViewElement::onShowDataPointRangeChanged(void)
{
    if (m_showIndex)
    {
        delete[] m_showIndex;
        m_showIndex = 0;
    }
}
//当显示数据值范围改变后调用此方法。
void WRSpectroDataViewElement::onShowDataValueRangeChanged(void)
{
	//add code here
}

//当大小改变后调用此方法。
void WRSpectroDataViewElement::onSizeChanged(void)
{
	//通知所有通道无效
	WRSpectroControl* chart = (WRSpectroControl*)owner();
	for(int i = 0; i < WRSPECTROCHANNELS; ++i)
	{
		chart->m_channels[i].invalidate();
	}
}
//当宽度改变后调用此方法。
void WRSpectroDataViewElement::onWidthChanged(void)
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
void WRSpectroDataViewElement::onHeightChanged(void)
{
	//add code here
}

//执行缩放处理。
bool WRSpectroDataViewElement::doZoom(const WRPoint& begPos, const WRPoint& endPos)
{
    WRSpectroControl* chart = (WRSpectroControl*)owner();
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
    return chart->changeShowDataRange(WRSpectroDataRange(showPointRange, showValueRange));
}
//执行移动处理。
bool WRSpectroDataViewElement::doMove(const WRPoint& begPos, const WRPoint& endPos)
{
    WRSpectroControl* chart = (WRSpectroControl*)owner();
    WRChartSampleRange showPointRange(chart->showDataPointRange());
    WRChartDValueRange showValueRange(chart->showDataValueRange());
    chart->doMouseMoveH(showPointRange, begPos.x(), endPos.x(), width());
    chart->doMouseMoveV(showValueRange, begPos.y(), endPos.y(), height());
    return chart->changeShowDataRange(WRSpectroDataRange(showPointRange, showValueRange));
}

//鼠标滚动处理。
bool WRSpectroDataViewElement::onMouseWheel(const QWheelEvent& e)
{
    WRSpectroControl* chart = (WRSpectroControl*)owner();
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
    return chart->changeShowDataRange(WRSpectroDataRange(showPointRange, showValueRange));
}

//初始化数据点索引。
void WRSpectroDataViewElement::initIndex(void)
{
	if (m_showIndex == 0)
	{
		WRSpectroControl* chart = (WRSpectroControl*)owner();

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
void WRSpectroDataViewElement::onPaint(QPainter& painter)
{
    WRSpectroControl* chart = (WRSpectroControl*)owner();
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
		int gridRight = this->width() - 1;
		int gridTop = 0;
		int gridBottom = this->height() - 1;
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
		long long showValueBeginL = (long long)((chart->showDataValueBegin() - chart->dataMinValue()) * valueMultiple + 0.5);
		long long showValueBeing2L = showValueBeginL;
		long long segValueStartL = showValueBeginL % segValueSpanL;
		if (segValueStartL != 0)
		{
			showValueBeginL += segValueSpanL - segValueStartL;
		}
		long long showValueEndL = (long long)((chart->showDataValueEnd() - chart->dataMinValue()) * valueMultiple + 0.5);
		double valueMultipleF = (double)valueMultiple;
		while (showValueBeginL < showValueEndL)
		{
			int yPos = chart->getDataValueOffsetPos(height(), (showValueBeginL - showValueBeing2L) / valueMultipleF);
            painter.drawLine(gridLeft, yPos, gridRight, yPos);
			showValueBeginL += segValueSpanL;
		}

		//绘制纵向网格
		int segPointCount = chart->getDataPointCount(width(), 20);
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
			while(segPointCount > t1)
			{
				t1 *= 10;
				t2 = t2 * 10 + 9;
			}
			t1 /= 10;
			segPointCount = (segPointCount + t2) / t1 * t1;
		}
		int showPointBegin = chart->showDataPointBegin();
		int segPointStart = showPointBegin % segPointCount;
		if (segPointStart != 0)
		{
			showPointBegin += segPointCount - segPointStart;
		}
		int showPointEnd = chart->showDataPointEnd();
		while(showPointBegin < showPointEnd)
		{
			int xPos = chart->getDataPointPos(width(), showPointBegin);
            painter.drawLine(xPos, gridTop, xPos, gridBottom);
			showPointBegin += segPointCount;
		}
	}
	//执行通道绘制
	for(int i = 0; i < WRSPECTROCHANNELS; ++i)
	{
		chart->m_channels[i].onPaint(painter);
	}
}
