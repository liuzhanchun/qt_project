#include <WRCharting/WRDirMapScrollElement.h>
#include <WRCharting/WRDirMapControl.h>

//鼠标按下处理，如果需要重绘，则返回True。
bool WRDirMapHScrollElement::onMouseDown(const QMouseEvent&)
{
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRDirMapHScrollElement::onMouseUp(const QMouseEvent&)
{
	return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRDirMapHScrollElement::onMouseMove(const QMouseEvent&)
{
    return false;
}

//鼠标滚动处理。
bool WRDirMapHScrollElement::onMouseWheel(const QWheelEvent&)
{
    return false;
}

//执行纵滚动条绘制处理。
void WRDirMapVScrollElement::onPaint(QPainter&)
{

}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRDirMapHScrollElement::onPaintMouseFeedback(QPainter&)
{

}


//鼠标按下处理，如果需要重绘，则返回True。
bool WRDirMapVScrollElement::onMouseDown(const QMouseEvent&)
{
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRDirMapVScrollElement::onMouseUp(const QMouseEvent&)
{
	return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRDirMapVScrollElement::onMouseMove(const QMouseEvent&)
{
    return false;
}

//鼠标滚动处理。
bool WRDirMapVScrollElement::onMouseWheel(const QWheelEvent&)
{
    return false;
}

//执行横滚动条绘制处理。
void WRDirMapHScrollElement::onPaint(QPainter&)
{

}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRDirMapVScrollElement::onPaintMouseFeedback(QPainter&)
{

}
