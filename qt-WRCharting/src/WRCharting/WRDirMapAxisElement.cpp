#include <WRCharting/WRDirMapAxisElement.h>
#include <WRCharting/WRDirMapControl.h>
#include <WRCharting/WRText.h>

//鼠标按下处理，如果需要重绘，则返回True。
bool WRDirMapHAxisElement::onMouseDown(const QMouseEvent& e)
{
	if (e.button() == Qt::LeftButton)
	{
        mouseSavePos(e.pos());
		setCapture();
	}
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRDirMapHAxisElement::onMouseUp(const QMouseEvent& e)
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
bool WRDirMapHAxisElement::onMouseMove(const QMouseEvent& e)
{
	if (mouseCaptured())
	{
		WRDirMapControl* chart = (WRDirMapControl*)owner();
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
bool WRDirMapHAxisElement::onMouseDoubleClick(const QMouseEvent& e)
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
			WRDirMapControl* chart = (WRDirMapControl*)owner();
			WRChartSampleRange showPointRange(chart->showDataPointRange());
			chart->doMouseWheelH(showPointRange, e.x() - left(), delta, width());
			return chart->changeShowDataPointRange(showPointRange);
		}
	}
	return false;
}

//鼠标滚动处理。
bool WRDirMapHAxisElement::onMouseWheel(const QWheelEvent& e)
{
	if (scalable())
	{
		WRDirMapControl* chart = (WRDirMapControl*)owner();
		WRChartSampleRange showPointRange(chart->showDataPointRange());
		chart->doMouseWheelH(showPointRange, e.x() - left(), e.delta(), width());
		return chart->changeShowDataPointRange(showPointRange);
	}
	return false;
}

//执行横坐标轴绘制处理。
void WRDirMapHAxisElement::onPaint(QPainter& painter)
{
	WRDirMapControl* chart = (WRDirMapControl*)owner();
	WRDirMapDataSource* dataSource = chart->dataSource();
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
void WRDirMapHAxisElement::onPaintMouseFeedback(QPainter&)
{
	//add code here
}


//鼠标按下处理，如果需要重绘，则返回True。
bool WRDirMapVAxisElement::onMouseDown(const QMouseEvent& e)
{
	if (e.button() == Qt::LeftButton)
	{
        mouseSavePos(e.pos());
		setCapture();
	}
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRDirMapVAxisElement::onMouseUp(const QMouseEvent& e)
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
bool WRDirMapVAxisElement::onMouseMove(const QMouseEvent& e)
{
	if (mouseCaptured())
	{
		WRDirMapControl* chart = (WRDirMapControl*)owner();
		WRChartDValueRange showAngleRange(chart->showDataAngleRange());
		chart->doMouseMoveV(showAngleRange, mouseSavePos().y(), mouseCurrPos().y(), height());
		if(chart->changeShowDataAngleRange(showAngleRange))
		{
            mouseSavePos(e.pos());
			return true;
		}
	}
    return false;
}

//鼠标双击处理，如果需要重绘，则返回True。
bool WRDirMapVAxisElement::onMouseDoubleClick(const QMouseEvent& e)
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
			WRDirMapControl* chart = (WRDirMapControl*)owner();
			WRChartDValueRange showAngleRange(chart->showDataAngleRange());
			chart->doMouseWheelV(showAngleRange, e.y() - top(), delta, height());
			return chart->changeShowDataAngleRange(showAngleRange);
		}
	}
	return false;
}

//鼠标滚动处理。
bool WRDirMapVAxisElement::onMouseWheel(const QWheelEvent& e)
{
    if (scalable())
    {
        WRDirMapControl* chart = (WRDirMapControl*)owner();
        WRChartDValueRange showAngleRange(chart->showDataAngleRange());
        chart->doMouseWheelV(showAngleRange, e.y() - top(), e.delta(), height());
        return chart->changeShowDataAngleRange(showAngleRange);
    }
    return false;
}

//执行纵坐标轴绘制处理。
void WRDirMapVAxisElement::onPaint(QPainter& painter)
{
    WRDirMapControl* chart = (WRDirMapControl*)owner();
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
    long long angleMultiple = 1;
    double segAngleSpan = chart->getDataAngleSpan(height(), 20);
    while (segAngleSpan < 1.0)
    {
        segAngleSpan *= 10;
        angleMultiple *= 10;
    }
    long long segAngleSpanL = (long long)(segAngleSpan + 1);
    if (segAngleSpanL > 10)
    {
        long long t1 = 100;
        long long t2 = 9;
        while (segAngleSpanL > t1)
        {
            t1 *= 10;
            t2 = t2 * 10 + 9;
        }
        t1 /= 10;
        segAngleSpanL = (segAngleSpanL + t2) / t1 * t1;
    }
    long long showAngleBeginL = (long long)((chart->showDataAngleBegin() - chart->angleMinValue()) * angleMultiple + 0.5);
    long long showAngleBeing2L = showAngleBeginL;
    long long segAngleStartL = showAngleBeginL % segAngleSpanL;
    if (segAngleStartL != 0)
    {
        showAngleBeginL += segAngleSpanL - segAngleStartL;
    }
    long long showAngleEndL = (long long)((chart->showDataAngleEnd() - chart->angleMinValue()) * angleMultiple + 0.5);
    double angleMultipleF = (double)angleMultiple;
    //执行坐标轴绘制
    char buffer1[256];
    QChar buffer2[256];
    //以最长数据值字符串长度作为刻度线的显示依据
    int length = WRText::toString(chart->showDataAngleBegin(), buffer1, false);
    WRText::copy(buffer1, buffer2, length);
    QString string = QString::fromRawData(buffer2, length);
    QFontMetrics fontMetrics(font);
    int size = fontMetrics.width(string);
    int segHeight = size;
    length = WRText::toString(chart->showDataAngleEnd(), buffer1, false);
    WRText::copy(buffer1, buffer2, length);
    string = QString::fromRawData(buffer2, length);
    size = fontMetrics.width(string);
    if (segHeight < size) segHeight = size;

    int yPos = height() - 1 - chart->getDataAngleOffsetPos(height(), segAngleSpanL / angleMultipleF);
    int mainSpan = (segHeight + 8 + yPos - 1) / yPos;
    if (mainSpan < 1)
    {
        mainSpan = 1;
    }
    long long segIndex = showAngleBeginL / segAngleSpanL;
    while (showAngleBeginL < showAngleEndL)
    {
        int yPos = chart->getDataAngleOffsetPos(height(), (showAngleBeginL - showAngleBeing2L) / angleMultipleF);
        if (segIndex % mainSpan == 0)
        {
            //绘制刻度线
            painter.drawLine(lineLeft, yPos, lineRightMain, yPos);
            //绘制刻度值
            length = WRText::toString(chart->angleMinValue() + showAngleBeginL / angleMultipleF, buffer1);
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
        showAngleBeginL += segAngleSpanL;
    }
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRDirMapVAxisElement::onPaintMouseFeedback(QPainter&)
{
	//add code here
}
