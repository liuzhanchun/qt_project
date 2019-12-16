#include <WRCharting/WRDirMapLineElement.h>
#include <WRCharting/WRDirMapControl.h>
#include <QApplication>

//设置线条颜色。
void WRDirMapLineElement::setColor(WRColor value)
{
    if (m_color.change(value.red(), value.green(), value.blue()))
    {
        m_color = value;
        doUpdate();
        emit colorChanged(m_color);
    }
}
//设置可否移动。
void WRDirMapLineElement::setMoveable(bool value)
{
    if (value != readFlag(WRDIRMAPLINEELEMENT_MOVEABLE))
    {
        writeFlag(WRDIRMAPLINEELEMENT_MOVEABLE, value);
        emit moveableChanged(value);
    }
}

//设置线条颜色。
bool WRDirMapLineElement::color(WRColor value)
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
bool WRDirMapLineElement::moveable(bool value)
{
    if (value != readFlag(WRDIRMAPLINEELEMENT_MOVEABLE))
    {
        writeFlag(WRDIRMAPLINEELEMENT_MOVEABLE, value);
        emit moveableChanged(value);
        return true;
    }
    return false;
}

//获取元素标识。
WRDirMapGaugeElement::Type WRDirMapDataAngleLineElement::type() const
{
	return DataAngleLine;
}
//更新元素的布局。
void WRDirMapDataAngleLineElement::arrange(void)
{
	WRDirMapControl* chart = (WRDirMapControl*)owner();
	WRDirMapDataViewElement* dataView = chart->dataView();
	if (!dataView->size().empty() && m_position >= chart->showDataAngleBegin() && m_position <= chart->showDataAngleEnd())
	{
		int y = chart->getDataAnglePos(dataView->height(), m_position);
		this->doLayout(WRRect(dataView->left(), dataView->top() + y - 2, dataView->width(), 5));
		return;
	}
	this->doLayout(WRRect());
}

//键盘按下处理，如果需要重绘，则返回True。
bool WRDirMapDataAngleLineElement::onKeyDown(const QKeyEvent& e)
{
	if (moveable() && ((e.modifiers() & Qt::ControlModifier) == Qt::ControlModifier))
	{
		double position = m_position;
		if (e.key() == Qt::Key_Up)
		{
			WRDirMapControl* chart = (WRDirMapControl*)owner();
			if (position < chart->showDataAngleEnd())
			{
				WRDirMapDataViewElement* dataView = chart->dataView();
				position = chart->getDataAngleAt(dataView->height(), top() + 1 - dataView->top());
			}
		}
		else if (e.key() == Qt::Key_Down)
		{
			WRDirMapControl* chart = (WRDirMapControl*)owner();
			if (position > chart->showDataAngleBegin())
			{
				WRDirMapDataViewElement* dataView = chart->dataView();
				position = chart->getDataAngleAt(dataView->height(), top() + 3 - dataView->top());
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
bool WRDirMapDataAngleLineElement::onKeyUp(const QKeyEvent&)
{
	return false;
}

//鼠标按下处理，如果需要重绘，则返回True。
bool WRDirMapDataAngleLineElement::onMouseDown(const QMouseEvent& e)
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
bool WRDirMapDataAngleLineElement::onMouseUp(const QMouseEvent& e)
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
bool WRDirMapDataAngleLineElement::onMouseMove(const QMouseEvent& e)
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
			WRDirMapControl* chart = (WRDirMapControl*)owner();
			WRDirMapDataViewElement* dataView = chart->dataView();
			int y = e.y() - dataView->top();
			if (y < 0)
			{
				y = 0;
			}
			else if (y >= dataView->height())
			{
				y = dataView->height() - 1;
			}
			double position = chart->getDataAngleAt(dataView->height(), y);
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
bool WRDirMapDataAngleLineElement::onMouseLeave(void)
{
    if (!mouseCaptured() && mouseCursor())
    {
        QApplication::restoreOverrideCursor();
        mouseCursor(false);
    }
    return false;
}

//执行绘制处理。
void WRDirMapDataAngleLineElement::onPaint(QPainter& painter)
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
void WRDirMapDataAngleLineElement::onPaintMouseFeedback(QPainter&)
{
	//add code ehre
}

//设置数据索引。
void WRDirMapDataAngleLineElement::setPosition(double value)
{
    if (value != m_position)
    {
        m_position = value;
        WRDirMapControl* chart = (WRDirMapControl*)owner();
        if (chart && chart->effect())
        {
            arrange();
            chart->invalidate();
        }
        emit positionChanged(m_position);
    }
}
//设置数据索引。
bool WRDirMapDataAngleLineElement::position(double value)
{
	if (value != m_position)
	{
		m_position = value;
		WRDirMapControl* chart = (WRDirMapControl*)owner();
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
WRDirMapGaugeElement::Type WRDirMapDataPointLineElement::type() const
{
	return DataPointLine;
}
//更新元素的布局。
void WRDirMapDataPointLineElement::arrange(void)
{
	WRDirMapControl* chart = (WRDirMapControl*)owner();
	WRDirMapDataViewElement* dataView = chart->dataView();
	if (!dataView->size().empty() && m_position >= chart->showDataPointBegin() && m_position <= chart->showDataPointEnd())
	{
		int x = chart->getDataPointPos(dataView->width(), m_position);
		this->doLayout(WRRect(dataView->left() + x - 2, dataView->top(), 5, dataView->height()));
		return;
	}
	this->doLayout(WRRect());
}

//键盘按下处理，如果需要重绘，则返回True。
bool WRDirMapDataPointLineElement::onKeyDown(const QKeyEvent& e)
{
	if (moveable() && ((e.modifiers() & Qt::ControlModifier) == Qt::ControlModifier))
	{
		int position = m_position;
		if (e.key() == Qt::Key_Left)
		{
			WRDirMapControl* chart = (WRDirMapControl*)owner();
			if (position > chart->showDataPointBegin())
			{
				WRDirMapDataViewElement* dataView = chart->dataView();
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
			WRDirMapControl* chart = (WRDirMapControl*)owner();
			if (position < chart->showDataPointEnd())
			{
				WRDirMapDataViewElement* dataView = chart->dataView();
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
bool WRDirMapDataPointLineElement::onKeyUp(const QKeyEvent&)
{
	return false;
}

//鼠标按下处理，如果需要重绘，则返回True。
bool WRDirMapDataPointLineElement::onMouseDown(const QMouseEvent& e)
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
bool WRDirMapDataPointLineElement::onMouseUp(const QMouseEvent& e)
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
bool WRDirMapDataPointLineElement::onMouseMove(const QMouseEvent& e)
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
			WRDirMapControl* chart = (WRDirMapControl*)owner();
			WRDirMapDataViewElement* dataView = chart->dataView();
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
bool WRDirMapDataPointLineElement::onMouseLeave(void)
{
    if (!mouseCaptured() && mouseCursor())
    {
        QApplication::restoreOverrideCursor();
        mouseCursor(false);
    }
    return false;
}

//执行绘制处理。
void WRDirMapDataPointLineElement::onPaint(QPainter& painter)
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
void WRDirMapDataPointLineElement::onPaintMouseFeedback(QPainter&)
{
	//add code here
}

//设置数据索引。
void WRDirMapDataPointLineElement::setPosition(int value)
{
    if (value != m_position)
    {
        m_position = value;
        WRDirMapControl* chart = (WRDirMapControl*)owner();
        if (chart && chart->effect())
        {
            arrange();
            chart->invalidate();
        }
        emit positionChanged(m_position);
    }
}
//设置数据索引。
bool WRDirMapDataPointLineElement::position(int value)
{
	if (value != m_position)
	{
		m_position = value;		
		WRDirMapControl* chart = (WRDirMapControl*)owner();
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

