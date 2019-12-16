#include <WRCharting/WRWaterfallControl.h>
#include "WRWaterfallDataSourceT.h"

#define WRWATERFALLAXIS_WIDTH 20
#define WRWATERFALLSCROLL_WIDTH 20

#define WRWATERFALLFIRSTGAUGE (WRWaterfallGaugeElement*)(m_hScroll->next())

//执行控件的初始化。
void WRWaterfallControl::initialize(void)
{	
    writeFlag(WRWATERFALLCONTROL_HOLDSTATUS, false);
	m_backColor.update(98, 108, 123);

	m_vAxis = new WRWaterfallVAxisElement();
	m_hAxis = new WRWaterfallHAxisElement();
    m_vScroll = new WRWaterfallVScrollElement();
    m_hScroll = new WRWaterfallHScrollElement();
    m_dataView = new WRWaterfallDataViewElement();

    addLast(m_dataView);
    addLast(m_vAxis);
    addLast(m_hAxis);
    addLast(m_vScroll);
    addLast(m_hScroll);
}
//清理当前对象所占用的相关资源。
WRWaterfallControl::~WRWaterfallControl(void)
{
	m_backSource->release();
	m_currSource->release();
}

//当布局时调用此方法。
void WRWaterfallControl::onLayout(const WRRect& rect)
{
    WRChartControl::arrange(rect, m_hAxis, m_vAxis, m_hScroll, m_vScroll, m_dataView);
	//执行测量元旦布局
    WRWaterfallGaugeElement* gauge = WRWATERFALLFIRSTGAUGE;
    while (gauge)
    {
        gauge->arrange();
        gauge =(WRWaterfallGaugeElement*) gauge->next();
    }
}

//键盘按下处理，如果需要重绘，则返回True。
bool WRWaterfallControl::onKeyDown(const QKeyEvent& e)
{
	if (((e.modifiers() & Qt::ControlModifier) == Qt::ControlModifier))
	{
		if (e.key() == Qt::Key_Left)
		{
			if (vertical())
			{
				if (m_dataView->width() >= m_showDataRange.pointCount())
				{
					if (m_showDataRange.pointBegin() > 0)
					{
						changeShowDataPointRange(WRChartSampleRange(m_showDataRange.pointBegin() - 1, m_showDataRange.pointCount()));
						return true;
					}
				}
				else
				{
					WRChartSampleRange showPointRange(m_showDataRange.pointRange());
					doVMouseMoveH(showPointRange, 1, 0, m_dataView->width());
					if (changeShowDataPointRange(showPointRange))
					{
						return true;
					}
				}
			}
			else
			{
				if (m_dataView->width() >= m_showDataRange.frameCount())
				{
					if (m_showDataRange.frameBegin() > 0)
					{
						changeShowDataFrameRange(WRChartSampleRange(m_showDataRange.frameBegin() - 1, m_showDataRange.frameCount()));
						return true;
					}
				}
				else
				{
					WRChartSampleRange showFrameRange(m_showDataRange.frameRange());
					doHMouseMoveH(showFrameRange, 1, 0, m_dataView->width());
					if (changeShowDataFrameRange(showFrameRange))
					{
						return true;
					}
				}
			}
		}
		else if (e.key() == Qt::Key_Right)
		{
			if (vertical())
			{
				if (m_dataView->width() >= m_showDataRange.pointCount())
				{
					if (m_showDataRange.pointBegin() + m_showDataRange.pointCount() < m_currSource->points())
					{
						changeShowDataPointRange(WRChartSampleRange(m_showDataRange.pointBegin() + 1, m_showDataRange.pointCount()));
						return true;
					}
				}
				else
				{
					WRChartSampleRange showPointRange(m_showDataRange.pointRange());
					doVMouseMoveH(showPointRange, 0, 1, m_dataView->width());
					if (changeShowDataPointRange(showPointRange))
					{
						return true;
					}
				}
			}
			else
			{
				if (m_dataView->width() >= m_showDataRange.frameCount())
				{
					if (m_showDataRange.frameBegin() + m_showDataRange.frameCount() < m_currSource->capacity())
					{
						changeShowDataFrameRange(WRChartSampleRange(m_showDataRange.frameBegin() + 1, m_showDataRange.frameCount()));
						return true;
					}
				}
				else
				{
					WRChartSampleRange showFrameRange(m_showDataRange.frameRange());
					doHMouseMoveH(showFrameRange, 0, 1, m_dataView->width());
					if (changeShowDataFrameRange(showFrameRange))
					{
						return true;
					}
				}
			}
		}
		else if (e.key() == Qt::Key_Up)
		{
			if (vertical())
			{
				if (m_dataView->height() >= m_showDataRange.frameCount())
				{
					if (m_showDataRange.frameBegin() > 0)
					{
						changeShowDataFrameRange(WRChartSampleRange(m_showDataRange.frameBegin() - 1, m_showDataRange.frameCount()));
						return true;
					}
				}
				else
				{
					WRChartSampleRange showFrameRange(m_showDataRange.frameRange());
					doVMouseMoveV(showFrameRange, 1, 0, m_dataView->height());
					if (changeShowDataFrameRange(showFrameRange))
					{
						return true;
					}
				}
			}
			else
			{
				if (m_dataView->height() >= m_showDataRange.pointCount())
				{
					if (m_showDataRange.pointBegin() + m_showDataRange.pointCount() < m_currSource->points())
					{
						changeShowDataPointRange(WRChartSampleRange(m_showDataRange.pointBegin() + 1, m_showDataRange.pointCount()));
						return true;
					}
				}
				else
				{
					WRChartSampleRange showPointRange(m_showDataRange.pointRange());
					doHMouseMoveV(showPointRange, 1, 0, m_dataView->height());
					if (changeShowDataPointRange(showPointRange))
					{
						return true;
					}
				}
			}
		}
		else if (e.key() == Qt::Key_Down)
		{
			if (vertical())
			{
				if (m_dataView->height() >= m_showDataRange.frameCount())
				{
					if (m_showDataRange.frameBegin() + m_showDataRange.frameCount() < m_currSource->capacity())
					{
						changeShowDataFrameRange(WRChartSampleRange(m_showDataRange.frameBegin() + 1, m_showDataRange.frameCount()));
						return true;
					}
				}
				else
				{
					WRChartSampleRange showFrameRange(m_showDataRange.frameRange());
					doVMouseMoveV(showFrameRange, 0, 1, m_dataView->height());
					if (changeShowDataFrameRange(showFrameRange))
					{
						return true;
					}
				}
			}
			else
			{
				if (m_dataView->height() >= m_showDataRange.pointCount())
				{
					if (m_showDataRange.pointBegin() > 0)
					{
						changeShowDataPointRange(WRChartSampleRange(m_showDataRange.pointBegin() - 1, m_showDataRange.pointCount()));
						return true;
					}
				}
				else
				{
					WRChartSampleRange showPointRange(m_showDataRange.pointRange());
					doHMouseMoveV(showPointRange, 0, 1, m_dataView->height());
					if (changeShowDataPointRange(showPointRange))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
//键盘释放处理，如果需要重绘，则返回True。
bool WRWaterfallControl::onKeyUp(const QKeyEvent&)
{
	return false;
}

//执行绘制处理操作。
void WRWaterfallControl::onPaint(QPainter& painter)
{
    painter.fillRect(rect(), m_backColor);
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRWaterfallControl::onPaintMouseFeedback(QPainter&)
{
	//add code here
}

//验证图形，如果需要重新绘制，则返回True。
bool WRWaterfallControl::validate(void)
{
	bool changed = false;
	//验证数据源
	WRWaterfallDataSource* dataSource = 0;
	if (!holdStatus())
	{
		WRSynch synch(m_mutex);
		if (m_backSource != m_currSource)
		{
			changed = true;
			dataSource = m_currSource;
			m_currSource = m_backSource;
			m_currSource->addRef();
			m_currSource->validate();
			m_dataView->invalidate();
			if (vertical())
			{
				m_vAxis->invalidate();
			}
			else
			{
				m_hAxis->invalidate();
			}
		}
		else
		{
			long long frames = m_currSource->frames();
			if (m_currSource->validate() != frames)
			{
				changed = true;
				m_dataView->invalidate();
				if (vertical())
				{
					m_vAxis->invalidate();
				}
				else
				{
					m_hAxis->invalidate();
				}
			}
		}
	}
	if (dataSource)
	{
        dataSource->release();
        emit dataChanged();
        resetShowDataRange(WRWaterfallDataRange(0, m_currSource->points(), 0, m_currSource->capacity()));
		m_hAxis->invalidate();
		m_vAxis->invalidate();
	}

    return changed;
}

//当显示数据范围改变后调用此方法 。
void WRWaterfallControl::onShowDataRangeChanged()
{
    if (effect())
    {
        //WRWaterfallGaugeElement* element = WRWATERFALLFIRSTGAUGE;
        //while (element)
        //{
        //    if (element->type() == WRWaterfallGaugeElement::Block)
        //    {
        //        element->arrange();
        //    }
        //    element =(WRWaterfallGaugeElement*) element->next();
        //}
    }
    m_dataView->onShowDataRangeChanged();
    invalidate();
}
//当显示数据点范围改变后调用此方法。
void WRWaterfallControl::onShowDataPointRangeChanged()
{
    if (effect())
    {
        WRWaterfallGaugeElement* element = WRWATERFALLFIRSTGAUGE;
        while (element)
        {
			if (element->type() == WRWaterfallGaugeElement::DataPointLine)
            {
                element->arrange();
            }
            element =(WRWaterfallGaugeElement*) element->next();
        }
    }
	if (vertical())
	{
		m_hAxis->invalidate();
	}
	else
	{
		m_vAxis->invalidate();
	}
    m_dataView->onShowDataPointRangeChanged();
}
//当显示数据帧范围改变后调用此方法。
void WRWaterfallControl::onShowDataFrameRangeChanged()
{
    if (effect())
    {
        WRWaterfallGaugeElement* element = WRWATERFALLFIRSTGAUGE;
        while (element)
        {
			if (element->type() == WRWaterfallGaugeElement::DataFrameLine)
            {
                element->arrange();
            }
            element =(WRWaterfallGaugeElement*) element->next();
        }
    }
	if (vertical())
	{
		m_vAxis->invalidate();
	}
	else
	{
		m_hAxis->invalidate();
	}
    m_dataView->onShowDataFrameRangeChanged();
}

//设置显示数据范围。
void WRWaterfallControl::setShowDataRange(const WRWaterfallDataRange& value)
{
    bool change = false;
    if (m_showDataRange.pointRange(value.pointRange()))
    {
        onShowDataPointRangeChanged();
        emit showDataPointRangeChanged(m_showDataRange.pointRange());
        change = true;
    }
    if (m_showDataRange.frameRange(value.frameRange()))
    {
        onShowDataFrameRangeChanged();
        emit showDataFrameRangeChanged(m_showDataRange.frameRange());
        change = true;
    }
    if (change)
    {
        onShowDataRangeChanged();
        emit showDataRangeChanged(m_showDataRange);
    }
}
//设置数据点显示数据范围。
void WRWaterfallControl::setShowDataPointRange(const WRChartSampleRange& value)
{
    if (m_showDataRange.pointRange(value))
    {
        onShowDataPointRangeChanged();
        onShowDataRangeChanged();
        emit showDataPointRangeChanged(m_showDataRange.pointRange());
        emit showDataRangeChanged(m_showDataRange);
    }
}
//设置数据帧显示数据范围。
void WRWaterfallControl::setShowDataFrameRange(const WRChartSampleRange& value)
{
    if (m_showDataRange.frameRange(value))
    {
        onShowDataFrameRangeChanged();
        onShowDataRangeChanged();
        emit showDataFrameRangeChanged(m_showDataRange.frameRange());
        emit showDataRangeChanged(m_showDataRange);
    }
}

//设置显示数据范围。
bool WRWaterfallControl::showDataRange(const WRWaterfallDataRange& value)
{
    bool change = false;
    if (m_showDataRange.pointRange(value.pointRange()))
    {
        onShowDataPointRangeChanged();
        emit showDataPointRangeChanged(m_showDataRange.pointRange());
        change = true;
    }
    if (m_showDataRange.frameRange(value.frameRange()))
    {
        onShowDataFrameRangeChanged();
        emit showDataFrameRangeChanged(m_showDataRange.frameRange());
        change = true;
    }
    if (change)
    {
        onShowDataRangeChanged();
        emit showDataRangeChanged(m_showDataRange);
        return true;
    }
    return false;
}
//设置数据点显示数据范围。
bool WRWaterfallControl::showDataPointRange(const WRChartSampleRange& value)
{
    if (m_showDataRange.pointRange(value))
    {
        onShowDataPointRangeChanged();
        onShowDataRangeChanged();
        emit showDataPointRangeChanged(m_showDataRange.pointRange());
        emit showDataRangeChanged(m_showDataRange);
        return true;
    }
    return false;
}
//设置数据帧显示数据范围。
bool WRWaterfallControl::showDataFrameRange(const WRChartSampleRange& value)
{
    if (m_showDataRange.frameRange(value))
    {
        onShowDataFrameRangeChanged();
        onShowDataRangeChanged();
        emit showDataFrameRangeChanged(m_showDataRange.frameRange());
        emit showDataRangeChanged(m_showDataRange);
        return true;
    }
    return false;
}

//初始化默认瀑布图控件。
WRWaterfallControl::WRWaterfallControl(bool vertical)
{
	writeFlag(WRWATERFALLCONTROL_VERTICAL, vertical);
	initialize();
	WRWaterfallInitParams<unsigned char> initArgs(0, 255, 0, 101, true, 90000000, 100000000, 10, 100);
	m_backSource = new WRWaterfallDataSourceT<unsigned char>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, 101);
	m_showDataRange.frameRange().update(0, 100);
}

//初始化瀑布图控件，使用8位有符号整数数据源。
WRWaterfallControl::WRWaterfallControl(const WRWaterfallInitParams<signed char>& initArgs, bool vertical)
{
	writeFlag(WRWATERFALLCONTROL_VERTICAL, vertical);
	initialize();
	m_backSource = new WRWaterfallDataSourceT<signed char>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.frameRange().update(0, m_currSource->capacity());
}
//初始化瀑布图控件，使用8位无符号整数数据源。
WRWaterfallControl::WRWaterfallControl(const WRWaterfallInitParams<unsigned char>& initArgs, bool vertical)
{
	writeFlag(WRWATERFALLCONTROL_VERTICAL, vertical);
	initialize();
	m_backSource = new WRWaterfallDataSourceT<unsigned char>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.frameRange().update(0, m_currSource->capacity());
}

//初始化瀑布图控件，使用16位有符号整数数据源。
WRWaterfallControl::WRWaterfallControl(const WRWaterfallInitParams<short>& initArgs, bool vertical)
{
	writeFlag(WRWATERFALLCONTROL_VERTICAL, vertical);
	initialize();
	m_backSource = new WRWaterfallDataSourceT<short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.frameRange().update(0, m_currSource->capacity());
}
//初始化瀑布图控件，使用16位无符号整数数据源。
WRWaterfallControl::WRWaterfallControl(const WRWaterfallInitParams<unsigned short>& initArgs, bool vertical)
{
	writeFlag(WRWATERFALLCONTROL_VERTICAL, vertical);
	initialize();
	m_backSource = new WRWaterfallDataSourceT<unsigned short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.frameRange().update(0, m_currSource->capacity());
}

//初始化瀑布图控件，使用32位有符号整数数据源。
WRWaterfallControl::WRWaterfallControl(const WRWaterfallInitParams<int>& initArgs, bool vertical)
{
	writeFlag(WRWATERFALLCONTROL_VERTICAL, vertical);
	initialize();
	m_backSource = new WRWaterfallDataSourceT<int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.frameRange().update(0, m_currSource->capacity());
}
//初始化瀑布图控件，使用32位无符号整数数据源。
WRWaterfallControl::WRWaterfallControl(const WRWaterfallInitParams<unsigned int>& initArgs, bool vertical)
{
	writeFlag(WRWATERFALLCONTROL_VERTICAL, vertical);
	initialize();
	m_backSource = new WRWaterfallDataSourceT<unsigned int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.frameRange().update(0, m_currSource->capacity());
}

//初始化瀑布图控件，使用32位浮点数数据源。
WRWaterfallControl::WRWaterfallControl(const WRWaterfallInitParams<float>& initArgs, bool vertical)
{
	writeFlag(WRWATERFALLCONTROL_VERTICAL, vertical);
	initialize();
	m_backSource = new WRWaterfallDataSourceT<float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.frameRange().update(0, m_currSource->capacity());
}
//初始化瀑布图控件，使用64位浮点数数据源。
WRWaterfallControl::WRWaterfallControl(const WRWaterfallInitParams<double>& initArgs, bool vertical)
{
	writeFlag(WRWATERFALLCONTROL_VERTICAL, vertical);
	initialize();
	m_backSource = new WRWaterfallDataSourceT<double>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.frameRange().update(0, m_currSource->capacity());
}

//初始化瀑布图控件，使用8位有符号整数数据源。该方法可以在多线程环境中使用。
void WRWaterfallControl::initialize(const WRWaterfallInitParams<signed char>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRWaterfallDataSourceT<signed char>(initArgs);
}
//初始化瀑布图控件，使用8位无符号整数数据源。该方法可以在多线程环境中使用。
void WRWaterfallControl::initialize(const WRWaterfallInitParams<unsigned char>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRWaterfallDataSourceT<unsigned char>(initArgs);
}

//初始化瀑布图控件，使用16位有符号整数数据源。该方法可以在多线程环境中使用。
void WRWaterfallControl::initialize(const WRWaterfallInitParams<short>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRWaterfallDataSourceT<short>(initArgs);
}
//初始化瀑布图控件，使用16位无符号整数数据源。该方法可以在多线程环境中使用。
void WRWaterfallControl::initialize(const WRWaterfallInitParams<unsigned short>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRWaterfallDataSourceT<unsigned short>(initArgs);
}

//初始化瀑布图控件，使用32位有符号整数数据源。该方法可以在多线程环境中使用。
void WRWaterfallControl::initialize(const WRWaterfallInitParams<int>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRWaterfallDataSourceT<int>(initArgs);
}
//初始化瀑布图控件，使用32位无符号整数数据源。该方法可以在多线程环境中使用。
void WRWaterfallControl::initialize(const WRWaterfallInitParams<unsigned int>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRWaterfallDataSourceT<unsigned int>(initArgs);
}

//初始化瀑布图控件，使用32位浮点数数据源。该方法可以在多线程环境中使用。
void WRWaterfallControl::initialize(const WRWaterfallInitParams<float>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRWaterfallDataSourceT<float>(initArgs);
}
//初始化瀑布图控件，使用64位浮点数数据源。该方法可以在多线程环境中使用。
void WRWaterfallControl::initialize(const WRWaterfallInitParams<double>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRWaterfallDataSourceT<double>(initArgs);
}

//清除数据。
void WRWaterfallControl::clearData(void)
{
    WRSynch synch(m_mutex);
    m_backSource->clear();
}
//写入数据。该方法可以在多线程环境中使用。
void WRWaterfallControl::writeData(const void* specBuffer, const long long* timeBuffer, int dataFrames)
{
	WRSynch synch(m_mutex);
	m_backSource->append(specBuffer, timeBuffer, dataFrames);
}

//设置是否暂停数据。
void WRWaterfallControl::setHoldStatus(bool value)
{
    if (value != readFlag(WRWATERFALLCONTROL_HOLDSTATUS))
    {
        writeFlag(WRWATERFALLCONTROL_HOLDSTATUS, value);
        emit holdStatusChanged(value);
    }
}
//设置是否暂停数据。
void WRWaterfallControl::setVertical(bool value)
{
    if (value != readFlag(WRWATERFALLCONTROL_VERTICAL))
    {
        writeFlag(WRWATERFALLCONTROL_VERTICAL, value);
        m_hAxis->invalidate();
        m_vAxis->invalidate();
        m_dataView->onVerticalChanged();
        if (effect())
        {
            WRWaterfallGaugeElement* element = WRWATERFALLFIRSTGAUGE;
            while (element)
            {
                element->arrange();
                element =(WRWaterfallGaugeElement*) element->next();
            }
            invalidate();
        }
        emit verticalChanged(value);
    }
}
//设置背景颜色。
void WRWaterfallControl::setBackColor(WRColor value)
{
    if (m_backColor.change(value.red(), value.green(), value.blue()))
    {
        invalidate();
        emit backColorChanged(m_backColor);
    }
}


//设置是否暂停数据。
bool WRWaterfallControl::holdStatus(bool value)
{
    if (value != readFlag(WRWATERFALLCONTROL_HOLDSTATUS))
    {
        writeFlag(WRWATERFALLCONTROL_HOLDSTATUS, value);
        emit holdStatusChanged(value);
        return true;
    }
    return false;
}
//设置是否暂停数据。
bool WRWaterfallControl::vertical(bool value)
{
    if (value != readFlag(WRWATERFALLCONTROL_VERTICAL))
    {
        writeFlag(WRWATERFALLCONTROL_VERTICAL, value);
		m_hAxis->invalidate();
		m_vAxis->invalidate();
		m_dataView->onVerticalChanged();
		if (effect())
		{
            WRWaterfallGaugeElement* element = WRWATERFALLFIRSTGAUGE;
            while (element)
            {
                element->arrange();
                element =(WRWaterfallGaugeElement*) element->next();
            }
			invalidate();
		}
        emit verticalChanged(value);
		return true;
    }
	return false;
}
//设置背景颜色。
bool WRWaterfallControl::backColor(WRColor value)
{
	if (m_backColor.change(value.red(), value.green(), value.blue()))
	{
		invalidate();
        emit backColorChanged(m_backColor);
		return true;
	}
	return false;
}

//添加数据帧线条。
WRWaterfallDataFrameLineElement* WRWaterfallControl::addDataFrameLine(int position)
{
    WRWaterfallDataFrameLineElement* child = new WRWaterfallDataFrameLineElement(position);
    {
        WRChartElement::addLast(child);
        child->arrange();
    }
    return child;
}
//添加数据点线条。
WRWaterfallDataPointLineElement* WRWaterfallControl::addDataPointLine(int position)
{
    WRWaterfallDataPointLineElement* child = new WRWaterfallDataPointLineElement(position);
    {
        WRChartElement::addLast(child);
        child->arrange();
    }
    return child;
}

//移除测量元素。
void WRWaterfallControl::remove(WRWaterfallGaugeElement** element)
{
    if ((*element)->parent() == this)
    {
        WRChartElement::remove(*element);
		delete *element;
		*element = 0;
        doUpdate();
    }
}
