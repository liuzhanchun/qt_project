#include <WRCharting/WROscilloControl.h>
#include "WROscilloDataSourceT.h"

#define WROSCILLOFIRSTGAUGE (WROscilloGaugeElement*)(m_hScroll->next())

//执行控件的初始化。
void WROscilloControl::initialize(void)
{
    writeFlag(WROSCILLOCONTROL_HOLDSTATUS, false);
	m_backColor.update(98, 108, 123);

	m_vAxis = new WROscilloVAxisElement();
	m_hAxis = new WROscilloHAxisElement();
    m_vScroll = new WROscilloVScrollElement();
    m_hScroll = new WROscilloHScrollElement();
    m_dataView = new WROscilloDataViewElement();

    addLast(m_dataView);
    addLast(m_vAxis);
    addLast(m_hAxis);
    addLast(m_vScroll);
    addLast(m_hScroll);
}
//清理当前对象所占用的相关资源。
WROscilloControl::~WROscilloControl(void)
{
	m_backSource->release();
	m_currSource->release();
}

//当布局时调用此方法。
void WROscilloControl::onLayout(const WRRect& rect)
{
    WRChartControl::arrange(rect, m_hAxis, m_vAxis, m_hScroll, m_vScroll, m_dataView);
	//执行测量元旦布局
    WROscilloGaugeElement* gauge = WROSCILLOFIRSTGAUGE;
    while (gauge)
    {
        gauge->arrange();
        gauge =(WROscilloGaugeElement*) gauge->next();
    }
}

//键盘按下处理，如果需要重绘，则返回True。
bool WROscilloControl::onKeyDown(const QKeyEvent& e)
{
	if (((e.modifiers() & Qt::ControlModifier) == Qt::ControlModifier))
	{
		if (e.key() == Qt::Key_Left)
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
				doMouseMoveH(showPointRange, 1, 0, m_dataView->width());
				if (changeShowDataPointRange(showPointRange))
				{
					return true;
				}
			}
		}
		else if (e.key() == Qt::Key_Right)
		{
			if (m_dataView->width() >= m_showDataRange.pointCount())
			{
				if (m_showDataRange.pointBegin() + m_showDataRange.pointCount() < m_currSource->capacity())
				{
					changeShowDataPointRange(WRChartSampleRange(m_showDataRange.pointBegin() + 1, m_showDataRange.pointCount()));
					return true;
				}
			}
			else
			{
				WRChartSampleRange showPointRange(m_showDataRange.pointRange());
				doMouseMoveH(showPointRange, 0, 1, m_dataView->width());
				if (changeShowDataPointRange(showPointRange))
				{
					return true;
				}
			}
		}
		else if (e.key() == Qt::Key_Up)
		{
			WRChartDValueRange showValueRange(m_showDataRange.valueRange());
			doMouseMoveV(showValueRange, 1, 0, m_dataView->height());
			if (changeShowDataValueRange(showValueRange))
			{
				return true;
			}
		}
		else if (e.key() == Qt::Key_Down)
		{
			WRChartDValueRange showValueRange(m_showDataRange.valueRange());
			doMouseMoveV(showValueRange, 0, 1, m_dataView->height());
			if (changeShowDataValueRange(showValueRange))
			{
				return true;
			}
		}
	}
	return false;
}
//键盘释放处理，如果需要重绘，则返回True。
bool WROscilloControl::onKeyUp(const QKeyEvent&)
{
	return false;
}

//执行绘制处理操作。
void WROscilloControl::onPaint(QPainter& painter)
{
    painter.fillRect(rect(), m_backColor);//填充背景
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WROscilloControl::onPaintMouseFeedback(QPainter&)
{
	//add code here
}

//验证图形，如果需要重新绘制，则返回True。
bool WROscilloControl::validate(void)
{
	bool changed = false;
	//验证数据源
	WROscilloDataSource* dataSource = 0;
	if (!holdStatus())
	{
		WRSynch synch(m_mutex);
		if (m_backSource != m_currSource)
		{
			changed = true;
			dataSource = m_currSource;
			m_currSource = m_backSource;
			m_currSource->addRef();
			m_dataView->invalidate();
			m_dataView->invalidateBuffer();
		}
		else
		{
            long version = m_currSource->version();
			if (version != m_currSource->validate())
			{
				changed = true;
				m_dataView->invalidateBuffer();
				m_dataView->invalidate();
				m_hAxis->invalidate();
			}
		}
	}
	if (dataSource)
	{
		dataSource->release();
        emit dataChanged();
        resetShowDataRange(WROscilloDataRange(0, m_currSource->capacity(), m_currSource->minValue(), m_currSource->maxValue()));
		m_hAxis->invalidate();
		m_vAxis->invalidate();
    }
	//
    return changed;
}

//当显示数据范围改变后调用此方法 。
void WROscilloControl::onShowDataRangeChanged()
{
    if (effect())
    {
        //WROscilloGaugeElement* element = WROSCILLOFIRSTGAUGE;
        //while (element)
        //{
        //    if (element->type() == WROscilloGaugeElement::Block)
        //    {
        //        element->arrange();
        //    }
        //    element =(WROscilloGaugeElement*) element->next();
        //}
    }
    m_dataView->onShowDataRangeChanged();
    invalidate();
}
//当显示数据点范围改变后调用此方法。
void WROscilloControl::onShowDataPointRangeChanged()
{
    if (effect())
    {
        WROscilloGaugeElement* element = WROSCILLOFIRSTGAUGE;
        while (element)
        {
            if (element->type() == WROscilloGaugeElement::DataPointLine)
            {
                element->arrange();
            }
            element =(WROscilloGaugeElement*) element->next();
        }
    }
	m_hAxis->invalidate();
    m_dataView->onShowDataPointRangeChanged();
}
//当显示数据值范围改变后调用此方法。
void WROscilloControl::onShowDataValueRangeChanged()
{
    if (effect())
    {
		WROscilloGaugeElement* element = WROSCILLOFIRSTGAUGE;
		while (element)
		{
			if (element->type() == WROscilloGaugeElement::DataValueLine)
			{
				element->arrange();
			}
			element =(WROscilloGaugeElement*) element->next();
		}
    }
	m_vAxis->invalidate();
    m_dataView->onShowDataValueRangeChanged();
}

//设置显示数据范围。
void WROscilloControl::setShowDataRange(const WROscilloDataRange& value)
{
    bool change = false;
    if (m_showDataRange.pointRange(value.pointRange()))
    {
        onShowDataPointRangeChanged();
        emit showDataPointRangeChanged(m_showDataRange.pointRange());
        change = true;
    }
    if (m_showDataRange.valueRange(value.valueRange()))
    {
        onShowDataValueRangeChanged();
        emit showDataValueRangeChanged(m_showDataRange.valueRange());
        change = true;
    }
    if (change)
    {
        onShowDataRangeChanged();
        emit showDataRangeChanged(m_showDataRange);
    }
}
//设置数据点显示数据范围。
void WROscilloControl::setShowDataPointRange(const WRChartSampleRange& value)
{
    if (m_showDataRange.pointRange(value))
    {
        onShowDataPointRangeChanged();
        onShowDataRangeChanged();
        emit showDataPointRangeChanged(m_showDataRange.pointRange());
        emit showDataRangeChanged(m_showDataRange);
    }
}
//设置数据值显示数据范围。
void WROscilloControl::setShowDataValueRange(const WRChartDValueRange& value)
{
    if (m_showDataRange.valueRange(value))
    {
        onShowDataValueRangeChanged();
        onShowDataRangeChanged();
        emit showDataValueRangeChanged(m_showDataRange.valueRange());
        emit showDataRangeChanged(m_showDataRange);
    }
}

//设置显示数据范围。
bool WROscilloControl::showDataRange(const WROscilloDataRange& value)
{
    bool change = false;
    if (m_showDataRange.pointRange(value.pointRange()))
    {
        onShowDataPointRangeChanged();
        emit showDataPointRangeChanged(m_showDataRange.pointRange());
        change = true;
    }
    if (m_showDataRange.valueRange(value.valueRange()))
    {
        onShowDataValueRangeChanged();
        emit showDataValueRangeChanged(m_showDataRange.valueRange());
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
bool WROscilloControl::showDataPointRange(const WRChartSampleRange& value)
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
//设置数据值显示数据范围。
bool WROscilloControl::showDataValueRange(const WRChartDValueRange& value)
{
    if (m_showDataRange.valueRange(value))
    {
        onShowDataValueRangeChanged();
        onShowDataRangeChanged();
        emit showDataValueRangeChanged(m_showDataRange.valueRange());
        emit showDataRangeChanged(m_showDataRange);
        return true;
    }
    return false;
}

//初始化默认波形图控件。
WROscilloControl::WROscilloControl(void)
{
	initialize();
	WROscilloInitParams<short> initArgs(-32000, 32000, 8000,  4000, 16000);
	m_backSource = new WROscilloDataSourceT<short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, 16000);
	m_showDataRange.valueRange().update(-32000, 32000);
}

//初始化波形图控件，使用8位有符号整数数据源。
WROscilloControl::WROscilloControl(const WROscilloInitParams<signed char>& initArgs)
{
	initialize();
	m_backSource = new WROscilloDataSourceT<signed char>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->capacity());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}
//初始化波形图控件，使用16位有符号整数数据源。
WROscilloControl::WROscilloControl(const WROscilloInitParams<short>& initArgs)
{
	initialize();
	m_backSource = new WROscilloDataSourceT<short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->capacity());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}
//初始化波形图控件，使用32位有符号整数数据源。
WROscilloControl::WROscilloControl(const WROscilloInitParams<int>& initArgs)
{
	initialize();
	m_backSource = new WROscilloDataSourceT<int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->capacity());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}
//初始化波形图控件，使用32位浮点数数据源。
WROscilloControl::WROscilloControl(const WROscilloInitParams<float>& initArgs)
{
	initialize();
	m_backSource = new WROscilloDataSourceT<float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->capacity());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}
//初始化波形图控件，使用64位浮点数数据源。
WROscilloControl::WROscilloControl(const WROscilloInitParams<double>& initArgs)
{
	initialize();
	m_backSource = new WROscilloDataSourceT<double>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->capacity());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}

//初始化波形图控件，使用8位有符号整数数据源。该方法可以在多线程环境中使用。
void WROscilloControl::initialize(const WROscilloInitParams<signed char>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WROscilloDataSourceT<signed char>(initArgs);
}
//初始化波形图控件，使用16位有符号整数数据源。该方法可以在多线程环境中使用。
void WROscilloControl::initialize(const WROscilloInitParams<short>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WROscilloDataSourceT<short>(initArgs);
}
//初始化波形图控件，使用32位有符号整数数据源。该方法可以在多线程环境中使用。
void WROscilloControl::initialize(const WROscilloInitParams<int>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WROscilloDataSourceT<int>(initArgs);
}
//初始化波形图控件，使用32位浮点数数据源。该方法可以在多线程环境中使用。
void WROscilloControl::initialize(const WROscilloInitParams<float>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WROscilloDataSourceT<float>(initArgs);
}
//初始化波形图控件，使用64位浮点数数据源。该方法可以在多线程环境中使用。
void WROscilloControl::initialize(const WROscilloInitParams<double>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WROscilloDataSourceT<double>(initArgs);
}

//清除数据。
void WROscilloControl::clearData(void)
{
    WRSynch synch(m_mutex);
    m_backSource->clear();
}
//写入的数据。
void WROscilloControl::writeData(const void* data, int size, long long time)
{
	WRSynch synch(m_mutex);
    m_backSource->append(data, size, time);
}

//设置是否暂停数据。
void WROscilloControl::setHoldStatus(bool value)
{
    if (value != readFlag(WROSCILLOCONTROL_HOLDSTATUS))
    {
        writeFlag(WROSCILLOCONTROL_HOLDSTATUS, value);
        emit holdStatusChanged(value);
    }
}
//设置背景颜色。
void WROscilloControl::setBackColor(WRColor value)
{
    if (m_backColor.change(value.red(), value.green(), value.blue()))
    {
        invalidate();
        emit backColorChanged(m_backColor);
    }
}

//设置是否暂停数据。
bool WROscilloControl::holdStatus(bool value)
{
    if (value != readFlag(WROSCILLOCONTROL_HOLDSTATUS))
    {
        writeFlag(WROSCILLOCONTROL_HOLDSTATUS, value);
        emit holdStatusChanged(value);
        return true;
    }
    return false;
}
//设置背景颜色。
bool WROscilloControl::backColor(WRColor value)
{
	if (m_backColor.change(value.red(), value.green(), value.blue()))
	{
		invalidate();
        emit backColorChanged(m_backColor);
		return true;
	}
	return false;
}

//添加数据点线条。
WROscilloDataPointLineElement* WROscilloControl::addDataPointLine(int position)
{
    WROscilloDataPointLineElement* child = new WROscilloDataPointLineElement(position);
    {
        WRChartElement::addLast(child);
        child->arrange();
    }
    return child;
}
//添加数据值线条。
WROscilloDataValueLineElement* WROscilloControl::addDataValueLine(double position)
{
    WROscilloDataValueLineElement* child = new WROscilloDataValueLineElement(position);
    {
        WRChartElement::addLast(child);
        child->arrange();
    }
    return child;
}

//移除测量元素。
void WROscilloControl::remove(WROscilloGaugeElement** element)
{
    if ((*element)->parent() == this)
    {
        WRChartElement::remove(*element);
		delete *element;
		*element = 0;
        doUpdate();
    }
}
