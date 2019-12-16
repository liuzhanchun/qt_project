#include <WRCharting/WRChartScrollElement.h>
#include <WRCharting/WRChartControl.h>

//设置是否可见，如果可见性改变，则返回True。
void WRChartScrollElement::setVisible(bool value)
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
void WRChartScrollElement::setScalable(bool value)
{
    if (readFlag(WRCHARTSCROLL_SCALABLE) != value)
    {
        writeFlag(WRCHARTSCROLL_SCALABLE, value);
        emit scalableChanged(value);
    }
}

//设置背景颜色。
void WRChartScrollElement::setBackColor(WRColor value)
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
//设置前景颜色。
void WRChartScrollElement::setForeColor(WRColor value)
{
    if (m_foreColor.change(value.red(), value.green(), value.blue()))
    {
        if (visible() && !focused())
        {
            invalidate();
            doUpdate();
        }
        emit foreColorChanged(m_foreColor);
    }
}

//设置是否可见，如果可见性改变，则返回True。
bool WRChartScrollElement::visible(bool value)
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
bool WRChartScrollElement::scalable(bool value)
{
    if (readFlag(WRCHARTSCROLL_SCALABLE) != value)
    {
        writeFlag(WRCHARTSCROLL_SCALABLE, value);
        emit scalableChanged(value);
        return true;
    }
    return false;
}

//设置背景颜色。
bool WRChartScrollElement::backColor(WRColor value)
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
//设置前景颜色。
bool WRChartScrollElement::foreColor(WRColor value)
{
    if (m_foreColor.change(value.red(), value.green(), value.blue()))
    {
        if (visible() && !focused())
        {
            invalidate();
            doUpdate();
        }
        emit foreColorChanged(m_foreColor);
        return true;
    }
    return false;
}

//设置横向滚动条是否停靠在底部。
void WRChartHScrollElement::setDockBottom(bool value)
{
    if (readFlag(WRCHARTSCROLL_DOCK) != value)
    {
        writeFlag(WRCHARTSCROLL_DOCK,  value);
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
//设置横向滚动条是否停靠在底部。
bool WRChartHScrollElement::dockBottom(bool value)
{
    if (readFlag(WRCHARTSCROLL_DOCK) != value)
    {
        writeFlag(WRCHARTSCROLL_DOCK,  value);
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

//设置纵纵向滚动条是否停靠在左侧。
void WRChartVScrollElement::setDockLeft(bool value)
{
    if (readFlag(WRCHARTSCROLL_DOCK) != value)
    {
        writeFlag(WRCHARTSCROLL_DOCK,  value);
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
//设置纵纵向滚动条是否停靠在左侧。
bool WRChartVScrollElement::dockLeft(bool value)
{
    if (readFlag(WRCHARTSCROLL_DOCK) != value)
    {
        writeFlag(WRCHARTSCROLL_DOCK,  value);
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
