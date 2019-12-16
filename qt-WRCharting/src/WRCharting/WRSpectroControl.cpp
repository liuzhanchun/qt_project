#include <WRCharting/WRSpectroControl.h>
#include "WRSpectroDataSourceT.h"

#define WRSPECTROCONTROL_AXISWIDTH		20
#define WRSPECTROCONTROL_SCROLLWIDTH	20

#define WRSPECTROFIRSTGAUGE (WRSpectroGaugeElement*)(m_hScroll->next())

//执行控件的初始化。
void WRSpectroControl::initialize(void)
{
	for(int i = 0; i < WRSPECTROCHANNELS; ++i)
	{
		WRSpectroChannel* channel = &m_channels[i];
		channel->m_owner = this;
		channel->m_index = i;
	}

    writeFlag(WRSPECTROCONTROL_HOLDSTATUS, false);
	m_backColor.update(98, 108, 123);

	m_vAxis = new WRSpectroVAxisElement();
	m_hAxis = new WRSpectroHAxisElement();
    m_vScroll = new WRSpectroVScrollElement();
    m_hScroll = new WRSpectroHScrollElement();
    m_dataView = new WRSpectroDataViewElement();

    addLast(m_dataView);
    addLast(m_vAxis);
    addLast(m_hAxis);
    addLast(m_vScroll);
    addLast(m_hScroll);
}
//清理当前对象所占用的相关资源。
WRSpectroControl::~WRSpectroControl(void)
{
	m_backSource->release();
	m_currSource->release();
}

//当布局时调用此方法。
void WRSpectroControl::onLayout(const WRRect& rect)
{
    WRChartControl::arrange(rect, m_hAxis, m_vAxis, m_hScroll, m_vScroll, m_dataView);
	//执行测量元旦布局
    WRSpectroGaugeElement* gauge = WRSPECTROFIRSTGAUGE;
    while (gauge)
    {
        gauge->arrange();
        gauge =(WRSpectroGaugeElement*) gauge->next();
    }
}

//键盘按下处理，如果需要重绘，则返回True。
bool WRSpectroControl::onKeyDown(const QKeyEvent& e)
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
				if (m_showDataRange.pointBegin() + m_showDataRange.pointCount() < m_currSource->points())
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
bool WRSpectroControl::onKeyUp(const QKeyEvent&)
{
	return false;
}

//执行绘制处理操作。
void WRSpectroControl::onPaint(QPainter& painter)
{
    painter.fillRect(rect(), m_backColor);//填充背景
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRSpectroControl::onPaintMouseFeedback(QPainter&)
{
	//add code here
}

//验证图形，如果需要重新绘制，则返回True。
bool WRSpectroControl::validate(void)
{
	bool changed = false;
	//验证数据源
	WRSpectroDataSource* dataSource = 0;
	if (!holdStatus())
	{
		WRSynch synch(m_mutex);
		if (m_backSource != m_currSource)
		{
			changed = true;
			dataSource = m_currSource;
			m_currSource = m_backSource;
			m_currSource->addRef();
			for(int i = 0; i < WRSPECTROCHANNELS; ++i)
			{
				m_currSource->channel(i)->validate();
				m_channels[i].invalidate();
			}
			m_dataView->invalidate();
		}
		else
		{
			for(int i = 0; i < WRSPECTROCHANNELS; ++i)
			{
				WRSpectroDataChannel* channel = m_currSource->channel(i);
				long version = channel->version();
				if (version != channel->validate())
				{
					changed = true;
					m_channels[i].invalidate();
				}
			}
			if (changed)
			{
				m_dataView->invalidate();
			}
		}
	}
	if (dataSource)
	{
		dataSource->release();        
        emit dataChanged();
        resetShowDataRange(WRSpectroDataRange(0, m_currSource->points(), m_currSource->minValue(), m_currSource->maxValue()));
		m_hAxis->invalidate();
		m_vAxis->invalidate();
	}
	//
    return changed;
}

//当显示数据范围改变后调用此方法 。
void WRSpectroControl::onShowDataRangeChanged()
{
    if (effect())
    {
        //WRSpectroGaugeElement* element = WRSPECTROFIRSTGAUGE;
        //while (element)
        //{
        //    if (element->type() == WRSpectroGaugeElement::Block)
        //    {
        //        element->arrange();
        //    }
        //    element =(WRSpectroGaugeElement*) element->next();
        //}
    }
	for(int i = 0; i < WRSPECTROCHANNELS; ++i)
	{
		m_channels[i].invalidate();
	}
    m_dataView->onShowDataRangeChanged();
    invalidate();
}
//当显示数据点范围改变后调用此方法。
void WRSpectroControl::onShowDataPointRangeChanged()
{
    if (effect())
    {
        WRSpectroGaugeElement* element = WRSPECTROFIRSTGAUGE;
        while (element)
        {
            if (element->type() == WRSpectroGaugeElement::DataPointLine)
            {
                element->arrange();
            }
            element =(WRSpectroGaugeElement*) element->next();
        }
    }
	m_hAxis->invalidate();
    m_dataView->onShowDataPointRangeChanged();
}
//当显示数据值范围改变后调用此方法。
void WRSpectroControl::onShowDataValueRangeChanged()
{
    if (effect())
    {
		WRSpectroGaugeElement* element = WRSPECTROFIRSTGAUGE;
		while (element)
		{
			if (element->type() == WRSpectroGaugeElement::DataValueLine)
			{
				element->arrange();
			}
			element =(WRSpectroGaugeElement*) element->next();
		}
    }
	m_vAxis->invalidate();
    m_dataView->onShowDataValueRangeChanged();
}

//设置显示数据范围。
void WRSpectroControl::setShowDataRange(const WRSpectroDataRange& value)
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
void WRSpectroControl::setShowDataPointRange(const WRChartSampleRange& value)
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
void WRSpectroControl::setShowDataValueRange(const WRChartDValueRange& value)
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
bool WRSpectroControl::showDataRange(const WRSpectroDataRange& value)
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
bool WRSpectroControl::showDataPointRange(const WRChartSampleRange& value)
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
bool WRSpectroControl::showDataValueRange(const WRChartDValueRange& value)
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

//初始化默认频谱图控件。
WRSpectroControl::WRSpectroControl(void)
{
	initialize();
	WRSpectroInitParams<unsigned char> initArgs(0, 255, 0, 101, true, 90000000, 100000000);
	m_backSource = new WRSpectroDataSourceT<unsigned char>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, 101);
	m_showDataRange.valueRange().update(0, 100);
}

//初始化频谱图控件，使用8位有符号整数数据源。
WRSpectroControl::WRSpectroControl(const WRSpectroInitParams<signed char>& initArgs)
{
	initialize();
	m_backSource = new WRSpectroDataSourceT<signed char>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}
//初始化频谱图控件，使用8位无符号整数数据源。
WRSpectroControl::WRSpectroControl(const WRSpectroInitParams<unsigned char>& initArgs)
{
	initialize();
	m_backSource = new WRSpectroDataSourceT<unsigned char>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}

//初始化频谱图控件，使用16位有符号整数数据源。
WRSpectroControl::WRSpectroControl(const WRSpectroInitParams<short>& initArgs)
{
	initialize();
	m_backSource = new WRSpectroDataSourceT<short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}
//初始化频谱图控件，使用16位无符号整数数据源。
WRSpectroControl::WRSpectroControl(const WRSpectroInitParams<unsigned short>& initArgs)
{
	initialize();
	m_backSource = new WRSpectroDataSourceT<unsigned short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}

//初始化频谱图控件，使用32位有符号整数数据源。
WRSpectroControl::WRSpectroControl(const WRSpectroInitParams<int>& initArgs)
{
	initialize();
	m_backSource = new WRSpectroDataSourceT<int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}
//初始化频谱图控件，使用32位无符号整数数据源。
WRSpectroControl::WRSpectroControl(const WRSpectroInitParams<unsigned int>& initArgs)
{
	initialize();
	m_backSource = new WRSpectroDataSourceT<unsigned int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}

//初始化频谱图控件，使用32位浮点数数据源。
WRSpectroControl::WRSpectroControl(const WRSpectroInitParams<float>& initArgs)
{
	initialize();
	m_backSource = new WRSpectroDataSourceT<float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}
//初始化频谱图控件，使用64位浮点数数据源。
WRSpectroControl::WRSpectroControl(const WRSpectroInitParams<double>& initArgs)
{
	initialize();
	m_backSource = new WRSpectroDataSourceT<double>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.valueRange().update(m_currSource->minValue(), m_currSource->maxValue());
}

//初始化频谱图控件，使用8位有符号整数数据源。该方法可以在多线程环境中使用。
void WRSpectroControl::initialize(const WRSpectroInitParams<signed char>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRSpectroDataSourceT<signed char>(initArgs);
}
//初始化频谱图控件，使用8位无符号整数数据源。该方法可以在多线程环境中使用。
void WRSpectroControl::initialize(const WRSpectroInitParams<unsigned char>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRSpectroDataSourceT<unsigned char>(initArgs);
}

//初始化频谱图控件，使用16位有符号整数数据源。该方法可以在多线程环境中使用。
void WRSpectroControl::initialize(const WRSpectroInitParams<short>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRSpectroDataSourceT<short>(initArgs);
}
//初始化频谱图控件，使用16位无符号整数数据源。该方法可以在多线程环境中使用。
void WRSpectroControl::initialize(const WRSpectroInitParams<unsigned short>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRSpectroDataSourceT<unsigned short>(initArgs);
}

//初始化频谱图控件，使用32位有符号整数数据源。该方法可以在多线程环境中使用。
void WRSpectroControl::initialize(const WRSpectroInitParams<int>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRSpectroDataSourceT<int>(initArgs);
}
//初始化频谱图控件，使用32位无符号整数数据源。该方法可以在多线程环境中使用。
void WRSpectroControl::initialize(const WRSpectroInitParams<unsigned int>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRSpectroDataSourceT<unsigned int>(initArgs);
}

//初始化频谱图控件，使用32位浮点数数据源。该方法可以在多线程环境中使用。
void WRSpectroControl::initialize(const WRSpectroInitParams<float>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRSpectroDataSourceT<float>(initArgs);
}
//初始化频谱图控件，使用64位浮点数数据源。该方法可以在多线程环境中使用。
void WRSpectroControl::initialize(const WRSpectroInitParams<double>& initArgs)
{	
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRSpectroDataSourceT<double>(initArgs);
}

//更改指定通道的数据，如果数据为NULL，则表示清空数据。
void WRSpectroControl::alterData(int index, const void* data)
{
	WRSynch synch(m_mutex);
    m_backSource->channel(index)->change(data);
}
//更改指定通道的数据，如果数据为NULL，则表示清空数据。
void WRSpectroControl::alterData(int index, const void* data, const int* markBuf, int markLen)
{
	WRSynch synch(m_mutex);
    m_backSource->channel(index)->change(data, markBuf, markLen);
}

//更改指定通道集合的数据, 
void WRSpectroControl::alterData(const void** dataArray, const int* channelArray, int channelCount)
{
	WRSynch synch(m_mutex);
	for(int i = 0; i < channelCount; ++i)
	{
        m_backSource->channel(channelArray[i])->change(dataArray[i]);
	}
}

//设置是否暂停数据。
void WRSpectroControl::setHoldStatus(bool value)
{
    if (value != readFlag(WRSPECTROCONTROL_HOLDSTATUS))
    {
        writeFlag(WRSPECTROCONTROL_HOLDSTATUS, value);
        emit holdStatusChanged(value);
    }
}
//设置背景颜色。
void WRSpectroControl::setBackColor(WRColor value)
{
    if (m_backColor.change(value.red(), value.green(), value.blue()))
    {
        invalidate();
        emit backColorChanged(m_backColor);
    }
}

//设置是否暂停数据。
bool WRSpectroControl::holdStatus(bool value)
{
    if (value != readFlag(WRSPECTROCONTROL_HOLDSTATUS))
    {
        writeFlag(WRSPECTROCONTROL_HOLDSTATUS, value);
        emit holdStatusChanged(value);
        return true;
    }
    return false;
}
//设置背景颜色。
bool WRSpectroControl::backColor(WRColor value)
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
WRSpectroDataPointLineElement* WRSpectroControl::addDataPointLine(int position)
{
    WRSpectroDataPointLineElement* child = new WRSpectroDataPointLineElement(position);
    {
        WRChartElement::addLast(child);
        child->arrange();
    }
    return child;
}
//添加数据值线条。
WRSpectroDataValueLineElement* WRSpectroControl::addDataValueLine(double position)
{
    WRSpectroDataValueLineElement* child = new WRSpectroDataValueLineElement(position);
    {
        WRChartElement::addLast(child);
        child->arrange();
    }
    return child;
}
////添加栅栏。
//WRSpectroFenceElement* WRSpectroControl::addFence(const WRSpectroDataRange& dataRange, int lineCount)
//{
//    WRSpectroFenceElement* child = new WRSpectroFenceElement(dataRange, lineCount);
//    {
//        WRChartElement::addLast(child);
//        child->arrange();
//    }
//    return child;
//}
////添加方块。
//WRSpectroBlockElement* WRSpectroControl::addBlock(const WRSpectroRange& range)
//{
//    WRSpectroBlockElement* child = new WRSpectroBlockElement(range);
//    {
//        WRChartElement::addLast(child);
//        child->arrange();
//    }
//    return child;
//}

//移除测量元素。
void WRSpectroControl::remove(WRSpectroGaugeElement** element)
{
    if ((*element)->parent() == this)
    {
        WRChartElement::remove(*element);
		delete *element;
		*element = 0;
        doUpdate();
    }
}
