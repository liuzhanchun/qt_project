#include <WRCharting/WRChartPrivate.h>
#include <WRCharting/WRChartElement.h>
#include <WRCharting/WRChartControl.h>

#define WRCHART_TIMERINTERVAL	40

//初始化图形信息。
WRChartPrivate::WRChartPrivate(void)
{
    m_refCnt = 1;
    m_widget = 0;
    m_control = 0;
    m_focused = 0;
    m_capture = 0;
    m_current = 0;
    m_timerId = 0;
}
//清理当前对象所占用的相关资源。
WRChartPrivate::~WRChartPrivate(void)
{
    if (m_widget)
    {
        doDetach();
    }
}

//查找可以获取焦点的元素。
WRChartElement* WRChartPrivate::getFocusableElement(WRChartElement* current)
{
    WRChartElement* child = current->childFirst();
    while(child)
    {
        WRChartElement* focused = getFocusableElement(child);
        if (focused)
        {
            return focused;
        }
        child = child->next();
    }
    if (current->focusable() && current->visible() && !current->rect().empty())
    {
        return current;
    }
    return 0;
}
//查找下一个可以获取焦点的元素。
WRChartElement* WRChartPrivate::nextFocusableElement(void)
{
    if (m_focused == m_control)
    {
        return getFocusableElement(m_control);
    }
    else
    {
        WRChartElement* next = m_focused->next();
        while(next)
        {
            WRChartElement* focused = getFocusableElement(next);
            if (focused)
            {
                return focused;
            }
            next = next->next();
        }
        WRChartElement* parent = m_focused->parent();
        while(true)
        {
            if (parent->focusable() && parent->visible() && !parent->rect().empty() )
            {
                return parent;
            }
            next = parent->next();
            while(next)
            {
                WRChartElement* focused = getFocusableElement(next);
                if (focused)
                {
                    return focused;
                }
                next = next->next();
            }
            parent = parent->parent();
        }
    }
}

//执行窗口绑定。
void WRChartPrivate::doAttach(QWidget* widget)
{
    //设置元素未捕获鼠标
    m_capture = 0;
    //设置元素未命中鼠标
    m_current = 0;
    //设置元素无效，需要重绘
    m_control->invalidate();
    //获取窗口尺寸并重新而已元素
    WRRect rect(widget->rect());
    m_control->doLayout(rect);
    //保存窗口句柄。
    m_widget = widget;
    //设置鼠标跟踪。
    m_widget->setMouseTracking(true);
    //设置可以捕获焦点。
    m_widget->setFocusPolicy(Qt::StrongFocus);
    //安装事件过滤器。
    m_widget->installEventFilter(m_control);
    //创建定时器
    m_timerId = m_widget->startTimer(WRCHART_TIMERINTERVAL);
    //使窗口无效
    m_widget->update();
}
//执行窗口解绑。
void WRChartPrivate::doDetach()
{
    //删除定时器
    m_widget->killTimer(m_timerId);
    //移除消息过滤器
    m_widget->removeEventFilter(m_control);
    //清空相应变量。
    m_widget = 0;
}

//尺寸改变处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doSize(const WRSize& size)
{
    //获取窗口尺寸并重新而已元素
    m_control->doLayout(QRect(0,0, size.width(), size.height()));
    //设置显示无效
    m_control->invalidate();
    //使窗口无效
    m_widget->update();

    return false;
}

//获取焦点处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doGotFocus(void)
{
    WRChartElement* child = m_focused;
    while(child)
    {
        child->focused(true);
        child = child->parent();
    }
    m_control->invalidate();
    return false;
}
//失去焦点处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doLostFocus(void)
{
    WRChartElement* child = m_focused;
    while(child)
    {
        child->focused(false);
        child = child->parent();
    }
    m_control->invalidate();
    return false;
}

//绘制处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doPaint(void)
{
    if (m_control->size().empty())
    {
        return true;
    }
    QPainter painter(m_widget);
    //执行绘制处理
    m_control->doPaint(painter);
    //绘制鼠标反馈信息（捕获鼠标的元素或者当前鼠标在其上的元素）
    if (m_capture)
    {
        m_capture->onPaintMouseFeedback(painter);
    }
    else if (m_current)
    {
        m_current->onPaintMouseFeedback(painter);
    }
    //绘制聚焦虚线框。
    if (focused())
    {
        //TODO
        //painter.setPen(Qt::DotLine);
        //painter.focus();
    }
    return true;
}

//定时处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doTimer(int timerId)
{
    if (timerId == m_timerId)
    {
        if (m_control->validate() || m_control->invalid())
        {
            m_control->invalid(false);
            m_widget->update();
        }
        return true;
    }
    return false;
}

//键盘按下处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doKeyDown(QKeyEvent* e)
{
    if (((e->modifiers() & Qt::ControlModifier) == Qt::ControlModifier) && e->key() == Qt::Key_Tab)
    {
        WRChartElement* focused = nextFocusableElement();
        if (focused && focused != m_focused)
        {
            WRChartElement* child = m_focused;
            while(child)
            {
                child->focused(false);
                child = child->parent();
            }

            m_focused = focused;

            child = m_focused;
            while(child)
            {
                child->focused(true);
                child = child->parent();
            }

            m_control->invalidate();
        }
    }
    else
    {
        if (m_focused->onKeyDown(*e))
        {
            m_control->invalidate();
        }
    }
    m_focused->keyDown(e);
    return false;
}
//键盘释放处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doKeyUp(QKeyEvent* e)
{
    if (m_focused->onKeyUp(*e))
    {
        m_control->invalidate();
    }
    emit m_focused->keyUp(e);
    return false;
}

//鼠标滚动处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doMouseWheel(QWheelEvent* e)
{
    m_mouseCurrPos = e->pos();

    bool changed = false;
    WRChartElement* element = m_control->hitTest(m_mouseCurrPos);
    if (m_current != element)
    {
        if (m_current)
        {
            if (m_current->onMouseLeave())
            {
                changed = true;
            }
            emit m_current->mouseLeave();
        }
        if (element)
        {
            if (element->onMouseEnter())
            {
                changed = true;
            }
            emit element->mouseEnter();
        }
        m_current = element;
    }
    if ((element && element->onMouseWheel(*e)) || changed)
    {
        m_control->invalidate();
    }
    if (element)
    {
        emit element->mouseWheel(e);
    }
    return false;
}
//鼠标按下处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doMouseDown(QMouseEvent* e)
{
    m_mouseCurrPos = e->pos();

    bool changed = false;
    WRChartElement* element = m_control->hitTest(m_mouseCurrPos);

    if (element)
    {
        WRChartElement* child = element;
        while(child)
        {
            if (child->focusable())
            {
                break;
            }
            child = child->parent();
        }
        if (m_focused != child)
        {
            WRChartElement* child2 = m_focused;
            while(child2)
            {
                child2->focused(false);
                child2 = child2->parent();
            }

            m_focused = child;

            while(child)
            {
                child->focused(true);
                child = child->parent();
            }

            changed = true;
        }
    }

    if (m_current != element)
    {
        if (m_current)
        {
            if (m_current->onMouseLeave())
            {
                changed = true;
            }
            emit m_current->mouseLeave();
        }
        if (element)
        {
            if (element->onMouseEnter())
            {
                changed = true;
            }
            emit element->mouseEnter();
        }
        m_current = element;
    }

    if (m_capture) element = m_capture;
    if ((element && element->onMouseDown(*e)) || changed)
    {
        m_control->invalidate();
    }
    if (element)
    {
        emit element->mouseDown(e);
    }
    return false;
}
//鼠标释放处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doMouseUp(QMouseEvent* e)
{
    m_mouseCurrPos = e->pos();

    bool changed = false;
    WRChartElement* element = m_control->hitTest(m_mouseCurrPos);
    if (m_current != element)
    {
        if (m_current)
        {
            if (m_current->onMouseLeave())
            {
                changed = true;
            }
            emit m_current->mouseLeave();
        }
        if (element)
        {
            if (element->onMouseEnter())
            {
                changed = true;
            }
            emit element->mouseEnter();
        }
        m_current = element;
    }
    if (m_capture) element = m_capture;
    if ((element && element->onMouseUp(*e)) || changed)
    {
        m_control->invalidate();
    }
    if (element)
    {
        emit element->mouseUp(e);
    }
    return false;
}
//鼠标移动处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doMouseMove(QMouseEvent* e)
{
    m_mouseCurrPos = e->pos();

    bool changed = false;
    WRChartElement* element = m_control->hitTest(m_mouseCurrPos);
    if (m_current != element)
    {
        if (m_current)
        {
            if (m_current->onMouseLeave())
            {
                changed = true;
            }
            emit m_current->mouseLeave();
        }
        if (element)
        {
            if (element->onMouseEnter())
            {
                changed = true;
            }
            emit element->mouseEnter();
        }
        m_current = element;
    }
    if (m_capture) element = m_capture;
    if ((element && element->onMouseMove(*e)) || changed)
    {
        m_control->invalidate();
    }
    if (element)
    {
        emit element->mouseMove(e);
    }
    return false;
}

//鼠标双击处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doMouseDoubleClick(QMouseEvent* e)
{
    m_mouseCurrPos = e->pos();

    bool changed = false;
    WRChartElement* element = m_control->hitTest(m_mouseCurrPos);
    if (m_current != element)
    {
        if (m_current)
        {
            if (m_current->onMouseLeave())
            {
                changed = true;
            }
            emit m_current->mouseLeave();
        }
        if (element)
        {
            if (element->onMouseEnter())
            {
                changed = true;
            }
            emit element->mouseEnter();
        }
        m_current = element;
    }
    if (m_capture) element = m_capture;
    if ((element && element->onMouseDoubleClick(*e)) || changed)
    {
        m_control->invalidate();
    }
    if (element)
    {
        emit element->mouseDoubleClick(e);
    }
    return false;
}

//鼠标进入处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doMouseEnter(void)
{
    return false;
}
//鼠标离开处理，如果不需要继续处理，则返回True。
bool WRChartPrivate::doMouseLeave(void)
{
    if (m_current)
    {
        if (m_current->onMouseLeave())
        {
            m_control->invalidate();
        }
        emit m_current->mouseLeave();
        m_current = 0;
    }
    return false;
}
