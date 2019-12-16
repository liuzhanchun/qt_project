#include <WRCharting/WRChartDataViewElement.h>

//设置是否横向缩放。
void WRChartDataViewElement::setHScalable(bool value)
{
    if (value != readFlag(WRCHARTDATAVIEW_HSCALABLE))
    {
        writeFlag(WRCHARTDATAVIEW_HSCALABLE, value);
        emit hScalableChanged(value);
    }
}
//设置是否纵向缩放。
void WRChartDataViewElement::setVScalable(bool value)
{
    if (value != readFlag(WRCHARTDATAVIEW_VSCALABLE))
    {
        writeFlag(WRCHARTDATAVIEW_VSCALABLE, value);
        emit vScalableChanged(value);
    }
}

//设置鼠标拖动模式。
void WRChartDataViewElement::setMouseDragMode(MouseDragMode value)
{
    if (value != m_mouseDragMode)
    {
        m_mouseDragMode = value;
        emit mouseDragModeChanged(value);
    }
}
//设置鼠标矩形模式。
void WRChartDataViewElement::setMouseRectMode(MouseRectMode value)
{
    if (value != m_mouseRectMode)
    {
        m_mouseRectMode = value;
        emit mouseRectModeChanged(value);
    }
}

//设置鼠标矩形颜色。
void WRChartDataViewElement::setMouseRectColor(WRColor value)
{
    if (m_mouseRectColor.change(value))
    {
        if (mouseCaptured())
        {
            doUpdate();
        }
        emit mouseRectColorChanged(m_mouseRectColor);
    }
}
//设置鼠标线条颜色。
void WRChartDataViewElement::setMouseLineColor(WRColor value)
{
    if (m_mouseLineColor.change(value.red(), value.green(), value.blue()))
    {
        if (mouseCaptured())
        {
            doUpdate();
        }
        emit mouseLineColorChanged(m_mouseLineColor);
    }
}

//设置是否横向缩放。
bool WRChartDataViewElement::hScalable(bool value)
{
    if (value != readFlag(WRCHARTDATAVIEW_HSCALABLE))
    {
        writeFlag(WRCHARTDATAVIEW_HSCALABLE, value);
        emit hScalableChanged(value);
        return true;
    }
    return false;
}
//设置是否纵向缩放。
bool WRChartDataViewElement::vScalable(bool value)
{
    if (value != readFlag(WRCHARTDATAVIEW_VSCALABLE))
    {
        writeFlag(WRCHARTDATAVIEW_VSCALABLE, value);
        emit vScalableChanged(value);
        return true;
    }
    return false;
}
//设置鼠标拖动模式。
bool WRChartDataViewElement::mouseDragMode(MouseDragMode value)
{
    if (value != m_mouseDragMode)
    {
        m_mouseDragMode = value;
        emit mouseDragModeChanged(value);
        return true;
    }
    return false;
}
//设置鼠标矩形模式。
bool WRChartDataViewElement::mouseRectMode(MouseRectMode value)
{
    if (value != m_mouseRectMode)
    {
        m_mouseRectMode = value;
        emit mouseRectModeChanged(value);
        return true;
    }
    return false;
}

//设置鼠标矩形颜色。
bool WRChartDataViewElement::mouseRectColor(WRColor value)
{
    if (m_mouseRectColor.change(value))
    {
        if (mouseCaptured())
        {
            doUpdate();
        }
        emit mouseRectColorChanged(m_mouseRectColor);
        return true;
    }
    return false;
}
//设置鼠标线条颜色。
bool WRChartDataViewElement::mouseLineColor(WRColor value)
{
    if (m_mouseLineColor.change(value.red(), value.green(), value.blue()))
    {
        if (mouseCaptured())
        {
            doUpdate();
        }
        emit mouseLineColorChanged(m_mouseLineColor);
        return true;
    }
    return false;
}

//执行缩放处理。
bool WRChartDataViewElement::doZoom(const WRPoint&, const WRPoint&)
{
    return false;
}
//执行移动处理。
bool WRChartDataViewElement::doMove(const WRPoint&, const WRPoint&)
{
    return false;
}

//鼠标按下处理，如果需要重绘，则返回True。
bool WRChartDataViewElement::onMouseDown(const QMouseEvent& e)
{
    if (e.button() == Qt::LeftButton)
    {
        if (m_mouseDragMode != WRChartDataViewElement::MouseDragNone)
        {
            mouseSavePos(e.pos());
            setCapture();
        }
    }
    return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRChartDataViewElement::onMouseUp(const QMouseEvent& e)
{
    if (e.button() == Qt::LeftButton)
    {
        if (mouseCaptured())
        {
            releaseCapture();
            switch (m_mouseDragMode)
            {
            case WRChartDataViewElement::MouseDragZoom://缩放模式
            {
                WRPoint begPos = mouseSavePos();
                WRPoint endPos = mouseCurrPos();
                rect().adjust(endPos);

                emit mouseDragReleased(begPos, endPos);

                doZoom(begPos, endPos);

                return true;
            }
            case WRChartDataViewElement::MouseDragRect://矩形模式
            case WRChartDataViewElement::MouseDragLine://线性模式
            {
                WRPoint currPoint = mouseCurrPos();
                rect().adjust(currPoint);
                emit mouseDragReleased(mouseSavePos(), currPoint);
                return true;
            }
            default://默认处理
            {
                return false;
            }
            }
        }
    }
    return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRChartDataViewElement::onMouseMove(const QMouseEvent& e)
{
    if (mouseCaptured())
    {
        //根据拖动的不同进行处理
        switch (m_mouseDragMode)
        {
        case WRChartDataViewElement::MouseDragMove://移动模式
        {
            if (doMove(mouseSavePos(), mouseCurrPos()))
            {
                mouseSavePos(e.pos());
                return true;
            }
            return false;
        }
        case WRChartDataViewElement::MouseDragZoom://缩放模式
        case WRChartDataViewElement::MouseDragRect://矩形模式
        case WRChartDataViewElement::MouseDragLine://线性模式
        {
            WRPoint currPoint = mouseCurrPos();
            rect().adjust(currPoint);
            emit mouseDragChanged(mouseSavePos(), currPoint);
            return true;
        }
        default://默认处理
        {
            return false;
        }
        }
    }
    return false;
}

//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRChartDataViewElement::onPaintMouseFeedback(QPainter& painter)
{
   //绘制拖动信息
    if (mouseCaptured())
    {
        //根据拖动的不同进行处理
        switch (m_mouseDragMode)
        {
        case WRChartDataViewElement::MouseDragZoom://缩放模式
        case WRChartDataViewElement::MouseDragRect://矩形模式
        {
            WRPoint pos = mouseCurrPos();
            this->rect().adjust(pos);
            WRRect rect(mouseSavePos(), pos);
            if (!hScalable())
            {
                rect.left(left());
                rect.width(width());
            }
            else if (!vScalable())
            {
                rect.top(top());
                rect.height(height());
            }

            painter.fillRect(rect, m_mouseRectColor);
        }
            break;
        case WRChartDataViewElement::MouseDragLine://线性模式
        {
            WRPoint p1 = mouseSavePos();
            WRPoint p2 = mouseCurrPos();
            rect().adjust(p2);
            if (p1 != p2)
            {
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.setPen(m_mouseLineColor);
                painter.drawLine(p1, p2);
                painter.setRenderHint(QPainter::Antialiasing, false);
            }
        }
            break;
        default://默认处理
            break;
        }
    }
    else
    {
        //add code here
    }
}
