#include <WRCharting/WRDirMapControl.h>
#include "WRDirMapDataSourceT.h"

#define WRDIRMAPFIRSTGAUGE (WRDirMapGaugeElement*)(m_hScroll->next())

//执行控件的初始化。
void WRDirMapControl::initialize(void)
{	
    writeFlag(WRDIRMAPCONTROL_HOLDSTATUS, false);
	m_backColor.update(98, 108, 123);
	m_dataProcMethod = ShowMaxValue;

	m_vAxis = new WRDirMapVAxisElement();
	m_hAxis = new WRDirMapHAxisElement();
    m_vScroll = new WRDirMapVScrollElement();
    m_hScroll = new WRDirMapHScrollElement();
    m_dataView = new WRDirMapDataViewElement();

    addLast(m_dataView);
    addLast(m_vAxis);
    addLast(m_hAxis);
    addLast(m_vScroll);
    addLast(m_hScroll);
}
//清理当前对象所占用的相关资源。
WRDirMapControl::~WRDirMapControl(void)
{
	m_backSource->release();
	m_currSource->release();
}

//当布局时调用此方法。
void WRDirMapControl::onLayout(const WRRect& rect)
{
    WRChartControl::arrange(rect, m_hAxis, m_vAxis, m_hScroll, m_vScroll, m_dataView);
	//执行测量元旦布局
    WRDirMapGaugeElement* gauge = WRDIRMAPFIRSTGAUGE;
    while (gauge)
    {
        gauge->arrange();
        gauge =(WRDirMapGaugeElement*) gauge->next();
    }
}

//键盘按下处理，如果需要重绘，则返回True。
bool WRDirMapControl::onKeyDown(const QKeyEvent& e)
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
			WRChartDValueRange showAngleRange(m_showDataRange.angleRange());
			doMouseMoveV(showAngleRange, 1, 0, m_dataView->height());
			if (changeShowDataAngleRange(showAngleRange))
			{
				return true;
			}
		}
        else if (e.key() == Qt::Key_Down)
		{
			WRChartDValueRange showAngleRange(m_showDataRange.angleRange());
			doMouseMoveV(showAngleRange, 0, 1, m_dataView->height());
			if (changeShowDataAngleRange(showAngleRange))
			{
				return true;
			}
		}
	}
	return false;
}
//键盘释放处理，如果需要重绘，则返回True。
bool WRDirMapControl::onKeyUp(const QKeyEvent&)
{
	return false;
}

//执行绘制处理操作。
void WRDirMapControl::onPaint(QPainter& painter)
{
    painter.fillRect(rect(), m_backColor);//填充背景
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRDirMapControl::onPaintMouseFeedback(QPainter&)
{
	//add code here
}

//验证图形，如果需要重新绘制，则返回True。
bool WRDirMapControl::validate(void)
{
	bool changed = false;
	//验证数据源
	WRDirMapDataSource* dataSource = 0;
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
		}
		else
		{
			long version = m_currSource->version();
			if (m_currSource->validate() != version)
			{
				changed = true;
				m_dataView->invalidate();
			}
		}
	}
	if (dataSource)
	{
        dataSource->release();
        emit dataChanged();
        resetShowDataRange(WRDirMapDataRange(0, m_currSource->points(), m_currSource->angleMinValue(), m_currSource->angleMaxValue()));
		m_hAxis->invalidate();
		m_vAxis->invalidate();
	}

    return changed;
}

//当显示数据范围改变后调用此方法 。
void WRDirMapControl::onShowDataRangeChanged()
{
    if (effect())
    {
        //WRDirMapGaugeElement* element = WRDIRMAPFIRSTGAUGE;
        //while (element)
        //{
        //    if (element->type() == WRDirMapGaugeElement::Block)
        //    {
        //        element->arrange();
        //    }
        //    element =(WRDirMapGaugeElement*) element->next();
        //}
    }
    m_dataView->onShowDataRangeChanged();
    invalidate();
}
//当显示数据点范围改变后调用此方法。
void WRDirMapControl::onShowDataPointRangeChanged()
{
    if (effect())
    {
        WRDirMapGaugeElement* element = WRDIRMAPFIRSTGAUGE;
        while (element)
        {
            if (element->type() == WRDirMapGaugeElement::DataPointLine)
            {
                element->arrange();
            }
            element =(WRDirMapGaugeElement*) element->next();
        }
    }
	m_hAxis->invalidate();
    m_dataView->onShowDataPointRangeChanged();
}
//当显示数据角度范围改变后调用此方法。
void WRDirMapControl::onShowDataAngleRangeChanged()
{
    if (effect())
    {
        WRDirMapGaugeElement* element = WRDIRMAPFIRSTGAUGE;
        while (element)
        {
            if (element->type() == WRDirMapGaugeElement::DataAngleLine)
            {
                element->arrange();
            }
            element =(WRDirMapGaugeElement*) element->next();
        }
    }
	m_vAxis->invalidate();
    m_dataView->onShowDataAngleRangeChanged();
}

//设置显示数据范围。
void WRDirMapControl::setShowDataRange(const WRDirMapDataRange& value)
{
    bool change = false;
    if (m_showDataRange.pointRange(value.pointRange()))
    {
        onShowDataPointRangeChanged();
        emit showDataPointRangeChanged(m_showDataRange.pointRange());
        change = true;
    }
    if (m_showDataRange.angleRange(value.angleRange()))
    {
        onShowDataAngleRangeChanged();
        emit showDataAngleRangeChanged(m_showDataRange.angleRange());
        change = true;
    }
    if (change)
    {
        onShowDataRangeChanged();
        emit showDataRangeChanged(m_showDataRange);
    }
}
//设置数据点显示数据范围。
void WRDirMapControl::setShowDataPointRange(const WRChartSampleRange& value)
{
    if (m_showDataRange.pointRange(value))
    {
        onShowDataPointRangeChanged();
        onShowDataRangeChanged();
        emit showDataPointRangeChanged(m_showDataRange.pointRange());
        emit showDataRangeChanged(m_showDataRange);
    }
}
//设置数据角度显示数据范围。
void WRDirMapControl::setShowDataAngleRange(const WRChartDValueRange& value)
{
    if (m_showDataRange.angleRange(value))
    {
        onShowDataAngleRangeChanged();
        onShowDataRangeChanged();
        emit showDataAngleRangeChanged(m_showDataRange.angleRange());
        emit showDataRangeChanged(m_showDataRange);
    }
}

//设置显示数据范围。
bool WRDirMapControl::showDataRange(const WRDirMapDataRange& value)
{
    bool change = false;
    if (m_showDataRange.pointRange(value.pointRange()))
    {
        onShowDataPointRangeChanged();
        emit showDataPointRangeChanged(m_showDataRange.pointRange());
        change = true;
    }
    if (m_showDataRange.angleRange(value.angleRange()))
    {
        onShowDataAngleRangeChanged();
        emit showDataAngleRangeChanged(m_showDataRange.angleRange());
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
bool WRDirMapControl::showDataPointRange(const WRChartSampleRange& value)
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
//设置数据角度显示数据范围。
bool WRDirMapControl::showDataAngleRange(const WRChartDValueRange& value)
{
    if (m_showDataRange.angleRange(value))
    {
        onShowDataAngleRangeChanged();
        onShowDataRangeChanged();
        emit showDataAngleRangeChanged(m_showDataRange.angleRange());
        emit showDataRangeChanged(m_showDataRange);
        return true;
    }
    return false;
}

//初始化默认向频图控件。
WRDirMapControl::WRDirMapControl(void)
{
	initialize();
	WRDirMapInitParams<unsigned char, float> initArgs(0, 255, 0, 1, 0, 360, 101, true, 90000000, 100000000, 10, 100);
	m_backSource = new WRDirMapDataSourceT<unsigned char, float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, 101);
	m_showDataRange.angleRange().update(0, 100);
}

//初始化向频图控件，使用8位有符号整数幅度数据和16位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<signed char, short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<signed char, short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用8位无符号整数幅度数据和16位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned char, short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned char, short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用16位有符号整数幅度数据和16位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<short, short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<short, short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用16位无符号整数幅度数据和16位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned short, short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned short, short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位有符号整数幅度数据和16位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<int, short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<int, short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用32位无符号整数幅度数据和16位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned int, short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned int, short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位浮点数幅度数据和16位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<float, short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<float, short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用64位浮点数幅度数据和16位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<double, short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<double, short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用8位有符号整数幅度数据和16位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<signed char, unsigned short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<signed char, unsigned short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用8位无符号整数幅度数据和16位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned char, unsigned short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned char, unsigned short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用16位有符号整数幅度数据和16位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<short, unsigned short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<short, unsigned short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用16位无符号整数幅度数据和16位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned short, unsigned short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned short, unsigned short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位有符号整数幅度数据和16位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<int, unsigned short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<int, unsigned short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用32位无符号整数幅度数据和16位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned int, unsigned short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned int, unsigned short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位浮点数幅度数据和16位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<float, unsigned short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<float, unsigned short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用64位浮点数幅度数据和16位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<double, unsigned short>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<double, unsigned short>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用8位有符号整数幅度数据和32位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<signed char, int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<signed char, int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用8位无符号整数幅度数据和32位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned char, int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned char, int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用16位有符号整数幅度数据和32位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<short, int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<short, int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用16位无符号整数幅度数据和32位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned short, int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned short, int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位有符号整数幅度数据和32位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<int, int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<int, int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用32位无符号整数幅度数据和32位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned int, int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned int, int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位浮点数幅度数据和32位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<float, int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<float, int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用64位浮点数幅度数据和32位有符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<double, int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<double, int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用8位有符号整数幅度数据和32位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<signed char, unsigned int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<signed char, unsigned int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用8位无符号整数幅度数据和32位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned char, unsigned int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned char, unsigned int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用16位有符号整数幅度数据和32位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<short, unsigned int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<short, unsigned int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用16位无符号整数幅度数据和32位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned short, unsigned int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned short, unsigned int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位有符号整数幅度数据和32位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<int, unsigned int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<int, unsigned int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用32位无符号整数幅度数据和32位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned int, unsigned int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned int, unsigned int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位浮点数幅度数据和32位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<float, unsigned int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<float, unsigned int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用64位浮点数幅度数据和32位无符号整数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<double, unsigned int>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<double, unsigned int>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用8位有符号整数幅度数据和32位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<signed char, float>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<signed char, float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用8位无符号整数幅度数据和32位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned char, float>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned char, float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用16位有符号整数幅度数据和32位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<short, float>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<short, float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用16位无符号整数幅度数据和32位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned short, float>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned short, float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位有符号整数幅度数据和32位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<int, float>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<int, float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用32位无符号整数幅度数据和32位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned int, float>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned int, float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位浮点数幅度数据和32位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<float, float>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<float, float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用64位浮点数幅度数据和32位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<double, float>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<double, float>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用8位有符号整数幅度数据和64位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<signed char, double>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<signed char, double>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用8位无符号整数幅度数据和64位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned char, double>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned char, double>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用16位有符号整数幅度数据和64位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<short, double>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<short, double>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用16位无符号整数幅度数据和64位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned short, double>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned short, double>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位有符号整数幅度数据和64位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<int, double>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<int, double>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用32位无符号整数幅度数据和64位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<unsigned int, double>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<unsigned int, double>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用32位浮点数幅度数据和64位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<float, double>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<float, double>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}
//初始化向频图控件，使用64位浮点数幅度数据和64位浮点数方向数据。
WRDirMapControl::WRDirMapControl(const WRDirMapInitParams<double, double>& initArgs)
{
	initialize();
	m_backSource = new WRDirMapDataSourceT<double, double>(initArgs);
	m_currSource = m_backSource;
	m_currSource->addRef();
	m_showDataRange.pointRange().update(0, m_currSource->points());
	m_showDataRange.angleRange().update(m_currSource->angleMinValue(), m_currSource->angleMaxValue());
}

//初始化向频图控件，使用8位有符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<signed char, short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<signed char, short>(initArgs);
}
//初始化向频图控件，使用8位无符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned char, short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned char, short>(initArgs);
}

//初始化向频图控件，使用16位有符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<short, short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<short, short>(initArgs);
}
//初始化向频图控件，使用16位无符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned short, short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned short, short>(initArgs);
}

//初始化向频图控件，使用32位有符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<int, short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<int, short>(initArgs);
}
//初始化向频图控件，使用32位无符号整数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned int, short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned int, short>(initArgs);
}

//初始化向频图控件，使用32位浮点数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<float, short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<float, short>(initArgs);
}
//初始化向频图控件，使用64位浮点数幅度数据和16位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<double, short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<double, short>(initArgs);
}

//初始化向频图控件，使用8位有符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<signed char, unsigned short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<signed char, unsigned short>(initArgs);
}
//初始化向频图控件，使用8位无符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned char, unsigned short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned char, unsigned short>(initArgs);
}

//初始化向频图控件，使用16位有符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<short, unsigned short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<short, unsigned short>(initArgs);
}
//初始化向频图控件，使用16位无符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned short, unsigned short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned short, unsigned short>(initArgs);
}

//初始化向频图控件，使用32位有符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<int, unsigned short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<int, unsigned short>(initArgs);
}
//初始化向频图控件，使用32位无符号整数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned int, unsigned short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned int, unsigned short>(initArgs);
}

//初始化向频图控件，使用32位浮点数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<float, unsigned short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<float, unsigned short>(initArgs);
}
//初始化向频图控件，使用64位浮点数幅度数据和16位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<double, unsigned short>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<double, unsigned short>(initArgs);
}

//初始化向频图控件，使用8位有符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<signed char, int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<signed char, int>(initArgs);
}
//初始化向频图控件，使用8位无符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned char, int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned char, int>(initArgs);
}

//初始化向频图控件，使用16位有符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<short, int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<short, int>(initArgs);
}
//初始化向频图控件，使用16位无符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned short, int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned short, int>(initArgs);
}

//初始化向频图控件，使用32位有符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<int, int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<int, int>(initArgs);
}
//初始化向频图控件，使用32位无符号整数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned int, int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned int, int>(initArgs);
}

//初始化向频图控件，使用32位浮点数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<float, int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<float, int>(initArgs);
}
//初始化向频图控件，使用64位浮点数幅度数据和32位有符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<double, int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<double, int>(initArgs);
}

//初始化向频图控件，使用8位有符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<signed char, unsigned int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<signed char, unsigned int>(initArgs);
}
//初始化向频图控件，使用8位无符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned char, unsigned int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned char, unsigned int>(initArgs);
}

//初始化向频图控件，使用16位有符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<short, unsigned int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<short, unsigned int>(initArgs);
}
//初始化向频图控件，使用16位无符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned short, unsigned int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned short, unsigned int>(initArgs);
}

//初始化向频图控件，使用32位有符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<int, unsigned int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<int, unsigned int>(initArgs);
}
//初始化向频图控件，使用32位无符号整数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned int, unsigned int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned int, unsigned int>(initArgs);
}

//初始化向频图控件，使用32位浮点数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<float, unsigned int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<float, unsigned int>(initArgs);
}
//初始化向频图控件，使用64位浮点数幅度数据和32位无符号整数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<double, unsigned int>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<double, unsigned int>(initArgs);
}

//初始化向频图控件，使用8位有符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<signed char, float>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<signed char, float>(initArgs);
}
//初始化向频图控件，使用8位无符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned char, float>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned char, float>(initArgs);
}

//初始化向频图控件，使用16位有符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<short, float>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<short, float>(initArgs);
}
//初始化向频图控件，使用16位无符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned short, float>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned short, float>(initArgs);
}

//初始化向频图控件，使用32位有符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<int, float>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<int, float>(initArgs);
}
//初始化向频图控件，使用32位无符号整数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned int, float>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned int, float>(initArgs);
}

//初始化向频图控件，使用32位浮点数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<float, float>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<float, float>(initArgs);
}
//初始化向频图控件，使用64位浮点数幅度数据和32位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<double, float>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<double, float>(initArgs);
}

//初始化向频图控件，使用8位有符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<signed char, double>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<signed char, double>(initArgs);
}
//初始化向频图控件，使用8位无符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned char, double>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned char, double>(initArgs);
}

//初始化向频图控件，使用16位有符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<short, double>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<short, double>(initArgs);
}
//初始化向频图控件，使用16位无符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned short, double>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned short, double>(initArgs);
}

//初始化向频图控件，使用32位有符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<int, double>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<int, double>(initArgs);
}
//初始化向频图控件，使用32位无符号整数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<unsigned int, double>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<unsigned int, double>(initArgs);
}

//初始化向频图控件，使用32位浮点数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<float, double>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<float, double>(initArgs);
}
//初始化向频图控件，使用64位浮点数幅度数据和64位浮点数方向数据。该方法可以在多线程环境中使用。
void WRDirMapControl::initialize(const WRDirMapInitParams<double, double>& initArgs)
{
	WRSynch synch(m_mutex);
	m_backSource->release();
	m_backSource = new WRDirMapDataSourceT<double, double>(initArgs);
}

//清除数据。
void WRDirMapControl::clearData(void)
{
    WRSynch synch(m_mutex);
    m_backSource->clear();
}
//写入数据。该方法可以在多线程环境中使用。
void WRDirMapControl::writeData(const void* specBuffer, const void* angleBuffer, int dataFrames)
{
	WRSynch synch(m_mutex);
	m_backSource->append(specBuffer, angleBuffer, dataFrames);
}

//设置数据处理方式。
void WRDirMapControl::setDataProcMethod(DataProcMethod value)
{
    if (value != m_dataProcMethod)
    {
        m_dataProcMethod = value;
        invalidate();
        m_dataView->invalidate();
        invalidate();
        emit dataProcMethodChanged(m_dataProcMethod);
    }
}
//设置是否暂停数据。
void WRDirMapControl::setHoldStatus(bool value)
{
    if (value != readFlag(WRDIRMAPCONTROL_HOLDSTATUS))
    {
        writeFlag(WRDIRMAPCONTROL_HOLDSTATUS, value);
        emit holdStatusChanged(value);
    }
}
//设置背景颜色。
void WRDirMapControl::setBackColor(WRColor value)
{
    if (m_backColor.change(value.red(), value.green(), value.blue()))
    {
        invalidate();
        emit backColorChanged(m_backColor);
    }
}


//设置数据处理方式。
bool WRDirMapControl::dataProcMethod(DataProcMethod value)
{
	if (value != m_dataProcMethod)
	{
		m_dataProcMethod = value;
		invalidate();
		m_dataView->invalidate();
		invalidate();
        emit dataProcMethodChanged(m_dataProcMethod);
		return true;
	}
	return false;
}
//设置是否暂停数据。
bool WRDirMapControl::holdStatus(bool value)
{
    if (value != readFlag(WRDIRMAPCONTROL_HOLDSTATUS))
    {
        writeFlag(WRDIRMAPCONTROL_HOLDSTATUS, value);
        emit holdStatusChanged(value);
        return true;
    }
    return false;
}
//设置背景颜色。
bool WRDirMapControl::backColor(WRColor value)
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
WRDirMapDataPointLineElement* WRDirMapControl::addDataPointLine(int position)
{
    WRDirMapDataPointLineElement* child = new WRDirMapDataPointLineElement(position);
    {
        WRChartElement::addLast(child);
        child->arrange();
    }
    return child;
}
//添加数据角度线条。
WRDirMapDataAngleLineElement* WRDirMapControl::addDataAngleLine(double position)
{
    WRDirMapDataAngleLineElement* child = new WRDirMapDataAngleLineElement(position);
    {
        WRChartElement::addLast(child);
        child->arrange();
    }
    return child;
}

//移除测量元素。
void WRDirMapControl::remove(WRDirMapGaugeElement** element)
{
    if ((*element)->parent() == this)
    {
        WRChartElement::remove(*element);
		delete *element;
		*element = 0;
        doUpdate();
    }
}
