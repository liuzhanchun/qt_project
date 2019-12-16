#include <WRCharting/WRWaterfallLineElement.h>
#include <WRCharting/WRWaterfallControl.h>
#include <QApplication>

//设置线条颜色。
void WRWaterfallLineElement::setColor(WRColor value)
{
    if (m_color.change(value.red(), value.green(), value.blue()))
    {
        m_color = value;
        doUpdate();
        emit colorChanged(m_color);
    }
}
//设置可否移动。
void WRWaterfallLineElement::setMoveable(bool value)
{
    if (value != readFlag(WRWATERFALLLINEELEMENT_MOVEABLE))
    {
        writeFlag(WRWATERFALLLINEELEMENT_MOVEABLE, value);
        emit moveableChanged(value);
    }
}

//设置线条颜色。
bool WRWaterfallLineElement::color(WRColor value)
{
	if (m_color.change(value.red(), value.green(), value.blue()))
	{
		m_color = value;
		doUpdate();
        emit colorChanged(m_color);
		return true;
	}
	return false;
}
//设置可否移动。
bool WRWaterfallLineElement::moveable(bool value)
{
    if (value != readFlag(WRWATERFALLLINEELEMENT_MOVEABLE))
    {
        writeFlag(WRWATERFALLLINEELEMENT_MOVEABLE, value);
        emit moveableChanged(value);
        return true;
    }
    return false;
}

//绘制水平线条。
void WRWaterfallLineElement::hLine(QPainter& painter)
{
    QPen pen(m_color);
    painter.setPen(pen);

    int y = this->top() + 2;
    int r = this->right();

    QPoint points[3];
    QPoint* p = points;
    p->setX(this->left());
    p->setY(y);
    ++p;
    p->setX(r);
    p->setY(y);
    painter.drawLine(points[0], points[1]);

    if (focused())
    {
        QBrush brush(m_color);
        painter.setBrush(brush);

        p = points;
        p->setX(this->left() + 8);
        p->setY(y);
        ++p;
        p->setX(this->left());
        p->setY(y - 4);
        ++p;
        p->setX(this->left());
        p->setY(y + 5);
        painter.drawPolygon(points, 3);

        r -= 1;
        p = points;
        p->setX(r - 8);
        ++p;
        p->setX(r);
        ++p;
        p->setX(r);
        painter.drawPolygon(points, 3);
    }
}
//绘制垂直线条。
void WRWaterfallLineElement::vLine(QPainter& painter)
{
    QPen pen(m_color);
    painter.setPen(pen);

    int x = this->left() + 2;
    int b = this->bottom();

    QPoint points[3];
    QPoint* p = points;
    p->setX(x);
    p->setY(this->top());
    ++p;
    p->setX(x);
    p->setY(b);
    painter.drawLine(points[0], points[1]);

    if (focused())
    {
        QBrush brush(m_color);
        painter.setBrush(brush);

        p = points;
        p->setX(x);
        p->setY(this->top() + 8);
        ++p;
        p->setX(x - 4);
        p->setY(this->top());
        ++p;
        p->setX(x + 4);
        p->setY(this->top());
        painter.drawPolygon(points, 3);

        b -= 1;
        p = points;
        p->setY(b - 8);
        ++p;
        p->setY(b);
        ++p;
        p->setY(b);
        painter.drawPolygon(points, 3);
    }
}

//获取元素标识。
WRWaterfallGaugeElement::Type WRWaterfallDataFrameLineElement::type() const
{
	return DataFrameLine;
}
//更新元素的布局。
void WRWaterfallDataFrameLineElement::arrange(void)
{
	WRWaterfallControl* chart = (WRWaterfallControl*)owner();
	WRWaterfallDataViewElement* dataView = chart->dataView();
	if (!dataView->size().empty() && m_position >= chart->showDataFrameBegin() && m_position <= chart->showDataFrameEnd())
	{
		if (chart->vertical())
		{
			int y = chart->getVDataFramePos(dataView->height(), m_position);
			this->doLayout(WRRect(dataView->left(), dataView->top() + y - 2, dataView->width(), 5));
		}
		else
		{
			int x = chart->getHDataFramePos(dataView->width(), m_position);
			this->doLayout(WRRect(dataView->left() + x - 2, dataView->top(),  5, dataView->height()));
		}
		return;
	}
	this->doLayout(WRRect());
}

//键盘按下处理，如果需要重绘，则返回True。
bool WRWaterfallDataFrameLineElement::onKeyDown(const QKeyEvent& e)
{
	if (moveable() && ((e.modifiers() & Qt::ControlModifier) == Qt::ControlModifier))
	{
		int position = m_position;
		WRWaterfallControl* chart = (WRWaterfallControl*)owner();
		if (chart->vertical())
		{
			if (e.key() == Qt::Key_Up)
			{
				if (position > chart->showDataFrameBegin())
				{
					WRWaterfallDataViewElement* dataView = chart->dataView();
					if ((int)(dataView->height() * 2) <= chart->showDataFrameCount())
					{
						position = chart->getHDataFrameAt(dataView->height(), top() + 1 - dataView->top());
					}
					else
					{
						--position;
					}
				}
			}
			else if (e.key() == Qt::Key_Down)
			{
				WRWaterfallControl* chart = (WRWaterfallControl*)owner();
				if (position < chart->showDataFrameEnd())
				{
					WRWaterfallDataViewElement* dataView = chart->dataView();
					if ((int)(dataView->height() * 2) <= chart->showDataFrameCount())
					{
						position = chart->getHDataFrameAt(dataView->height(), top() + 3 - dataView->top());
					}
					else
					{
						++position;
					}
				}
			}
		}
		else
		{
			if (e.key() == Qt::Key_Left)
			{
				if (position > chart->showDataFrameBegin())
				{
					WRWaterfallDataViewElement* dataView = chart->dataView();
					if ((int)(dataView->width() * 2) <= chart->showDataFrameCount())
					{
						position = chart->getVDataFrameAt(dataView->width(), left() + 1 - dataView->left());
					}
					else
					{
						--position;
					}
				}
			}
			else if (e.key() == Qt::Key_Right)
			{
				WRWaterfallControl* chart = (WRWaterfallControl*)owner();
				if (position < chart->showDataFrameEnd())
				{
					WRWaterfallDataViewElement* dataView = chart->dataView();
					if ((int)(dataView->width() * 2) <= chart->showDataFrameCount())
					{
						position = chart->getVDataFrameAt(dataView->width(), left() + 3 - dataView->left());
					}
					else
					{
						++position;
					}
				}
			}
		}
		if (position != m_position)
		{
			m_position = position;
			arrange();            
            emit positionUpdated(m_position);
            emit positionChanged(m_position);
			return true;
		}
	}
	return false;
}
//键盘释放处理，如果需要重绘，则返回True。
bool WRWaterfallDataFrameLineElement::onKeyUp(const QKeyEvent&)
{
	return false;
}

//鼠标按下处理，如果需要重绘，则返回True。
bool WRWaterfallDataFrameLineElement::onMouseDown(const QMouseEvent& e)
{
	if (moveable())
	{
		if (e.button() == Qt::LeftButton)
        {
			setCapture();
		}
	}
	return true;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRWaterfallDataFrameLineElement::onMouseUp(const QMouseEvent& e)
{
	if (e.button() == Qt::LeftButton)
	{
		if (mouseCaptured())
        {
			releaseCapture();
            if (!mouseHovered() && mouseCursor())
            {
                QApplication::restoreOverrideCursor();
                mouseCursor(false);
            }
		}
	}
	return true;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRWaterfallDataFrameLineElement::onMouseMove(const QMouseEvent& e)
{
	if (moveable())
	{
		WRWaterfallControl* chart = (WRWaterfallControl*)owner();
		if (chart->vertical())
        {
            if (!mouseCursor())
            {
                QApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
                mouseCursor(true);
            }
			if (mouseCaptured())
			{
				WRWaterfallDataViewElement* dataView = chart->dataView();
				int y = e.y() - dataView->top();
				if (y < 0)
				{
					y = 0;
				}
				else if (y >= dataView->height())
				{
					y = dataView->height() - 1;
				}
				int position = chart->getVDataFrameAt(dataView->height(), y);
				if (position != m_position)
				{
					m_position = position;
					arrange();                    
                    emit positionUpdated(m_position);
                    emit positionChanged(m_position);
				}
			}
		}
		else
        {
            if (!mouseCursor())
            {
                QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
                mouseCursor(true);
            }
			if (mouseCaptured())
			{
				WRWaterfallDataViewElement* dataView = chart->dataView();
				int x = e.x() - dataView->left();
				if (x < 0)
				{
					x = 0;
				}
				else if (x >= dataView->width())
				{
					x = dataView->width() - 1;
				}
				int position = chart->getHDataFrameAt(dataView->width(), x);
				if (position != m_position)
				{
					m_position = position;
					arrange();
                    emit positionUpdated(m_position);
                    emit positionChanged(m_position);
				}
			}
		}
	}
	return true;
}

//鼠标离开处理，如果需要重绘，则返回True。
bool WRWaterfallDataFrameLineElement::onMouseLeave(void)
{
    if (!mouseCaptured() && mouseCursor())
    {
        QApplication::restoreOverrideCursor();
        mouseCursor(false);
    }
    return false;
}

//执行绘制处理。
void WRWaterfallDataFrameLineElement::onPaint(QPainter& painter)
{
	WRWaterfallControl* chart = (WRWaterfallControl*)owner();
	if (chart->vertical())
	{
		hLine(painter);
	}
	else
	{
		vLine(painter);
	}
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRWaterfallDataFrameLineElement::onPaintMouseFeedback(QPainter&)
{
	//add code ehre
}

//设置数据索引。
void WRWaterfallDataFrameLineElement::setPosition(int value)
{
    if (value != m_position)
    {
        m_position = value;
        WRWaterfallControl* chart = (WRWaterfallControl*)owner();
        if (chart && chart->effect())
        {
            arrange();
            chart->invalidate();
        }
        emit positionChanged(m_position);
    }
}
//设置数据索引。
bool WRWaterfallDataFrameLineElement::position(int value)
{
	if (value != m_position)
	{
		m_position = value;
		WRWaterfallControl* chart = (WRWaterfallControl*)owner();
		if (chart && chart->effect())
		{
			arrange();
			chart->invalidate();
        }
        emit positionChanged(m_position);
		return true;
	}
	return false;
}

//获取元素标识。
WRWaterfallGaugeElement::Type WRWaterfallDataPointLineElement::type() const
{
	return DataPointLine;
}
//更新元素的布局。
void WRWaterfallDataPointLineElement::arrange(void)
{
	WRWaterfallControl* chart = (WRWaterfallControl*)owner();
	WRWaterfallDataViewElement* dataView = chart->dataView();
	if (!dataView->size().empty() && m_position >= chart->showDataPointBegin() && m_position <= chart->showDataPointEnd())
	{
		if (chart->vertical())
		{
			int x = chart->getVDataPointPos(dataView->width(), m_position);
			this->doLayout(WRRect(dataView->left() + x - 2, dataView->top(), 5, dataView->height()));
		}
		else
		{
			int y = chart->getHDataPointPos(dataView->height(), m_position);
			this->doLayout(WRRect(dataView->left(), dataView->top() + y - 2, dataView->width(), 5));
		}
		return;
	}
	this->doLayout(WRRect());
}

//键盘按下处理，如果需要重绘，则返回True。
bool WRWaterfallDataPointLineElement::onKeyDown(const QKeyEvent& e)
{
	if (moveable() && ((e.modifiers() & Qt::ControlModifier) == Qt::ControlModifier))
	{
		WRWaterfallControl* chart = (WRWaterfallControl*)owner();
		int position = m_position;
		if (chart->vertical())
		{
			if (e.key() == Qt::Key_Left)
			{
				if (position > chart->showDataPointBegin())
				{
					WRWaterfallDataViewElement* dataView = chart->dataView();
					if ((int)(dataView->width() * 2) <= chart->showDataPointCount())
					{
						position = chart->getVDataPointAt(dataView->width(), left() + 1 - dataView->left());
					}
					else
					{
						--position;
					}
				}
			}
			else if (e.key() == Qt::Key_Right)
			{
				WRWaterfallControl* chart = (WRWaterfallControl*)owner();
				if (position < chart->showDataPointEnd())
				{
					WRWaterfallDataViewElement* dataView = chart->dataView();
					if ((int)(dataView->width() * 2) <= chart->showDataPointCount())
					{
						position = chart->getVDataPointAt(dataView->width(), left() + 3 - dataView->left());
					}
					else
					{
						++position;
					}
				}
			}
		}
		else
		{
			if (e.key() == Qt::Key_Up)
			{
				if (position > chart->showDataPointBegin())
				{
					WRWaterfallDataViewElement* dataView = chart->dataView();
					if ((int)(dataView->height() * 2) <= chart->showDataPointCount())
					{
						position = chart->getHDataPointAt(dataView->height(), top() + 1 - dataView->top());
					}
					else
					{
						++position;
					}
				}
			}
			else if (e.key() == Qt::Key_Down)
			{
				WRWaterfallControl* chart = (WRWaterfallControl*)owner();
				if (position < chart->showDataPointEnd())
				{
					WRWaterfallDataViewElement* dataView = chart->dataView();
					if ((int)(dataView->height() * 2) <= chart->showDataPointCount())
					{
						position = chart->getHDataPointAt(dataView->height(), top() + 3 - dataView->top());
					}
					else
					{
						--position;
					}
				}
			}
		}
		if (position != m_position)
		{
			m_position = position;
            arrange();
            emit positionUpdated(m_position);
            emit positionChanged(m_position);
			return true;
		}
	}
	return false;
}
//键盘释放处理，如果需要重绘，则返回True。
bool WRWaterfallDataPointLineElement::onKeyUp(const QKeyEvent&)
{
	return false;
}

//鼠标按下处理，如果需要重绘，则返回True。
bool WRWaterfallDataPointLineElement::onMouseDown(const QMouseEvent& e)
{
	if (moveable())
	{
		if (e.button() == Qt::LeftButton)
        {
			setCapture();
		}
	}
	return true;
}
//鼠标释放处理，如果需要重绘，则返回True。
bool WRWaterfallDataPointLineElement::onMouseUp(const QMouseEvent& e)
{
	if (e.button() == Qt::LeftButton)
	{
		if (mouseCaptured())
        {
			releaseCapture();
            if (!mouseHovered() && mouseCursor())
            {
                QApplication::restoreOverrideCursor();
                mouseCursor(false);
            }
		}
	}
	return true;
}
//鼠标移动处理，如果需要重绘，则返回True。
bool WRWaterfallDataPointLineElement::onMouseMove(const QMouseEvent& e)
{
	if (moveable())
	{
		WRWaterfallControl* chart = (WRWaterfallControl*)owner();
		if (chart->vertical())
        {
            if (!mouseCursor())
            {
                QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
                mouseCursor(true);
            }
			if (mouseCaptured())
			{
				WRWaterfallDataViewElement* dataView = chart->dataView();
				int x = e.x() - dataView->left();
				if (x < 0)
				{
					x = 0;
				}
				else if (x >= dataView->width())
				{
					x = dataView->width() - 1;
				}
				int position = chart->getVDataPointAt(dataView->width(), x);
				if (position != m_position)
				{
					m_position = position;
                    arrange();
                    emit positionUpdated(m_position);
                    emit positionChanged(m_position);
				}
			}
		}
		else
        {
            if (!mouseCursor())
            {
                QApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
                mouseCursor(true);
            }
			if (mouseCaptured())
			{
				WRWaterfallDataViewElement* dataView = chart->dataView();
				int y = e.y() - dataView->top();
				if (y < 0)
				{
					y = 0;
				}
				else if (y >= dataView->height())
				{
					y = dataView->height() - 1;
				}
				int position = chart->getHDataPointAt(dataView->height(), y);
				if (position != m_position)
				{
					m_position = position;
                    arrange();
                    emit positionUpdated(m_position);
                    emit positionChanged(m_position);
				}
			}
		}
	}
	return true;
}

//鼠标离开处理，如果需要重绘，则返回True。
bool WRWaterfallDataPointLineElement::onMouseLeave(void)
{
    if (!mouseCaptured() && mouseCursor())
    {
        QApplication::restoreOverrideCursor();
        mouseCursor(false);
    }
    return false;
}

//执行绘制处理。
void WRWaterfallDataPointLineElement::onPaint(QPainter& painter)
{
	WRWaterfallControl* chart = (WRWaterfallControl*)owner();
	if (chart->vertical())
	{
		vLine(painter);
	}
	else
	{
		hLine(painter);
	}
}
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRWaterfallDataPointLineElement::onPaintMouseFeedback(QPainter&)
{
	//add code here
}

//设置数据索引。
void WRWaterfallDataPointLineElement::setPosition(int value)
{
    if (value != m_position)
    {
        m_position = value;
        WRWaterfallControl* chart = (WRWaterfallControl*)owner();
        if (chart && chart->effect())
        {
            arrange();
            chart->invalidate();
        }
        emit positionChanged(m_position);
    }
}
//设置数据索引。
bool WRWaterfallDataPointLineElement::position(int value)
{
	if (value != m_position)
	{
		m_position = value;		
		WRWaterfallControl* chart = (WRWaterfallControl*)owner();
		if (chart && chart->effect())
		{
			arrange();
			chart->invalidate();
        }
        emit positionChanged(m_position);
		return true;
	}
	return false;
}

