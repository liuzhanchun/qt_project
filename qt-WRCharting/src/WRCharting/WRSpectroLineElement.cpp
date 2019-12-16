#include <WRCharting/WRSpectroLineElement.h>
#include <WRCharting/WRSpectroControl.h>
#include <QApplication>

//设置线条颜色。
void WRSpectroLineElement::setColor(WRColor value)
{
    if (m_color.change(value.red(), value.green(), value.blue()))
    {
        m_color = value;
        doUpdate();
        emit colorChanged(m_color);
    }
}
//设置可否移动。
void WRSpectroLineElement::setMoveable(bool value)
{
    if (value != readFlag(WRSPECTROLINEELEMENT_MOVEABLE))
    {
        writeFlag(WRSPECTROLINEELEMENT_MOVEABLE, value);
        emit moveableChanged(value);
    }
}

//设置线条颜色。
bool WRSpectroLineElement::color(WRColor value)
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
bool WRSpectroLineElement::moveable(bool value)
{
    if (value != readFlag(WRSPECTROLINEELEMENT_MOVEABLE))
    {
        writeFlag(WRSPECTROLINEELEMENT_MOVEABLE, value);
        emit moveableChanged(value);
        return true;
    }
    return false;
}

//获取元素标识。
WRSpectroGaugeElement::Type WRSpectroDataValueLineElement::type() const
{
	return DataValueLine;
}
//更新元素的布局。
void WRSpectroDataValueLineElement::arrange(void)
{
	WRSpectroControl* chart = (WRSpectroControl*)owner();
	WRSpectroDataViewElement* dataView = chart->dataView();
	if (!dataView->size().empty() && m_position >= chart->showDataValueBegin() && m_position <= chart->showDataValueEnd())
	{
		int y = chart->getDataValuePos(dataView->height(), m_position);
		this->doLayout(WRRect(dataView->left(), dataView->top() + y - 2, dataView->width(), 5));
		return;
	}
	this->doLayout(WRRect());
}

//键盘按下处理，如果需要重绘，则返回True。
bool WRSpectroDataValueLineElement::onKeyDown(const QKeyEvent& e)
{
	if (moveable() && ((e.modifiers() & Qt::ControlModifier) == Qt::ControlModifier))
	{
		double position = m_position;
		if (e.key() == Qt::Key_Up)
		{
			WRSpectroControl* chart = (WRSpectroControl*)owner();
			if (position < chart->showDataValueEnd())
			{
				WRSpectroDataViewElement* dataView = chart->dataView();
				position = chart->getDataValueAt(dataView->height(), top() + 1 - dataView->top());
			}
		}
		else if (e.key() == Qt::Key_Down)
		{
			WRSpectroControl* chart = (WRSpectroControl*)owner();
			if (position > chart->showDataValueBegin())
			{
				WRSpectroDataViewElement* dataView = chart->dataView();
				position = chart->getDataValueAt(dataView->height(), top() + 3 - dataView->top());
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
bool WRSpectroDataValueLineElement::onKeyUp(const QKeyEvent&)
{
	return false;
}

//鼠标按下处理，如果需要重绘，则返回True。
bool WRSpectroDataValueLineElement::onMouseDown(const QMouseEvent& e)
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
bool WRSpectroDataValueLineElement::onMouseUp(const QMouseEvent& e)
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
bool WRSpectroDataValueLineElement::onMouseMove(const QMouseEvent& e)
{
	if (moveable())
    {
        if (!mouseCursor())
        {
            QApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
            mouseCursor(true);
        }
		if (mouseCaptured())
		{
			WRSpectroControl* chart = (WRSpectroControl*)owner();
			WRSpectroDataViewElement* dataView = chart->dataView();
			int y = e.y() - dataView->top();
			if (y < 0)
			{
				y = 0;
			}
			else if (y >= dataView->height())
			{
				y = dataView->height() - 1;
			}
			double position = chart->getDataValueAt(dataView->height(), y);
			if (position != m_position)
			{
				m_position = position;
				arrange();
                emit positionUpdated(m_position);
                emit positionChanged(m_position);
			}
		}
	}
	return true;
}

//鼠标离开处理，如果需要重绘，则返回True。
bool WRSpectroDataValueLineElement::onMouseLeave(void)
{
    if (!mouseCaptured() && mouseCursor())
    {
        QApplication::restoreOverrideCursor();
        mouseCursor(false);
    }
    return false;
}

//执行绘制处理。
void WRSpectroDataValueLineElement::onPaint(QPainter& painter)
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
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRSpectroDataValueLineElement::onPaintMouseFeedback(QPainter&)
{
	//add code ehre
}

//设置数据索引。
void WRSpectroDataValueLineElement::setPosition(double value)
{
    if (value != m_position)
    {
        m_position = value;
        WRSpectroControl* chart = (WRSpectroControl*)owner();
        if (chart && chart->effect())
        {
            arrange();
            chart->invalidate();
        }
        emit positionChanged(m_position);
    }
}
//设置数据索引。
bool WRSpectroDataValueLineElement::position(double value)
{
	if (value != m_position)
	{
		m_position = value;
		WRSpectroControl* chart = (WRSpectroControl*)owner();
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
WRSpectroGaugeElement::Type WRSpectroDataPointLineElement::type() const
{
	return DataPointLine;
}
//更新元素的布局。
void WRSpectroDataPointLineElement::arrange(void)
{
	WRSpectroControl* chart = (WRSpectroControl*)owner();
	WRSpectroDataViewElement* dataView = chart->dataView();
	if (!dataView->size().empty() && m_position >= chart->showDataPointBegin() && m_position <= chart->showDataPointEnd())
	{
		int x = chart->getDataPointPos(dataView->width(), m_position);
		this->doLayout(WRRect(dataView->left() + x - 2, dataView->top(), 5, dataView->height()));
		return;
	}
	this->doLayout(WRRect());
}

//键盘按下处理，如果需要重绘，则返回True。
bool WRSpectroDataPointLineElement::onKeyDown(const QKeyEvent& e)
{
	if (moveable() && ((e.modifiers() & Qt::ControlModifier) == Qt::ControlModifier))
	{
		int position = m_position;
		if (e.key() == Qt::Key_Left)
		{
			WRSpectroControl* chart = (WRSpectroControl*)owner();
			if (position > chart->showDataPointBegin())
			{
				WRSpectroDataViewElement* dataView = chart->dataView();
				if ((int)(dataView->width() * 2) <= chart->showDataPointCount())
				{
					position = chart->getDataPointAt(dataView->width(), left() + 1 - dataView->left());
				}
				else
				{
					--position;
				}
			}
		}
		else if (e.key() == Qt::Key_Right)
		{
			WRSpectroControl* chart = (WRSpectroControl*)owner();
			if (position < chart->showDataPointEnd())
			{
				WRSpectroDataViewElement* dataView = chart->dataView();
				if ((int)(dataView->width() * 2) <= chart->showDataPointCount())
				{
					position = chart->getDataPointAt(dataView->width(), left() + 3 - dataView->left());
				}
				else
				{
					++position;
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
bool WRSpectroDataPointLineElement::onKeyUp(const QKeyEvent&)
{
	return false;
}

//鼠标按下处理，如果需要重绘，则返回True。
bool WRSpectroDataPointLineElement::onMouseDown(const QMouseEvent& e)
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
bool WRSpectroDataPointLineElement::onMouseUp(const QMouseEvent& e)
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
bool WRSpectroDataPointLineElement::onMouseMove(const QMouseEvent& e)
{
	if (moveable())
    {
        if (!mouseCursor())
        {
            QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
            mouseCursor(true);
        }
		if (mouseCaptured())
		{
			WRSpectroControl* chart = (WRSpectroControl*)owner();
			WRSpectroDataViewElement* dataView = chart->dataView();
			int x = e.x() - dataView->left();
			if (x < 0)
			{
				x = 0;
			}
			else if (x >= dataView->width())
			{
				x = dataView->width() - 1;
			}
			int position = chart->getDataPointAt(dataView->width(), x);
			if (position != m_position)
			{
				m_position = position;
				arrange();
                emit positionUpdated(m_position);
                emit positionChanged(m_position);
			}
		}
	}
	return true;
}

//鼠标离开处理，如果需要重绘，则返回True。
bool WRSpectroDataPointLineElement::onMouseLeave(void)
{
    if (!mouseCaptured() && mouseCursor())
    {
        QApplication::restoreOverrideCursor();
        mouseCursor(false);
    }
    return false;
}

//执行绘制处理。
void WRSpectroDataPointLineElement::onPaint(QPainter& painter)
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
//执行所有绘制后，如果元素捕获了鼠标或者鼠标正处于此元素之上，将调用此方法进行相应的绘制处理。
void WRSpectroDataPointLineElement::onPaintMouseFeedback(QPainter&)
{
    //add code here
}

//设置数据索引。
void WRSpectroDataPointLineElement::setPosition(int value)
{
    if (value != m_position)
    {
        m_position = value;
        WRSpectroControl* chart = (WRSpectroControl*)owner();
        if (chart && chart->effect())
        {
            arrange();
            chart->invalidate();
        }
        emit positionChanged(m_position);
    }
}
//设置数据索引。
bool WRSpectroDataPointLineElement::position(int value)
{
	if (value != m_position)
	{
		m_position = value;		
		WRSpectroControl* chart = (WRSpectroControl*)owner();
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

