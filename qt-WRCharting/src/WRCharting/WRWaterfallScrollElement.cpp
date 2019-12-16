#include <WRCharting/WRWaterfallScrollElement.h>
#include <WRCharting/WRWaterfallControl.h>

//鼠标按下处理，如果需要重绘，则返回True。
bool WRWaterfallHScrollElement::onMouseDown(const QMouseEvent&)
{
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRWaterfallHScrollElement::onMouseUp(const QMouseEvent&)
{
	return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRWaterfallHScrollElement::onMouseMove(const QMouseEvent&)
{
    return false;
}

//鼠标滚动处理。
bool WRWaterfallHScrollElement::onMouseWheel(const QWheelEvent&)
{
    return false;
}

//执行纵滚动条绘制处理。
void WRWaterfallVScrollElement::onPaint(QPainter&)
{

}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRWaterfallHScrollElement::onPaintMouseFeedback(QPainter&)
{

}


//鼠标按下处理，如果需要重绘，则返回True。
bool WRWaterfallVScrollElement::onMouseDown(const QMouseEvent&)
{
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRWaterfallVScrollElement::onMouseUp(const QMouseEvent&)
{
	return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRWaterfallVScrollElement::onMouseMove(const QMouseEvent&)
{
    return false;
}

//鼠标滚动处理。
bool WRWaterfallVScrollElement::onMouseWheel(const QWheelEvent&)
{
    return false;
}

//执行横滚动条绘制处理。
void WRWaterfallHScrollElement::onPaint(QPainter&)
{

}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRWaterfallVScrollElement::onPaintMouseFeedback(QPainter&)
{

}
