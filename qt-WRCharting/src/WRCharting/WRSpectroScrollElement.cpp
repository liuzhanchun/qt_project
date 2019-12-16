#include <WRCharting/WRSpectroScrollElement.h>
#include <WRCharting/WRSpectroControl.h>

//鼠标按下处理，如果需要重绘，则返回True。
bool WRSpectroHScrollElement::onMouseDown(const QMouseEvent&)
{
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRSpectroHScrollElement::onMouseUp(const QMouseEvent&)
{
	return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRSpectroHScrollElement::onMouseMove(const QMouseEvent&)
{
    return false;
}

//鼠标滚动处理。
bool WRSpectroHScrollElement::onMouseWheel(const QWheelEvent&)
{
    return false;
}

//执行纵滚动条绘制处理。
void WRSpectroVScrollElement::onPaint(QPainter&)
{

}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRSpectroHScrollElement::onPaintMouseFeedback(QPainter&)
{

}


//鼠标按下处理，如果需要重绘，则返回True。
bool WRSpectroVScrollElement::onMouseDown(const QMouseEvent&)
{
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRSpectroVScrollElement::onMouseUp(const QMouseEvent&)
{
	return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRSpectroVScrollElement::onMouseMove(const QMouseEvent&)
{
    return false;
}

//鼠标滚动处理。
bool WRSpectroVScrollElement::onMouseWheel(const QWheelEvent&)
{
    return false;
}

//执行横滚动条绘制处理。
void WRSpectroHScrollElement::onPaint(QPainter&)
{

}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRSpectroVScrollElement::onPaintMouseFeedback(QPainter&)
{

}
