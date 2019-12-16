#include <WRCharting/WRSpectroAxisElement.h>
#include <WRCharting/WRSpectroControl.h>
#include <WRCharting/WRText.h>

//鼠标按下处理，如果需要重绘，则返回True。
bool WRSpectroHAxisElement::onMouseDown(const QMouseEvent& e)
{
	if (e.button() == Qt::LeftButton)
	{
        mouseSavePos(e.pos());
		setCapture();
	}
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRSpectroHAxisElement::onMouseUp(const QMouseEvent& e)
{
	if (e.button() == Qt::LeftButton)
	{
		if (mouseCaptured())
        {
			releaseCapture();
		}
	}
	return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRSpectroHAxisElement::onMouseMove(const QMouseEvent& e)
{
	if (mouseCaptured())
	{
		WRSpectroControl* chart = (WRSpectroControl*)owner();
		WRChartSampleRange showPointRange(chart->showDataPointRange());
		chart->doMouseMoveH(showPointRange, mouseSavePos().x(), mouseCurrPos().x(), width());
		if(chart->changeShowDataPointRange(showPointRange))
		{
			mouseSavePos(e.pos());
			return true;
		}
	}
    return false;
}

//鼠标双击处理，如果需要重绘，则返回True。
bool WRSpectroHAxisElement::onMouseDoubleClick(const QMouseEvent& e)
{
	if (scalable())
	{
		int delta = 0;
		if (e.button() == Qt::LeftButton)
		{
			delta = 1;
		}
		else if (e.button() == Qt::RightButton)
		{
			delta = -1;
		}
		if (delta != 0)
		{
			WRSpectroControl* chart = (WRSpectroControl*)owner();
			WRChartSampleRange showPointRange(chart->showDataPointRange());
			chart->doMouseWheelH(showPointRange, e.x() - left(), delta, width());
			return chart->changeShowDataPointRange(showPointRange);
		}
	}
	return false;
}

//鼠标滚动处理。
bool WRSpectroHAxisElement::onMouseWheel(const QWheelEvent& e)
{
    if (scalable())
    {
        WRSpectroControl* chart = (WRSpectroControl*)owner();
        WRChartSampleRange showPointRange(chart->showDataPointRange());
        chart->doMouseWheelH(showPointRange, e.x() - left(), e.delta(), width());
        return chart->changeShowDataPointRange(showPointRange);
    }
    return false;
}

//执行横坐标轴绘制处理。
void WRSpectroHAxisElement::onPaint(QPainter& painter)
{
    WRSpectroControl* chart = (WRSpectroControl*)owner();
    WRSpectroDataSource* dataSource = chart->dataSource();
    //填充背景
    painter.fillRect(QRect(0, 0, width(), height()), backColor());
    //绘制坐标轴线
    QPen textPen = painter.pen();
    textPen.setColor(textColor());
    //
    QPen linePen = painter.pen();
    linePen.setColor(lineColor());
    painter.setPen(linePen);
    //
    QFont font = painter.font();
    font.setPointSize(9);
    painter.setFont(font);
    //
    int lineRight, lineTop, lineBottomMain, lineBottomMinor, textBase;
    lineRight = width() - 1;
    if (dockBottom())
    {
        lineTop = 0;
        lineBottomMain = 13;
        lineBottomMinor = 4;
        painter.drawLine(0, lineTop, lineRight, lineTop);//绘制坐标轴线
        lineTop += 1;
        textBase = 16;
    }
    else
    {
        lineTop = height() - 1;
        lineBottomMain = lineTop - 13;
        lineBottomMinor = lineTop - 4;
        painter.drawLine(0, lineTop, lineRight, lineTop);//绘制坐标轴线
        lineTop -= 1;
        textBase = 12;
    }
    //计算刻度信息
    int segPointCount = chart->getDataPointCount(width(), 20);
    if (segPointCount < 1)
    {
        segPointCount = 1;
    }
    else if (segPointCount < 10)
    {
        segPointCount = (segPointCount + 1) / 2 * 2;
    }
    else
    {
        int t1 = 100;
        int t2 = 9;
        while (segPointCount > t1)
        {
            t1 *= 10;
            t2 = t2 * 10 + 9;
        }
        t1 /= 10;
        segPointCount = (segPointCount + t2) / t1 * t1;
    }
    int showPointBegin = chart->showDataPointBegin();
    int segPointStart = showPointBegin % segPointCount;
    if (segPointStart != 0)
    {
        showPointBegin += segPointCount - segPointStart;
    }
    int showPointEnd = chart->showDataPointEnd();
    //执行坐标轴绘制
    char buffer1[256];
    QChar buffer2[256];
    int length = WRText::toFreqString(chart->freqEnd(), buffer1, false);
    WRText::copy(buffer1, buffer2, length);
    QString string = QString::fromRawData(buffer2, length);
    QFontMetrics fontMetrics(font);
    int size = fontMetrics.width(string);
    int xSpan = chart->getDataPointWidth(width(), segPointCount);
    int mainSpan = (size + 8 + xSpan - 1) / xSpan;
    if (mainSpan < 1)
    {
        mainSpan = 1;
    }
    int segIndex = showPointBegin / segPointCount;
    while (showPointBegin < showPointEnd)
    {
        int xPos = chart->getDataPointPos(width(), showPointBegin);
        if (segIndex % mainSpan == 0)
        {
            //绘制刻度线
            painter.drawLine(xPos, lineTop, xPos, lineBottomMain);
            //绘制刻度值
            length = WRText::toFreqString(dataSource->getFreqValue(showPointBegin), buffer1);
            WRText::copy(buffer1, buffer2, length);
            string = QString::fromRawData(buffer2, length);
            size = fontMetrics.width(string);
            if ((width() - xPos - 2) >= size)
            {
                painter.setPen(textPen);
                painter.drawText(xPos + 2, textBase, string);
                painter.setPen(linePen);
            }
        }
        else
        {
            painter.drawLine(xPos, lineTop, xPos, lineBottomMinor);
        }
        segIndex += 1;
        showPointBegin += segPointCount;
    }
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRSpectroHAxisElement::onPaintMouseFeedback(QPainter&)
{
	//add code here
}


//鼠标按下处理，如果需要重绘，则返回True。
bool WRSpectroVAxisElement::onMouseDown(const QMouseEvent& e)
{
	if (e.button() == Qt::LeftButton)
	{
        mouseSavePos(e.pos());
		setCapture();
	}
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRSpectroVAxisElement::onMouseUp(const QMouseEvent& e)
{
	if (e.button() == Qt::LeftButton)
	{
		if (mouseCaptured())
        {
			releaseCapture();
		}
	}
	return false;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRSpectroVAxisElement::onMouseMove(const QMouseEvent& e)
{
	if (mouseCaptured())
	{
		WRSpectroControl* chart = (WRSpectroControl*)owner();
		WRChartDValueRange showValueRange(chart->showDataValueRange());
		chart->doMouseMoveV(showValueRange, mouseSavePos().y(), mouseCurrPos().y(), height());
		if(chart->changeShowDataValueRange(showValueRange))
		{
			mouseSavePos(e.pos());
			return true;
		}
	}
    return false;
}

//鼠标双击处理，如果需要重绘，则返回True。
bool WRSpectroVAxisElement::onMouseDoubleClick(const QMouseEvent& e)
{
	if (scalable())
	{
		int delta = 0;
		if (e.button() == Qt::LeftButton)
		{
			delta = 1;
		}
		else if (e.button() == Qt::RightButton)
		{
			delta = -1;
		}
		if (delta != 0)
		{
			WRSpectroControl* chart = (WRSpectroControl*)owner();
			WRChartDValueRange showValueRange(chart->showDataValueRange());
			chart->doMouseWheelV(showValueRange, e.y() - top(), delta, height());
			return chart->changeShowDataValueRange(showValueRange);
		}
	}
	return false;
}

//鼠标滚动处理。
bool WRSpectroVAxisElement::onMouseWheel(const QWheelEvent& e)
{
    if (scalable())
    {
        WRSpectroControl* chart = (WRSpectroControl*)owner();
        WRChartDValueRange showValueRange(chart->showDataValueRange());
        chart->doMouseWheelV(showValueRange, e.y() - top(), e.delta(), height());
        return chart->changeShowDataValueRange(showValueRange);
    }
    return false;
}

//执行纵坐标轴绘制处理。
void WRSpectroVAxisElement::onPaint(QPainter& painter)
{
    WRSpectroControl* chart = (WRSpectroControl*)owner();
    //填充背景
    painter.fillRect(QRect(0, 0, width(), height()), backColor());
	//绘制坐标轴线
    QPen textPen = painter.pen();
    textPen.setColor(textColor());
    //
    QPen linePen = painter.pen();
    linePen.setColor(lineColor());
    painter.setPen(linePen);
    //
    QFont font = painter.font();
    font.setPointSize(9);
    painter.setFont(font);
    //
    int lineLeft, lineBottom, lineRightMain, lineRightMinor, textBase;
    lineBottom = height() - 1;
    if (dockLeft())
    {
        lineLeft = width() - 1;
        lineRightMain = lineLeft - 13;
        lineRightMinor = lineLeft - 4;
        painter.drawLine(lineLeft, 0, lineLeft, lineBottom);//绘制坐标轴线
        lineLeft -= 1;
        textBase = 12;
    }
    else
    {
        lineLeft = 0;
        lineRightMain = 13;
        lineRightMinor = 4;
        painter.drawLine(lineLeft, 0, lineLeft, lineBottom);//绘制坐标轴线
        lineLeft += 1;
        textBase = 16;
    }
	//绘制刻度信息
    //计算刻度信息
    long long valueMultiple = 1;
    double segValueSpan = chart->getDataValueSpan(height(), 20);
    while (segValueSpan < 1.0)
    {
        segValueSpan *= 10;
        valueMultiple *= 10;
    }
    long long segValueSpanL = (long long)(segValueSpan + 1);
    if (segValueSpanL > 10)
    {
        long long t1 = 100;
        long long t2 = 9;
        while (segValueSpanL > t1)
        {
            t1 *= 10;
            t2 = t2 * 10 + 9;
        }
        t1 /= 10;
        segValueSpanL = (segValueSpanL + t2) / t1 * t1;
    }
    long long showValueBeginL = (long long)((chart->showDataValueBegin() - chart->dataMinValue()) * valueMultiple + 0.5);
    long long showValueBeing2L = showValueBeginL;
    long long segValueStartL = showValueBeginL % segValueSpanL;
    if (segValueStartL != 0)
    {
        showValueBeginL += segValueSpanL - segValueStartL;
    }
    long long showValueEndL = (long long)((chart->showDataValueEnd() - chart->dataMinValue()) * valueMultiple + 0.5);
    double valueMultipleF = (double)valueMultiple;
    //执行坐标轴绘制
    //以最长数据值字符串长度作为刻度线的显示依据
    char buffer1[256];
    QChar buffer2[256];
    int length = WRText::toString(chart->showDataValueBegin(), buffer1, false);
    WRText::copy(buffer1, buffer2, length);
    QString string = QString::fromRawData(buffer2, length);
    QFontMetrics fontMetrics(font);
    int size = fontMetrics.width(string);
    int segHeight = size;
    length = WRText::toString(chart->showDataValueEnd(), buffer1, false);
    WRText::copy(buffer1, buffer2, length);
    string = QString::fromRawData(buffer2, length);
    size = fontMetrics.width(string);
    if (segHeight < size) segHeight = size;

    int yPos = height() - 1 - chart->getDataValueOffsetPos(height(), segValueSpanL / valueMultipleF);
    int mainSpan = (segHeight + 8 + yPos - 1) / yPos;
    if (mainSpan < 1)
    {
        mainSpan = 1;
    }
    long long segIndex = showValueBeginL / segValueSpanL;
    while (showValueBeginL < showValueEndL)
    {
        int yPos = chart->getDataValueOffsetPos(height(), (showValueBeginL - showValueBeing2L) / valueMultipleF);
        if (segIndex % mainSpan == 0)
        {
            //绘制刻度线
            painter.drawLine(lineLeft, yPos, lineRightMain, yPos);
            //绘制刻度值
            length = WRText::toString(chart->dataMinValue() + chart->dataOffValue() + showValueBeginL / valueMultipleF, buffer1);
            WRText::copy(buffer1, buffer2, length);
            string = QString::fromRawData(buffer2, length);
            size = fontMetrics.width(string);
            if ((yPos - 2) >= size)
            {
                painter.setPen(textPen);
                painter.rotate(270);
                painter.drawText(-(yPos - 2), textBase, string);
                painter.rotate(-270);
                painter.setPen(linePen);
            }
        }
        else
        {
            painter.drawLine(lineLeft, yPos, lineRightMinor, yPos);
        }
        segIndex += 1;
        showValueBeginL += segValueSpanL;
    }
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRSpectroVAxisElement::onPaintMouseFeedback(QPainter&)
{
	//add code here
}
