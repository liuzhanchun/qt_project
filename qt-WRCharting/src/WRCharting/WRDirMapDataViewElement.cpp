#include <WRCharting/WRDirMapDataViewElement.h>
#include <WRCharting/WRDirMapControl.h>

//初始化向频图对象。
WRDirMapDataViewElement::WRDirMapDataViewElement(void)
{
    m_bitmap = 0;
	m_palette = WRDirMapDataPalette::defaultPalette();
	m_palette->addRef();

	m_showBuffer = 0;
	m_showIndex = 0;
}

//清理当前对象所占用的相关资源。
WRDirMapDataViewElement::~WRDirMapDataViewElement(void)
{
	if (m_showIndex)
	{
		delete[] m_showIndex;
	}
	if (m_showBuffer)
	{
		delete[] m_showBuffer;
	}
    if (m_bitmap)
    {
        delete m_bitmap;
    }
	m_palette->release();
}

//设置数据调色板。
void WRDirMapDataViewElement::setDataPalette(WRDirMapDataPalette* value)
{
    if (value == 0)
    {
        value = WRDirMapDataPalette::defaultPalette();
    }
    if (m_palette != value)
    {
        bool changed = m_palette->count() != value->count();
        if (!changed)
        {
            for(int i = 0; i < value->count(); ++i)
            {
                if (value->color(i) != m_palette->color(i))
                {
                    changed = true;
                    break;
                }
            }
        }
        if (changed)
        {
            m_palette->release();
            m_palette = value;
            m_palette->addRef();
            if (m_bitmap)
            {
                delete m_bitmap;
                m_bitmap = 0;
            }
            invalidate();
            doUpdate();
            emit dataPaletteChanged(m_palette);
        }
    }
}

//设置数据调色板。
bool WRDirMapDataViewElement::dataPalette(WRDirMapDataPalette* value)
{
	if (value == 0)
	{
		value = WRDirMapDataPalette::defaultPalette();
	}
	if (m_palette != value)
	{
		bool changed = m_palette->count() != value->count();
		if (!changed)
		{
			for(int i = 0; i < value->count(); ++i)
			{
				if (value->color(i) != m_palette->color(i))
				{
					changed = true;
					break;
				}
			}
		}
		if (changed)
		{
			m_palette->release();
			m_palette = value;
			m_palette->addRef();
            if (m_bitmap)
			{
                delete m_bitmap;
                m_bitmap = 0;
			}
			invalidate();
			doUpdate();
            emit dataPaletteChanged(m_palette);
			return true;
		}
	}
	return false;
}
//设置数据调色板。
bool WRDirMapDataViewElement::dataPalette(const WRColor* list, int size)
{
	bool changed = m_palette->count() != size;
	if (!changed)
	{
		for(int i = 0; i < size; ++i)
		{
			if (list[i] != m_palette->color(i))
			{
				changed = true;
				break;
			}
		}
	}
	if (changed)
	{
		m_palette->release();
		m_palette = new WRDirMapDataPalette(list, size);
        if (m_bitmap)
		{
            delete m_bitmap;
            m_bitmap = 0;
		}
		invalidate();
		doUpdate();
        emit dataPaletteChanged(m_palette);
		return true;
	}
	return false;
}

//当显示数据范围改变后调用此方法 。
void WRDirMapDataViewElement::onShowDataRangeChanged(void)
{
	invalidate();
}
//当显示数据点范围改变后调用此方法。
void WRDirMapDataViewElement::onShowDataPointRangeChanged(void)
{
    if (m_showIndex)
    {
        delete[] m_showIndex;
        m_showIndex = 0;
    }
}
//当显示数据角度范围改变后调用此方法。
void WRDirMapDataViewElement::onShowDataAngleRangeChanged(void)
{
	//add code here
}

//当大小改变后调用此方法。
void WRDirMapDataViewElement::onSizeChanged(void)
{
	if (m_showBuffer)
	{
		delete[] m_showBuffer;
		m_showBuffer = 0;
	}
    if (m_bitmap)
    {
        delete m_bitmap;
        m_bitmap = 0;
    }
}
//当宽度改变后调用此方法。
void WRDirMapDataViewElement::onWidthChanged(void)
{
    if (m_showIndex)
    {
        delete[] m_showIndex;
        m_showIndex = 0;
    }
}
//当高度改变后调用此方法。
void WRDirMapDataViewElement::onHeightChanged(void)
{
	//add code here
}

//执行缩放处理。
bool WRDirMapDataViewElement::doZoom(const WRPoint& begPos, const WRPoint& endPos)
{
    WRDirMapControl* chart = (WRDirMapControl*)owner();
    WRChartSampleRange showPointRange(chart->showDataPointRange());
    WRChartDValueRange showAngleRange(chart->showDataAngleRange());
    if (hScalable())
    {
        chart->doMouseZoomH(showPointRange, begPos.x() - left(), endPos.x() - left(), width());
    }
    if (vScalable())
    {
        chart->doMouseZoomV(showAngleRange, begPos.y() - top(), endPos.y() - top(), height());
    }
    return chart->changeShowDataRange(WRDirMapDataRange(showPointRange, showAngleRange));
}
//执行移动处理。
bool WRDirMapDataViewElement::doMove(const WRPoint& begPos, const WRPoint& endPos)
{
    WRDirMapControl* chart = (WRDirMapControl*)owner();
    WRChartSampleRange showPointRange(chart->showDataPointRange());
    WRChartDValueRange showAngleRange(chart->showDataAngleRange());
    chart->doMouseMoveH(showPointRange, begPos.x(), endPos.x(), width());
    chart->doMouseMoveV(showAngleRange, begPos.y(), endPos.y(), height());
    return chart->changeShowDataRange(WRDirMapDataRange(showPointRange, showAngleRange));
}

//鼠标滚动处理。
bool WRDirMapDataViewElement::onMouseWheel(const QWheelEvent& e)
{
    WRDirMapControl* chart = (WRDirMapControl*)owner();
    WRChartSampleRange showPointRange(chart->showDataPointRange());
    WRChartDValueRange showAngleRange(chart->showDataAngleRange());
    if (hScalable())
    {
        chart->doMouseWheelH(showPointRange, e.x() - left(), e.delta(), width());
    }
    if (vScalable())
    {
        chart->doMouseWheelV(showAngleRange, e.y() - top(), e.delta(), height());
    }
    return chart->changeShowDataRange(WRDirMapDataRange(showPointRange, showAngleRange));
}

//初始化数据点索引。
void WRDirMapDataViewElement::initIndex(void)
{
    if (!m_showIndex)
    {
        WRDirMapControl* chart = (WRDirMapControl*)owner();
        int showCountP = chart->showDataPointCount();
        if (showCountP > width())
        {
            m_showIndex = new int[width()];
            for (int x = 0, w = width() - 1; x < w; ++x)
            {
                int i1 = (int)(x * (showCountP- 1LL) / (width() - 1.0) + 0.5);
                int x1 = (int)(i1 * (width()- 1LL) / (showCountP - 1.0) + 0.5);
                if (x1 > x)
                {
                    for (int i = i1 - 1; i >= 0; --i)
                    {
                        x1 = (int)(i * (width()- 1LL) / (showCountP - 1.0) + 0.5);
                        if (x1 == x)
                        {
                            m_showIndex[x] = i + 1;
                            break;
                        }
                    }
                }
                else
                {
                    int i2 = (int)((x + 1) * (showCountP- 1LL) / (width() - 1.0) + 0.5);
                    int x2 = (int)(i2 * (width()- 1LL) / (showCountP - 1.0) + 0.5);
                    if (x2 == x)
                    {
                        for (int i = i2 + 1; i < showCountP; ++i)
                        {
                            x2 = (int)(i * (width()- 1LL) / (showCountP - 1.0) + 0.5);
                            if (x2 > x)
                            {
                                m_showIndex[x] = i;
                                break;
                            }
                        }
                    }
                    else
                    {
                        for (int i = i2 - 1; i >= 0; --i)
                        {
                            x2 = (int)(i * (width()- 1LL) / (showCountP - 1.0) + 0.5);
                            if (x2 == x)
                            {
                                m_showIndex[x] = i + 1;
                                break;
                            }
                        }
                    }
                }
            }
            m_showIndex[width() - 1] = showCountP;
        }
        else
        {
            m_showIndex = new int[showCountP];
            for (int i = 1; i < showCountP; ++i)
            {
                m_showIndex[i] = (int)(i * (width()- 1LL) / (showCountP - 1.0) + 0.5);
            }
            m_showIndex[0] = 0;
            m_showIndex[showCountP - 1] = width() - 1;
        }
    }
}
//填充位图。
void WRDirMapDataViewElement::fillBitmap(void)
{
    initIndex();

    int w = getBitmapWidth(width());
    unsigned char* bits = m_bitmap->bits();
    WRDirMapControl* chart = (WRDirMapControl*)owner();
    //如果数据源不存在，则用最小值填充图形并返回。
	WRDirMapDataSource* dataSource = chart->m_currSource;
    if (!dataSource)
    {
        memset(bits, 0, w * height());
        return;
    }
    //执行相应的填充处理
    if (width() > chart->showDataPointCount())//宽度大于点数
    {
		dataSource->retrieve(m_showBuffer, (WRDirMapDataSource::ProcMethod)(chart->dataProcMethod()), chart->showDataPointRange(), chart->showDataAngleRange(), height());
        if (chart->showDataPointCount() > 1)
        {
            //执行横向插值处理
            double* pDat = m_showBuffer;
            for (int y = 0; y < height(); ++y)
            {
                int x1 = 0;
                unsigned char* pImg1 = bits + y * w;
                *pImg1 = chart->getShowValue(*pDat);
                ++pDat;

                int x2, xSpan;
                unsigned char* pImg2;
                for (int p = 1; p < chart->showDataPointCount(); ++p, ++pDat)
                {
                    x2 = m_showIndex[p];
                    xSpan = x2 - x1;
                    pImg2 = pImg1 + xSpan;

                    *pImg2 = chart->getShowValue(*pDat);

                    for (int x = 1; x < xSpan; ++x)
                    {
                        pImg1[x] = (unsigned char)(*pImg1 + x * (*pImg2 - *pImg1) / (double)xSpan + 0.5);
                    }

                    x1 = x2;
                    pImg1 = pImg2;
                }
            }
        }
        else
        {
            double* pDat = m_showBuffer;
            unsigned char* pImg = bits;
            for (int y = 0; y < height(); ++y, ++pDat)
            {
                *pImg = chart->getShowValue(*pDat);
                for (int x = 1; x < width(); ++x)
                {
                    pImg[x] = *pImg;
                }
                pImg += w;
            }
        }
    }
    else
    {
		dataSource->retrieve(m_showBuffer, (WRDirMapDataSource::ProcMethod)(chart->dataProcMethod()), chart->showDataPointRange(), chart->showDataAngleRange(), m_showIndex, width(), height());
        //直接进行数据复制
        double* pDat = m_showBuffer;
        unsigned char* pImg = bits;
        for (int y = 0; y < height(); ++y)
        {
            for (int x = 0; x < width(); ++x, ++pDat)
            {
                pImg[x] = chart->getShowValue(*pDat);
            }
            pImg += w;
		}
    }
 }

//执行绘制处理。
void WRDirMapDataViewElement::onPaint(QPainter& painter)
{
    if (!m_bitmap)
    {
        m_bitmap = new QImage(width(), height(), QImage::Format_Indexed8);
        m_bitmap->setColorCount(256);
        for(int i = 0; i < 256; ++i)
        {
            m_bitmap->setColor(i, m_palette->m_table[i]);
        }
        invalidate();
    }
	//在缓存新建或者无效的情况下执行绘制处理
	if (invalid())
	{
		//初始化数据缓存
		if (!m_showBuffer)
		{
			m_showBuffer = new double[width() * height()];
		}
		//填充显示图形
		fillBitmap();
        invalid(false);
    }
    painter.drawImage(rect(), *m_bitmap);
}
