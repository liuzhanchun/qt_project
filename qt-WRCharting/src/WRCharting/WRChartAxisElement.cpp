#include <WRCharting/WRChartAxisElement.h>

//设置是否可见，如果可见性改变，则返回True。
void WRChartAxisElement::setVisible(bool value)
{
    if (value != WRChartElement::visible())
    {
        WRChartElement::visible(value);
        WRChartElement* owner = parent();
        if (owner)
        {
            owner->doLayout();
        }
        emit visibleChanged(value);
    }
}
//设置是否支持缩放。
void WRChartAxisElement::setScalable(bool value)
{
    if (readFlag(WRCHARTAXIS_SCALABLE) != value)
    {
        writeFlag(WRCHARTAXIS_SCALABLE, value);
        emit scalableChanged(value);
    }
}

//设置背景颜色。
void WRChartAxisElement::setBackColor(WRColor value)
{
    if (m_backColor.change(value.red(), value.green(), value.blue()))
    {
        if (visible() && !focused())
        {
            invalidate();
            doUpdate();
        }
        emit backColorChanged(m_backColor);
    }
}
//设置线条颜色。
void WRChartAxisElement::setLineColor(WRColor value)
{
    if (m_lineColor.change(value.red(), value.green(), value.blue()))
    {
        if (visible() && !focused())
        {
            invalidate();
            doUpdate();
        }
        emit lineColorChanged(m_lineColor);
    }
}
//设置文字颜色。
void WRChartAxisElement::setTextColor(WRColor value)
{
    if (m_textColor.change(value.red(), value.green(), value.blue()))
    {
        if (visible() && !focused())
        {
            invalidate();
            doUpdate();
        }
        emit textColorChanged(m_textColor);
    }
}

//设置是否可见，如果可见性改变，则返回True。
bool WRChartAxisElement::visible(bool value)
{
    if (value != WRChartElement::visible())
    {
        WRChartElement::visible(value);
        WRChartElement* owner = parent();
        if (owner)
        {
            owner->doLayout();
        }
        emit visibleChanged(value);
        return true;
    }
    return false;
}
//设置是否支持缩放。
bool WRChartAxisElement::scalable(bool value)
{
    if (readFlag(WRCHARTAXIS_SCALABLE) != value)
    {
        writeFlag(WRCHARTAXIS_SCALABLE, value);
        emit scalableChanged(value);
        return true;
    }
    return false;
}

//设置背景颜色。
bool WRChartAxisElement::backColor(WRColor value)
{
    if (m_backColor.change(value.red(), value.green(), value.blue()))
    {
        if (visible() && !focused())
        {
            invalidate();
            doUpdate();
        }
        emit backColorChanged(m_backColor);
        return true;
    }
    return false;
}
//设置线条颜色。
bool WRChartAxisElement::lineColor(WRColor value)
{
    if (m_lineColor.change(value.red(), value.green(), value.blue()))
    {
        if (visible() && !focused())
        {
            invalidate();
            doUpdate();
        }
        emit lineColorChanged(m_lineColor);
        return true;
    }
    return false;
}
//设置文字颜色。
bool WRChartAxisElement::textColor(WRColor value)
{
    if (m_textColor.change(value.red(), value.green(), value.blue()))
    {
        if (visible() && !focused())
        {
            invalidate();
            doUpdate();
        }
        emit textColorChanged(m_textColor);
        return true;
    }
    return false;
}

//设置横向坐标轴是否停靠在底部。
void WRChartHAxisElement::setDockBottom(bool value)
{
    if (readFlag(WRCHARTAXIS_DOCK) != value)
    {
        writeFlag(WRCHARTAXIS_DOCK,  value);
        if (visible())
        {
            WRChartElement* owner = parent();
            if (owner)
            {
                owner->doLayout();
            }
        }
        emit dockChanged(value);
    }
}
//设置横向坐标轴是否停靠在底部。
bool WRChartHAxisElement::dockBottom(bool value)
{
    if (readFlag(WRCHARTAXIS_DOCK) != value)
    {
        writeFlag(WRCHARTAXIS_DOCK,  value);
        if (visible())
        {
            WRChartElement* owner = parent();
            if (owner)
            {
                owner->doLayout();
            }
        }
        emit dockChanged(value);
        return true;
    }
    return false;
}

//设置纵纵向坐标轴是否停靠在左侧。
void WRChartVAxisElement::setDockLeft(bool value)
{
    if (readFlag(WRCHARTAXIS_DOCK) != value)
    {
        writeFlag(WRCHARTAXIS_DOCK,  value);
        if (visible())
        {
            WRChartElement* owner = parent();
            if (owner)
            {
                owner->doLayout();
            }
        }
        emit dockChanged(value);
    }
}
//设置纵纵向坐标轴是否停靠在左侧。
bool WRChartVAxisElement::dockLeft(bool value)
{
    if (readFlag(WRCHARTAXIS_DOCK) != value)
    {
        writeFlag(WRCHARTAXIS_DOCK,  value);
        if (visible())
        {
            WRChartElement* owner = parent();
            if (owner)
            {
                owner->doLayout();
            }
        }
        emit dockChanged(value);
        return true;
    }
    return false;
}

