#include <WRCharting/WRWaterfallAxisElement.h>
#include <WRCharting/WRWaterfallControl.h>
#include <WRCharting/WRText.h>

//鼠标按下处理，如果需要重绘，则返回True。
bool WRWaterfallHAxisElement::onMouseDown(const QMouseEvent& e)
{
	if (e.button() == Qt::LeftButton)
	{
        mouseSavePos(e.pos());
		setCapture();
	}
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRWaterfallHAxisElement::onMouseUp(const QMouseEvent& e)
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
bool WRWaterfallHAxisElement::onMouseMove(const QMouseEvent& e)
{
	if (mouseCaptured())
	{
		WRWaterfallControl* chart = (WRWaterfallControl*)owner();
		if (chart->vertical())
		{
			WRChartSampleRange showPointRange(chart->showDataPointRange());
			chart->doVMouseMoveH(showPointRange, mouseSavePos().x(), mouseCurrPos().x(), width());
			if(chart->changeShowDataPointRange(showPointRange))
			{
				mouseSavePos(e.pos());
				return true;
			}
		}
		else
		{
			WRChartSampleRange showFrameRange(chart->showDataFrameRange());
			chart->doHMouseMoveH(showFrameRange, mouseSavePos().x(), mouseCurrPos().x(), width());
			if(chart->changeShowDataFrameRange(showFrameRange))
			{
				mouseSavePos(e.pos());
				return true;
			}
		}
	}
    return false;
}

//鼠标双击处理，如果需要重绘，则返回True。
bool WRWaterfallHAxisElement::onMouseDoubleClick(const QMouseEvent& e)
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
			WRWaterfallControl* chart = (WRWaterfallControl*)owner();
			if (chart->vertical())
			{
				WRChartSampleRange showPointRange(chart->showDataPointRange());
				chart->doVMouseWheelH(showPointRange, e.x() - left(), delta, width());
				return chart->changeShowDataPointRange(showPointRange);
			}
			else
			{
				WRChartSampleRange showFrameRange(chart->showDataFrameRange());
				chart->doHMouseWheelH(showFrameRange, e.x() - left(), delta, width());
				return chart->changeShowDataFrameRange(showFrameRange);
			}
		}
	}
	return false;
}

//鼠标滚动处理。
bool WRWaterfallHAxisElement::onMouseWheel(const QWheelEvent& e)
{
    if (scalable())
    {
        WRWaterfallControl* chart = (WRWaterfallControl*)owner();
        if (chart->vertical())
        {
            WRChartSampleRange showPointRange(chart->showDataPointRange());
            chart->doVMouseWheelH(showPointRange, e.x() - left(), e.delta(), width());
            return chart->changeShowDataPointRange(showPointRange);
        }
        else
        {
            WRChartSampleRange showFrameRange(chart->showDataFrameRange());
            chart->doHMouseWheelH(showFrameRange, e.x() - left(), e.delta(), width());
            return chart->changeShowDataFrameRange(showFrameRange);
        }
    }
    return false;
}

//执行横坐标轴绘制处理。
void WRWaterfallHAxisElement::onPaint(QPainter& painter)
{
	WRWaterfallControl* chart = (WRWaterfallControl*)owner();
	WRWaterfallDataSource* dataSource = chart->dataSource();
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
    //绘制刻度信息
	if (chart->vertical())
	{
		//计算刻度信息
		int segPointCount = chart->getVDataPointOffsetAt(width(), 20);
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
        int xPos = (int)(segPointCount * (width() - 1LL) / (chart->showDataPointCount() - 1.0) + 0.5);
        int mainSpan = (size + 8 + xPos - 1) / xPos;
		if (mainSpan < 1)
		{
			mainSpan = 1;
		}
		int segPointIndex = showPointBegin / segPointCount;
		while (showPointBegin < showPointEnd)
		{
			xPos = chart->getVDataPointPos(width(), showPointBegin);
            if (segPointIndex % mainSpan == 0)
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
			segPointIndex += 1;
			showPointBegin += segPointCount;
		}
	}
	else
	{
		//计算刻度信息
		int segFrameCount = chart->getHDataFrameOffsetAt(width(), 20);
		if (segFrameCount < 1)
		{
			segFrameCount = 1;
		}
		else if (segFrameCount < 10)
		{
			segFrameCount = (segFrameCount + 1) / 2 * 2;
		}
		else
		{
			int t1 = 100;
			int t2 = 9;
			while (segFrameCount > t1)
			{
				t1 *= 10;
				t2 = t2 * 10 + 9;
			}
			t1 /= 10;
			segFrameCount = (segFrameCount + t2) / t1 * t1;
		}
		int showFrameBegin;
		int segFrameIndex;
		if (dataSource->frames() < dataSource->capacity())
		{
			showFrameBegin = (int)(dataSource->capacity() - dataSource->frames());
			segFrameIndex = 0;
			while (showFrameBegin < chart->showDataFrameBegin())
			{
				showFrameBegin += segFrameCount;
				++segFrameIndex;
			}
		}
		else
		{
			showFrameBegin = chart->showDataFrameBegin();
			long long frameIndex = dataSource->frames() - dataSource->capacity() + chart->showDataFrameBegin();
			int segStart = (int)(frameIndex % segFrameCount);
			segFrameIndex = (int)(frameIndex / segFrameCount);
			if (segStart != 0)
			{
				showFrameBegin += segFrameCount - segStart;
				++segFrameIndex;
			}
		}
		int showFrameEnd = chart->showDataFrameEnd();
		//执行坐标轴绘制
        char buffer1[256];
        QChar buffer2[256] = { '0', '0', ':', '0', '0', ':', '0', '0', '.', '0', '0', '0', '0', '0', '0', '0', '\0' };
        QString string = QString::fromRawData(buffer2, 16);
        QFontMetrics fontMetrics(font);
        int size = fontMetrics.width(string);
        int xPos = chart->getHDataFrameOffsetPos(width(), segFrameCount);
        int mainSpan = (size + 32 + xPos - 1) / xPos;
		if (mainSpan < 1)
		{
			mainSpan = 1;
		}
		while (showFrameBegin < showFrameEnd)
		{
			xPos = chart->getHDataFramePos(width(), showFrameBegin);
            if (segFrameIndex % mainSpan == 0)
            {
                //绘制刻度线
                painter.drawLine(xPos, lineTop, xPos, lineBottomMain);
                //绘制刻度值
                int length = WRText::toTimeString(dataSource->getTimeValue(showFrameBegin), buffer1);
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
			segFrameIndex += 1;
			showFrameBegin += segFrameCount;
        }
    }
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRWaterfallHAxisElement::onPaintMouseFeedback(QPainter&)
{
	//add code here
}


//鼠标按下处理，如果需要重绘，则返回True。
bool WRWaterfallVAxisElement::onMouseDown(const QMouseEvent& e)
{
	if (e.button() == Qt::LeftButton)
	{
        mouseSavePos(e.pos());
		setCapture();
	}
	return false;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRWaterfallVAxisElement::onMouseUp(const QMouseEvent& e)
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
bool WRWaterfallVAxisElement::onMouseMove(const QMouseEvent& e)
{
	if (mouseCaptured())
	{
		WRWaterfallControl* chart = (WRWaterfallControl*)owner();
		if (chart->vertical())
		{
			WRChartSampleRange showFrameRange(chart->showDataFrameRange());
			chart->doVMouseMoveV(showFrameRange, mouseSavePos().y(), mouseCurrPos().y(), height());
			if(chart->changeShowDataFrameRange(showFrameRange))
			{
				mouseSavePos(e.pos());
				return true;
			}
		}
		else
		{
			WRChartSampleRange showPointRange(chart->showDataPointRange());
			chart->doHMouseMoveV(showPointRange, mouseSavePos().y(), mouseCurrPos().y(), height());
			if(chart->changeShowDataPointRange(showPointRange))
			{
				mouseSavePos(e.pos());
				return true;
			}
		}
	}
    return false;
}

//鼠标双击处理，如果需要重绘，则返回True。
bool WRWaterfallVAxisElement::onMouseDoubleClick(const QMouseEvent& e)
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
			WRWaterfallControl* chart = (WRWaterfallControl*)owner();
			if (chart->vertical())
			{
				WRChartSampleRange showFrameRange(chart->showDataFrameRange());
				chart->doVMouseWheelV(showFrameRange, e.y() - top(), delta, height());
				return chart->changeShowDataFrameRange(showFrameRange);
			}
			else
			{
				WRChartSampleRange showPointRange(chart->showDataPointRange());
				chart->doHMouseWheelV(showPointRange, e.y() - top(), delta, height());
				return chart->changeShowDataPointRange(showPointRange);
			}
		}
	}
	return false;
}

//鼠标滚动处理。
bool WRWaterfallVAxisElement::onMouseWheel(const QWheelEvent& e)
{
    if (scalable())
    {
        WRWaterfallControl* chart = (WRWaterfallControl*)owner();
        if (chart->vertical())
        {
            WRChartSampleRange showFrameRange(chart->showDataFrameRange());
            chart->doVMouseWheelV(showFrameRange, e.y() - top(), e.delta(), height());
            return chart->changeShowDataFrameRange(showFrameRange);
        }
        else
        {
            WRChartSampleRange showPointRange(chart->showDataPointRange());
            chart->doHMouseWheelV(showPointRange, e.y() - top(), e.delta(), height());
            return chart->changeShowDataPointRange(showPointRange);
        }
    }
    return false;
}

//执行纵坐标轴绘制处理。
void WRWaterfallVAxisElement::onPaint(QPainter& painter)
{
	WRWaterfallControl* chart = (WRWaterfallControl*)owner();
	WRWaterfallDataSource* dataSource = chart->dataSource();
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
	if (chart->vertical())
    {
        int textBase = dockLeft() ? -4 : -8;
        //计算刻度信息
        int segFrameCount = chart->getVDataFrameOffsetAt(height(), 20);
        if (segFrameCount < 1)
        {
            segFrameCount = 1;
        }
        else if (segFrameCount < 10)
        {
            segFrameCount = (segFrameCount + 1) / 2 * 2;
        }
        else
        {
            int t1 = 100;
            int t2 = 9;
            while (segFrameCount > t1)
            {
                t1 *= 10;
                t2 = t2 * 10 + 9;
            }
            t1 /= 10;
            segFrameCount = (segFrameCount + t2) / t1 * t1;
        }
        int showFrameBegin;
        int segFrameIndex;
        if (dataSource->frames() < dataSource->capacity())
        {
            showFrameBegin = (int)(dataSource->capacity() - dataSource->frames());
            segFrameIndex = 0;
            while (showFrameBegin < chart->showDataFrameBegin())
            {
                showFrameBegin += segFrameCount;
                ++segFrameIndex;
            }
        }
        else
        {
            showFrameBegin = chart->showDataFrameBegin();
            long long frameIndex = dataSource->frames() - dataSource->capacity() + chart->showDataFrameBegin();
            int segStart = (int)(frameIndex % segFrameCount);
            segFrameIndex = (int)(frameIndex / segFrameCount);
            if (segStart != 0)
            {
                showFrameBegin += segFrameCount - segStart;
                ++segFrameIndex;
            }
        }
        int showFrameEnd = chart->showDataFrameEnd();
        //执行坐标轴绘制
        char buffer1[256];
        QChar buffer2[256] = { '0', '0', ':', '0', '0', ':', '0', '0', '.', '0', '0', '0', '0', '0', '0', '0', '\0' };
        QString string = QString::fromRawData(buffer2, 16);
        QFontMetrics fontMetrics(font);
        int size = fontMetrics.width(string);
        int yPos = chart->getHDataFrameOffsetPos(height(), segFrameCount);
        int mainSpan = (size + 32 + yPos - 1) / yPos;
        if (mainSpan < 1)
        {
            mainSpan = 1;
        }
        while (showFrameBegin < showFrameEnd)
        {
            yPos = chart->getVDataFramePos(height(), showFrameBegin);
            if (segFrameIndex % mainSpan == 0)
            {
                //绘制刻度线
                painter.drawLine(lineLeft, yPos, lineRightMain, yPos);
                //绘制刻度值
                int length = WRText::toTimeString(dataSource->getTimeValue(showFrameBegin), buffer1);
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
            segFrameIndex += 1;
            showFrameBegin += segFrameCount;
        }
	}
	else
    {
        int textBase = dockLeft() ? 12 : 16;
        //计算刻度信息
        int segPointCount = chart->getHDataPointOffsetAt(height(), height() - 21);
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
        int yPos = height() - 1 - chart->getHDataPointOffsetPos(height(), segPointCount);
        int mainSpan = (size + 8 + yPos - 1) / yPos;
        if (mainSpan < 1)
        {
            mainSpan = 1;
        }
        int segIndex = showPointBegin / segPointCount;
        while (showPointBegin < showPointEnd)
        {
            yPos = chart->getHDataPointPos(height(), showPointBegin);
            if (segIndex % mainSpan == 0)
            {
                //绘制刻度线
                painter.drawLine(lineLeft, yPos, lineRightMain, yPos);
                //绘制刻度值
                length = WRText::toFreqString(dataSource->getFreqValue(showPointBegin), buffer1);
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
            segIndex += 1;
            showPointBegin += segPointCount;
        }
	}
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRWaterfallVAxisElement::onPaintMouseFeedback(QPainter&)
{
	//add code here
}
