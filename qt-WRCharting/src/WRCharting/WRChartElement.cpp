#include <WRCharting/WRChartElement.h>
#include <WRCharting/WRChartControl.h>

//初始化图形元素。
WRChartElement::WRChartElement(void)
	: m_rect(0, 0, 0, 0)
{
    m_info = 0;

    m_prev = 0;
    m_next = 0;
    m_parent = 0;
    m_childFirst = 0;
    m_childLast = 0;

    m_bitmap = 0;

	visible(true);
	focused(false);
	focusable(false);
	invalid(true);
	buffered(false);
}
//释放图形元素所占用的相关资源。
WRChartElement::~WRChartElement(void)
{
	WRChartElement* child = m_childFirst;
    while (child)
	{
		WRChartElement* child2 = child->m_next;
		delete child;
		child = child2;
	}
    if (m_bitmap)
    {
        delete m_bitmap;
    }
}

//设置元素以及子级元素所属的控件。
void WRChartElement::info(WRChartPrivate* value)
{
    m_info = value;
	WRChartElement* child = m_childFirst;
    while (child)
	{
        child->info(value);
		child = child->m_next;
	}
}

//将指定的子元素插入到首位（底层）。
void WRChartElement::addFirst(WRChartElement* child)
{
    if (m_childFirst)
	{
		m_childFirst->m_prev = child;
		child->m_next = m_childFirst;
		m_childFirst = child;
		child->m_parent = this;
        child->info(m_info);
	}
	else
	{
		m_childFirst = child;
		m_childLast = child;
		child->m_parent = this;
        child->info(m_info);
	}
}
//将指定的子元素添加到末尾（顶层）。
void WRChartElement::addLast(WRChartElement* child)
{
    if (m_childLast)
	{
		m_childLast->m_next = child;
		child->m_prev = m_childLast;
		m_childLast = child;
		child->m_parent = this;
        child->info(m_info);
	}
	else
	{
		m_childFirst = child;
		m_childLast = child;
		child->m_parent = this;
        child->info(m_info);
	}
}
//将指定的子元素插入到指定元素之前（下层）。
void WRChartElement::addAfter(WRChartElement* current, WRChartElement* child)
{
	if (current == m_childLast)
	{
		m_childLast->m_next = child;
		child->m_prev = m_childLast;
		m_childLast = child;
		child->m_parent = this;
        child->info(m_info);
	}
	else
	{
		child->m_prev = current;
		child->m_next = current->m_next;
		current->m_next->m_prev = child;
		current->m_next = child;
		child->m_parent = this;
        child->info(m_info);
	}
}
//将指定的子元素插入到指定元素之后（上层）。
void WRChartElement::addBefore(WRChartElement* current, WRChartElement* child)
{
	if (current == m_childFirst)
	{
		m_childFirst->m_prev = child;
		child->m_next = m_childFirst;
		m_childFirst = child;
		child->m_parent = this;
        child->info(m_info);
	}
	else
	{
		child->m_prev = current->m_prev;
		child->m_next = current;
		current->m_prev->m_next = child;
		current->m_prev = child;
		child->m_parent = this;
        child->info(m_info);
	}
}
//移除指定的子元素。
void WRChartElement::remove(WRChartElement* child)
{
    if (child->m_prev)
	{
        child->m_prev->m_next = child->m_next;
	}
	else
    {
        m_childFirst = child->m_next;
	}
    if (child->m_next)
	{
        child->m_next->m_prev = child->m_prev;
	}
	else
    {
        m_childLast = child->m_prev;
	}
    child->m_prev = 0;
    child->m_next = 0;
    child->m_parent = 0;
    child->info(0);
}

//选中当前元素。
bool WRChartElement::select(void)
{
    if (m_info)
    {
        if (m_info->m_focused == this)
        {
            if (m_info->m_widget)
            {
                m_info->m_widget->setFocus();
            }
            return true;
        }
        else if (focusable())
        {
            WRChartElement* child = m_info->m_focused;
            while(child)
            {
                child->focused(false);
                child = child->parent();
            }
            m_info->m_focused = this;
            if (m_info->m_widget)
            {
                m_info->m_widget->setFocus();
            }
            return true;
        }
    }
    return false;
}

//绘制处理。
void WRChartElement::doPaint(QPainter& painter)
{
	if (visible() && !m_rect.empty())
	{
		//绘制当前元素
		if (buffered())
        {
			//创建缓存位图
            if (!m_bitmap)
			{
                m_bitmap = new QImage(size(), QImage::Format_RGB32);
				invalidate();
			}
            //执行缓存绘制
            if (invalid())
            {
                QPainter painter2(m_bitmap);
                onPaint(painter2);
            }
            painter.drawImage(m_rect, *m_bitmap);
        }
		else
		{
			onPaint(painter);
		}
		invalid(false);
		//循环进行子元素绘制
		WRChartElement* child = m_childFirst;
        while (child)
		{
			child->doPaint(painter);
			child = child->m_next;
		}
	}
}

//X值是否包含在内部。
bool WRChartElement::containsX(int x) const
{
	return m_rect.containsX(x);
}
//Y值是否包含在内部。
bool WRChartElement::containsY(int y) const
{
	return m_rect.containsY(y);
}
//判断指定的点是否在内部。
bool WRChartElement::contains(const WRPoint &p) const
{
	return m_rect.contains(p);
}

//命中测试。
WRChartElement* WRChartElement::hitTest(const WRPoint& pos)
{
	if (visible() && contains(pos))
	{
		WRChartElement* child = m_childLast;
        while (child)
		{
			WRChartElement* child2 = child->hitTest(pos);
            if (child2) return child2;
			child = child->m_prev;
		}
		return this;
	}
    return 0;
}

//当布局时调用此方法。
void WRChartElement::onLayout(const WRRect&)
{
	//add code here
}

//当矩形改变后调用此方法。
void WRChartElement::onRectChanged(void)
{
	//add code here
}

//当位置改变后调用此方法。
void WRChartElement::onPosChanged(void)
{
	//add code here
}
//当X坐标改变后调用此方法。
void WRChartElement::onLeftChanged(void)
{
	//add code here
}
//当Y坐标改变后调用此方法。
void WRChartElement::onTopChanged(void)
{
	//add code here
}
//当大小改变后调用此方法。
void WRChartElement::onSizeChanged(void)
{
	//add code here
}
//当宽度改变后调用此方法。
void WRChartElement::onWidthChanged(void)
{
	//add code here
}
//当高度改变后调用此方法。
void WRChartElement::onHeightChanged(void)
{
	//add code here
}

//改变元素布局。
void WRChartElement::doLayout(const WRRect& rect)
{
	int left = m_rect.left();
	int top = m_rect.top();
	int width = m_rect.width();
	int height = m_rect.height();
	m_rect = rect;

	bool rectChanged = false;

	bool posChanged = false;
	if (left != rect.left())
	{
		posChanged = true;
		onLeftChanged();
	}
	if (top != rect.top())
	{
		posChanged = true;
		onTopChanged();
	}
	if (posChanged)
	{
		rectChanged = true;
		onPosChanged();
	}

	bool sizeChanged = false;
	if (width != rect.width())
	{
		sizeChanged = true;
		onWidthChanged();
	}
	if (height != rect.height())
	{
		sizeChanged = true;
		onHeightChanged();
	}
	if (sizeChanged)
	{
		rectChanged = true;
        if (m_bitmap)
		{
            delete m_bitmap;
            m_bitmap = 0;
        }
		onSizeChanged();
	}

	if (rectChanged)
	{
		onRectChanged();
	}

	onLayout(m_rect);
}

//要求元素重新布局。
void WRChartElement::doLayout(void)
{
    if (m_info && m_info->m_widget)
	{
        onLayout(m_rect);
        m_info->m_control->invalidate();
	}
}
//请求元素所在的图形进行重新绘制。
void WRChartElement::doUpdate(void)
{
    if (m_info)
    {
        m_info->m_control->invalidate();
    }
}

//键盘按下处理，如果需要重绘，则返回True。
bool WRChartElement::onKeyDown(const QKeyEvent&)
{
	return false;
}
//键盘释放处理，如果需要重绘，则返回True。
bool WRChartElement::onKeyUp(const QKeyEvent&)
{
	return false;
}

//鼠标滚动处理，如果需要重绘，则返回True。
bool WRChartElement::onMouseWheel(const QWheelEvent&)
{
	return false;
}
//鼠标按下处理，如果需要重绘，则返回True。
bool WRChartElement::onMouseDown(const QMouseEvent&)
{
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRChartElement::onMouseUp(const QMouseEvent&)
{
	return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRChartElement::onMouseMove(const QMouseEvent&)
{
	return false;
}

//鼠标双击处理，如果需要重绘，则返回True。
bool WRChartElement::onMouseDoubleClick(const QMouseEvent&)
{
	return false;
}

//鼠标进入处理，如果需要重绘，则返回True。
bool WRChartElement::onMouseEnter(void)
{
	return false;
}
//鼠标离开处理，如果需要重绘，则返回True。
bool WRChartElement::onMouseLeave(void)
{
	return false;
}

//执行绘制处理。
void WRChartElement::onPaint(QPainter&)
{
	//add code here
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRChartElement::onPaintMouseFeedback(QPainter&)
{
	//add code here
}
