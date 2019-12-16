#include <WRCharting/WROscilloAxisElement.h>
#include <WRCharting/WROscilloControl.h>
#include <WRCharting/WRText.h>

//鼠标按下处理，如果需要重绘，则返回True。
bool WROscilloHAxisElement::onMouseDown(const QMouseEvent& e)
{
    if (e.button() == Qt::LeftButton)
	{
        mouseSavePos(e.pos());
		setCapture();
	}
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WROscilloHAxisElement::onMouseUp(const QMouseEvent& e)
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
bool WROscilloHAxisElement::onMouseMove(const QMouseEvent& e)
{
	if (mouseCaptured())
	{
		WROscilloControl* chart = (WROscilloControl*)owner();
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
bool WROscilloHAxisElement::onMouseDoubleClick(const QMouseEvent& e)
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
			WROscilloControl* chart = (WROscilloControl*)owner();
			WRChartSampleRange showPointRange(chart->showDataPointRange());
            chart->doMouseWheelH(showPointRange, e.x() - left(), delta, width());
			return chart->changeShowDataPointRange(showPointRange);
		}
	}
	return false;
}

//鼠标滚动处理。
bool WROscilloHAxisElement::onMouseWheel(const QWheelEvent& e)
{
    if (scalable())
    {
        WROscilloControl* chart = (WROscilloControl*)owner();
        WRChartSampleRange showPointRange(chart->showDataPointRange());
        chart->doMouseWheelH(showPointRange, e.x() - left(), e.delta(), width());
        return chart->changeShowDataPointRange(showPointRange);
    }
    return false;
}

//执行横坐标轴绘制处理。
void WROscilloHAxisElement::onPaint(QPainter& painter)
{
    WROscilloControl* chart = (WROscilloControl*)owner();
    WROscilloDataSource* dataSource = chart->dataSource();
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
    int lineRight, lineTop, lineBottomMain, lineBottomMinor , textBase;
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
    int segPointCount = chart->getDataPointOffsetAt(width(), 20);
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
    int showPointBegin;
    int segPointIndex;
    if (dataSource->points() < dataSource->capacity())
    {
        showPointBegin = (int)(dataSource->capacity() - dataSource->points());
        segPointIndex = 0;
        while (showPointBegin < chart->showDataPointBegin())
        {
            showPointBegin += segPointCount;
            ++segPointIndex;
        }
    }
    else
    {
        showPointBegin = chart->showDataPointBegin();
        long long frameIndex = dataSource->points() - dataSource->capacity() + chart->showDataPointBegin();
        int segStart = (int)(frameIndex % segPointCount);
        segPointIndex = (int)(frameIndex / segPointCount);
        if (segStart != 0)
        {
            showPointBegin += segPointCount - segStart;
            ++segPointIndex;
        }
    }
    int showPointEnd = chart->showDataPointEnd();
    //执行坐标轴绘制
    char buffer1[256];
    QChar buffer2[256] = { '0', '0', ':', '0', '0', ':', '0', '0', '.', '0', '0', '0', '0', '0', '0', '0', '\0' };
    QString string = QString::fromRawData(buffer2, 16);
    QFontMetrics fontMetrics(font);
    int size = fontMetrics.width(string);
    int xPos = chart->getDataPointOffsetPos(width(), segPointCount);
    int mainSpan = (size + 32 + xPos - 1) / xPos;
    if (mainSpan < 1)
    {
        mainSpan = 1;
    }
    while (showPointBegin < showPointEnd)
    {
        xPos = chart->getDataPointPos(width(), showPointBegin);
        if (segPointIndex % mainSpan == 0)
        {
            //绘制刻度线
            painter.drawLine(xPos, lineTop, xPos, lineBottomMain);
            //绘制刻度值
            int length = WRText::toTimeString(dataSource->getTimeValue(showPointBegin), buffer1);
            WRText::copy(buffer1, buffer2, length);
            string = QString::fromRawData(buffer2, 16);
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
        segPointIndex += 1;
        showPointBegin += segPointCount;
    }
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WROscilloHAxisElement::onPaintMouseFeedback(QPainter&)
{
	//add code here
}


//鼠标按下处理，如果需要重绘，则返回True。
bool WROscilloVAxisElement::onMouseDown(const QMouseEvent& e)
{
    if (e.button() == Qt::LeftButton)
	{
        mouseSavePos(e.pos());
		setCapture();
	}
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WROscilloVAxisElement::onMouseUp(const QMouseEvent& e)
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
bool WROscilloVAxisElement::onMouseMove(const QMouseEvent& e)
{
	if (mouseCaptured())
	{
		WROscilloControl* chart = (WROscilloControl*)owner();
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
bool WROscilloVAxisElement::onMouseDoubleClick(const QMouseEvent& e)
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
			WROscilloControl* chart = (WROscilloControl*)owner();
			WRChartDValueRange showValueRange(chart->showDataValueRange());
            chart->doMouseWheelV(showValueRange, e.y() - top(), delta, height());
			return chart->changeShowDataValueRange(showValueRange);
		}
	}
	return false;
}

//鼠标滚动处理。
bool WROscilloVAxisElement::onMouseWheel(const QWheelEvent& e)
{
    if (scalable())
    {
        WROscilloControl* chart = (WROscilloControl*)owner();
        WRChartDValueRange showValueRange(chart->showDataValueRange());
        chart->doMouseWheelV(showValueRange, e.y() - top(), e.delta(), height());
        return chart->changeShowDataValueRange(showValueRange);
    }
    return false;
}

//执行纵坐标轴绘制处理。
void WROscilloVAxisElement::onPaint(QPainter& painter)
{
    WROscilloControl* chart = (WROscilloControl*)owner();
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
    int lineLeft, lineBottom, lineRightMain, lineRightMinor;
    lineBottom = height() - 1;
    if (dockLeft())
    {
        lineLeft = width() - 1;
        lineRightMain = lineLeft - 13;
        lineRightMinor = lineLeft - 4;
        painter.drawLine(lineLeft, 0, lineLeft, lineBottom);//绘制坐标轴线
        lineLeft -= 1;
    }
    else
    {
        lineLeft = 0;
        lineRightMain = 13;
        lineRightMinor = 4;
        painter.drawLine(lineLeft, 0, lineLeft, lineBottom);//绘制坐标轴线
        lineLeft += 1;
    }
    //绘制刻度信息
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
    double valueMultipleF = (double)valueMultiple;
    //
    if (chart->showDataValueEnd() > 0)
    {
        int textBase = dockLeft() ? -4 : -8;
        long long showValueBeginL = chart->showDataValueBegin() > 0 ? (long long)(chart->showDataValueBegin() * valueMultiple + 0.5) : 0;
        long long segValueStartL = showValueBeginL % segValueSpanL;
        if (segValueStartL != 0)
        {
            showValueBeginL += segValueSpanL - segValueStartL;
        }
        long long showValueEndL = (long long)(chart->showDataValueEnd() * valueMultiple + 0.5);
        //执行坐标轴绘制
        char buffer1[256];
        QChar buffer2[256];
        int length = WRText::toString(chart->showDataValueEnd(), buffer1, false);
        WRText::copy(buffer1, buffer2, length);
        QString string = QString::fromRawData(buffer2, length);
        QFontMetrics fontMetrics(font);
        int segHeight = fontMetrics.width(string);
        //
        int yPos = height() - 1 - chart->getDataValueOffsetPos(height(), segValueSpanL / valueMultipleF);
        int mainSpan = (segHeight + 8 + yPos - 1) / yPos;
        if (mainSpan < 1)
        {
            mainSpan = 1;
        }
        long long segIndex = showValueBeginL / segValueSpanL;
        if (segIndex == 0)
        {
            segIndex += 1;
            showValueBeginL += segValueSpanL;
        }
        while (showValueBeginL < showValueEndL)
        {
            double value = showValueBeginL / valueMultipleF;
            int yPos = chart->getDataValuePos(height(), value);
            if (segIndex % mainSpan == 0)
            {
                //绘制刻度线
                painter.drawLine(lineLeft, yPos, lineRightMain, yPos);
                //绘制刻度值
                length = WRText::toString(value, buffer1);
                WRText::copy(buffer1, buffer2, length);
                string = QString::fromRawData(buffer2, length);
                int size = fontMetrics.width(string);
                if ((height() - yPos - 2) >= size)
                {
                    painter.setPen(textPen);
                    painter.rotate(90);
                    painter.drawText(yPos + 2, textBase, string);
                    painter.rotate(-90);
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
    if (chart->showDataValueBegin() < 0)
    {
        int textBase = dockLeft() ? 12 : 16;
        long long showValueEndL = chart->showDataValueEnd() > 0 ? 0 : (long long)(chart->showDataValueEnd() * valueMultiple - 0.5);
        long long segValueStartL = showValueEndL % segValueSpanL;
        if (segValueStartL != 0)
        {
            showValueEndL -= segValueSpanL + segValueStartL;
        }
        long long showValueBeginL = (long long)(chart->showDataValueBegin() * valueMultiple - 0.5);
        //执行坐标轴绘制
        char buffer1[256];
        QChar buffer2[256];
        int length = WRText::toString(chart->showDataValueBegin(), buffer1, false);
        WRText::copy(buffer1, buffer2, length);
        QString string = QString::fromRawData(buffer2, length);
        QFontMetrics fontMetrics(font);
        int segHeight = fontMetrics.width(string);

        int yPos = height() - 1 - chart->getDataValueOffsetPos(height(), segValueSpanL / valueMultipleF);
        int mainSpan = (segHeight + 8 + yPos - 1) / yPos;
        if (mainSpan < 1)
        {
            mainSpan = 1;
        }
        //
        long long segIndex = showValueEndL / segValueSpanL;
        if (segIndex == 0)
        {
            segIndex -= 1;
            showValueEndL -= segValueSpanL;
        }
        while (showValueBeginL < showValueEndL)
        {
            double value = showValueEndL / valueMultipleF;
            int yPos = chart->getDataValuePos(height(), value);
            if (segIndex % mainSpan == 0)
            {
                //绘制刻度线
                painter.drawLine(lineLeft, yPos, lineRightMain, yPos);
                //绘制刻度值
                length = WRText::toString(value, buffer1);
                WRText::copy(buffer1, buffer2, length);
                string = QString::fromRawData(buffer2, length);
                int size = fontMetrics.width(string);
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
            segIndex -= 1;
            showValueEndL -= segValueSpanL;
        }
    }
    if (chart->showDataValueBegin() <= 0 && chart->showDataValueEnd() >= 0)
    {
        int textBase = dockLeft() ? 12 : 16;
        int yPos = chart->getDataValuePos(height(), 0);
        //绘制刻度线
        painter.drawLine(lineLeft, yPos, lineRightMinor, yPos);
        //绘制刻度值
        QChar buffer[1] = {'0'};
        QString string = QString::fromRawData(buffer, 1);
        QFontMetrics fontMetrics(font);
        int size = fontMetrics.width(string);
        int y2 = size / 2;
        if ((yPos - y2 >= 0) && (yPos + y2 <= height()))
        {
            painter.setPen(textPen);
            painter.rotate(270);
            painter.drawText(-(yPos + y2), textBase, string);
            painter.rotate(-270);
            painter.setPen(linePen);
        }
    }
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WROscilloVAxisElement::onPaintMouseFeedback(QPainter&)
{
	//add code here
}
