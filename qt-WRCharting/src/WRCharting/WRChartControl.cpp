#include <WRCharting/WRChartControl.h>
#include <WRCharting/WRChartAxisElement.h>
#include <WRCharting/WRChartScrollElement.h>
#include <WRCharting/WRChartDataViewElement.h>

//执行元素布局。
void WRChartControl::arrange(const WRRect& rect, WRChartHAxisElement* hAxis, WRChartVAxisElement* vAxis, WRChartHScrollElement* hScroll, WRChartVScrollElement* vScroll, WRChartDataViewElement* dataView)
{
    bool bVAxis, bHAxis, bVScroll, bHScroll;
    //布局数据视图
    int dataViewLeft, dataViewTop, dataViewRight, dataViewBottom, dataViewWidth, dataViewHeight;
    {
        bVAxis = false;
        bHAxis = false;
        bVScroll = false;
        bHScroll = false;
        dataViewLeft = rect.left();
        dataViewWidth = rect.width();
        dataViewTop = rect.top();
        dataViewHeight = rect.height();

        if (vAxis->visible() && dataViewWidth > WRCHARTAXIS_WIDTH)
        {
            bVAxis = true;
            dataViewWidth -= WRCHARTAXIS_WIDTH;
            if (vAxis->dockLeft())
            {
                dataViewLeft += WRCHARTAXIS_WIDTH;
            }
        }
        if (vScroll->visible() && dataViewWidth > WRCHARTSCROLL_WIDTH)
        {
            bVScroll = true;
            dataViewWidth -= WRCHARTSCROLL_WIDTH;
            if (vScroll->dockLeft())
            {
                dataViewLeft += WRCHARTSCROLL_WIDTH;
            }
        }

        if (hAxis->visible() && dataViewHeight > WRCHARTAXIS_WIDTH)
        {
            bHAxis = true;
            dataViewHeight -= WRCHARTAXIS_WIDTH;
            if (!hAxis->dockBottom())
            {
                dataViewTop += WRCHARTAXIS_WIDTH;
            }
        }
        if (hScroll->visible() && dataViewHeight > WRCHARTSCROLL_WIDTH)
        {
            bHScroll = true;
            dataViewHeight -= WRCHARTSCROLL_WIDTH;
            if (!hScroll->dockBottom())
            {
                dataViewTop += WRCHARTSCROLL_WIDTH;
            }
        }

        if (dataViewHeight < 2)
        {
            if (bVScroll)
            {
                bVScroll = false;
                dataViewWidth += WRCHARTSCROLL_WIDTH;
                if (vScroll->dockLeft())
                {
                    dataViewLeft -= WRCHARTSCROLL_WIDTH;
                }
            }
            if (bVAxis)\
            {
                bVAxis = false;
                dataViewWidth += WRCHARTAXIS_WIDTH;
                if (vAxis->dockLeft())
                {
                    dataViewLeft -= WRCHARTAXIS_WIDTH;
                }
            }
        }
        if (dataViewWidth < 2)
        {
            if (bHScroll)
            {
                bHScroll = false;
                dataViewHeight += WRCHARTSCROLL_WIDTH;
                if (!hScroll->dockBottom())
                {
                    dataViewTop -= WRCHARTSCROLL_WIDTH;
                }
            }
            if (bHAxis)
            {
                bHAxis = false;
                dataViewHeight += WRCHARTAXIS_WIDTH;
                if (!hAxis->dockBottom())
                {
                    dataViewTop -= WRCHARTAXIS_WIDTH;
                }
            }
        }

        dataViewRight = dataViewLeft + dataViewWidth;
        dataViewBottom = dataViewTop + dataViewHeight;
    }
    dataView->doLayout(WRRect(dataViewLeft, dataViewTop, dataViewWidth, dataViewHeight));
    //布局纵坐标轴和横坐标轴
    int freeLeft, freeRight, freeTop, freeBottom;
    if (bVAxis)
    {
        if (vAxis->dockLeft())
        {
            freeLeft = dataViewLeft - WRCHARTAXIS_WIDTH;
            freeRight = dataViewRight;
            vAxis->doLayout(WRRect(freeLeft, dataViewTop, WRCHARTAXIS_WIDTH, dataViewHeight));
        }
        else
        {
            freeLeft = dataViewLeft;
            freeRight = dataViewRight + WRCHARTAXIS_WIDTH;
            vAxis->doLayout(WRRect(dataViewRight, dataViewTop, WRCHARTAXIS_WIDTH, dataViewHeight));
        }
    }
    else
    {
        freeLeft = dataViewLeft;
        freeRight = dataViewRight;
        vAxis->doLayout(WRRect(0, 0, 0, dataViewHeight));
    }
    if (bHAxis)
    {
        if (hAxis->dockBottom())
        {
            freeTop = dataViewTop;
            freeBottom = dataViewBottom + WRCHARTAXIS_WIDTH;
            hAxis->doLayout(WRRect(dataViewLeft, dataViewBottom, dataViewWidth, WRCHARTAXIS_WIDTH));
        }
        else
        {
            freeTop = dataViewTop - WRCHARTAXIS_WIDTH;
            freeBottom = dataViewBottom;
            hAxis->doLayout(WRRect(dataViewLeft, freeTop, dataViewWidth, WRCHARTAXIS_WIDTH));
        }
    }
    else
    {
        freeTop = dataViewTop;
        freeBottom = dataViewBottom;
        hAxis->doLayout(WRRect(0, 0, dataViewWidth, 0));
    }
    //布局纵向滚动条和横向滚动条
    if (bVScroll)
    {
        if (vScroll->dockLeft())
        {
            vScroll->doLayout(WRRect(freeLeft - 16, dataViewTop, 12, dataViewHeight));
        }
        else
        {
            vScroll->doLayout(WRRect(freeRight + 4, dataViewTop, 12, dataViewHeight));
        }
    }
    else
    {
        vScroll->doLayout(WRRect(0, 0, 0, dataViewHeight));
    }
    if (bHScroll)
    {
        if (hScroll->dockBottom())
        {
            hScroll->doLayout(WRRect(dataViewLeft, freeBottom + 4, dataViewWidth, 12));
        }
        else
        {
            hScroll->doLayout(WRRect(dataViewLeft, freeTop - 16, dataViewWidth, 12));
        }
    }
    else
    {
        hScroll->doLayout(WRRect(0, 0, dataViewWidth, 0));
    }
}

//初始化图形控件。
WRChartControl::WRChartControl(void)
{
    m_info = new WRChartPrivate();
    m_info->m_control = this;
    m_info->m_focused = this;
	focusable(true);
}
//初始化图形控件。
WRChartControl::WRChartControl(WRChartPrivate* info)
{
    m_info = info;
    m_info->m_control = this;
    m_info->m_focused = this;
    focusable(true);
}

//释放当前对象所占用的相关资源。
WRChartControl::~WRChartControl(void)
{
    //add code here
}

//添加对象引用。
void WRChartControl::addRef(void)
{
    m_info->addRef();
}
//释放对象引用, 如果引用计数为0，则删除对象，返回True，否则返回False。
bool WRChartControl::release(void)
{
    if (m_info->release())
    {
        delete this;
        return true;
    }
    return false;
}

//验证图形，如果需要重新绘制，则返回True。
bool WRChartControl::validate()
{
	return false;
}

//过滤消息。
bool WRChartControl::eventFilter(QObject *, QEvent* event)
{
    switch(event->type())
    {
    case QEvent::Resize://尺寸改变消息事件
    {
        QResizeEvent* e = static_cast<QResizeEvent*>(event);
        if (m_info->doSize(e->size()))
        {
            return true;
        }
    }
        break;
    case QEvent::FocusIn://设置焦点事件
        if (m_info->doGotFocus())
        {
            return true;
        }
        break;
    case QEvent::FocusOut://失去焦点事件
        if (m_info->doLostFocus())
        {
            return true;
        }
        break;
    case QEvent::Paint://绘制事件
        if (m_info->doPaint())
        {
            return true;
        }
        break;
    case QEvent::Timer://定时消息
    {
        QTimerEvent* e = static_cast<QTimerEvent*>(event);
        if (m_info->doTimer(e->timerId()))
        {
            return true;
        }
    }
        break;
    case QEvent::KeyPress://键盘按下事件
    {
        QKeyEvent* e = static_cast<QKeyEvent*>(event);
        if (m_info->doKeyDown(e))
        {
            return true;
        }
    }
        break;
    case QEvent::KeyRelease://键盘释放事件
    {
        QKeyEvent* e = static_cast<QKeyEvent*>(event);
        if (m_info->doKeyUp(e))
        {
            return true;
        }
    }
        break;
    case QEvent::MouseButtonPress://鼠标按下事件
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(event);
        if (m_info->doMouseDown(e))
        {
            return true;
        }
    }
        break;
    case QEvent::MouseButtonRelease://鼠标释放事件
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(event);
        if (m_info->doMouseUp(e))
        {
            return true;
        }
    }
        break;
    case QEvent::MouseMove://鼠标移动事件
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(event);
        if (m_info->doMouseMove(e))
        {
            return true;
        }
    }
        break;
    case QEvent::MouseButtonDblClick://鼠标双击事件
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(event);
        if (m_info->doMouseDoubleClick(e))
        {
            return true;
        }
    }
        break;
    case QEvent::Wheel://鼠标滚动事件
    {
        QWheelEvent* e = static_cast<QWheelEvent*>(event);
        if (m_info->doMouseWheel(e))
        {
            return true;
        }
        e->accept();
        return true;//TODO必须返回True，否则上层滚动条会滚动。
    }
        break;
    case QEvent::Enter://鼠标进入事件
        if (m_info->doMouseEnter())
        {
            return true;
        }
        break;
    case QEvent::Leave://鼠标离开事件
        if (m_info->doMouseLeave())
        {
            return true;
        }
        break;
    default:
        return false;
    }
    return false;
}
