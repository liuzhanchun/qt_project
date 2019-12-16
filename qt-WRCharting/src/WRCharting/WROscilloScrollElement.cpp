#include <WRCharting/WROscilloScrollElement.h>
#include <WRCharting/WROscilloControl.h>

//鼠标按下处理，如果需要重绘，则返回True。
bool WROscilloHScrollElement::onMouseDown(const QMouseEvent&)
{
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WROscilloHScrollElement::onMouseUp(const QMouseEvent&)
{
	return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WROscilloHScrollElement::onMouseMove(const QMouseEvent&)
{
    return false;
}

//鼠标滚动处理。
bool WROscilloHScrollElement::onMouseWheel(const QWheelEvent&)
{
    return false;
}

//执行纵滚动条绘制处理。
void WROscilloVScrollElement::onPaint(QPainter&)
{

}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WROscilloHScrollElement::onPaintMouseFeedback(QPainter&)
{

}


//鼠标按下处理，如果需要重绘，则返回True。
bool WROscilloVScrollElement::onMouseDown(const QMouseEvent&)
{
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WROscilloVScrollElement::onMouseUp(const QMouseEvent&)
{
	return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WROscilloVScrollElement::onMouseMove(const QMouseEvent&)
{
    return false;
}

//鼠标滚动处理。
bool WROscilloVScrollElement::onMouseWheel(const QWheelEvent&)
{
    return false;
}

//执行横滚动条绘制处理。
void WROscilloHScrollElement::onPaint(QPainter&)
{

}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WROscilloVScrollElement::onPaintMouseFeedback(QPainter&)
{

}
