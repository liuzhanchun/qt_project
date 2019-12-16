#include <WRCharting/WRWaterfallDataViewElement.h>
#include <WRCharting/WRWaterfallControl.h>

//初始化瀑布图对象。
WRWaterfallDataViewElement::WRWaterfallDataViewElement(void)
{
    m_bitmap = 0;
	m_palette = WRWaterfallDataPalette::defaultPalette();
	m_palette->addRef();

	m_showBuffer = 0;
	m_showIndexP = 0;
	m_showIndexF = 0;
}

//清理当前对象所占用的相关资源。
WRWaterfallDataViewElement::~WRWaterfallDataViewElement(void)
{
	if (m_showIndexP)
	{
		delete[] m_showIndexP;
	}
	if (m_showIndexF)
	{
		delete[] m_showIndexF;
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
void WRWaterfallDataViewElement::setDataPalette(WRWaterfallDataPalette* value)
{
    if (value == 0)
    {
        value = WRWaterfallDataPalette::defaultPalette();
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
bool WRWaterfallDataViewElement::dataPalette(WRWaterfallDataPalette* value)
{
	if (value == 0)
	{
		value = WRWaterfallDataPalette::defaultPalette();
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
bool WRWaterfallDataViewElement::dataPalette(const WRColor* list, int size)
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
		m_palette = new WRWaterfallDataPalette(list, size);
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

//当是否纵向改变后调用此方法。
void WRWaterfallDataViewElement::onVerticalChanged(void)
{
    if (m_showIndexF)
    {
        delete[] m_showIndexF;
        m_showIndexF = 0;
    }
    if (m_showIndexP)
    {
        delete[] m_showIndexP;
        m_showIndexP = 0;
    }
}
//当显示数据范围改变后调用此方法 。
void WRWaterfallDataViewElement::onShowDataRangeChanged(void)
{
	invalidate();
}
//当显示数据点范围改变后调用此方法。
void WRWaterfallDataViewElement::onShowDataPointRangeChanged(void)
{
    if (m_showIndexP)
    {
        delete[] m_showIndexP;
        m_showIndexP = 0;
    }
}
//当显示数据帧范围改变后调用此方法。
void WRWaterfallDataViewElement::onShowDataFrameRangeChanged(void)
{
    if (m_showIndexF)
    {
        delete[] m_showIndexF;
        m_showIndexF = 0;
    }
}

//当大小改变后调用此方法。
void WRWaterfallDataViewElement::onSizeChanged(void)
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
void WRWaterfallDataViewElement::onWidthChanged(void)
{
    WRWaterfallControl* chart = (WRWaterfallControl*)owner();
    if (chart->vertical())
    {
        if (m_showIndexP)
        {
            delete[] m_showIndexP;
            m_showIndexP = 0;
        }
    }
    else
    {
        if (m_showIndexF)
        {
            delete[] m_showIndexF;
            m_showIndexF = 0;
        }
    }
}
//当高度改变后调用此方法。
void WRWaterfallDataViewElement::onHeightChanged(void)
{
    WRWaterfallControl* chart = (WRWaterfallControl*)owner();
    if (chart->vertical())
    {
        if (m_showIndexF)
        {
            delete[] m_showIndexF;
            m_showIndexF = 0;
        }
    }
    else
    {
        if (m_showIndexP)
        {
            delete[] m_showIndexP;
            m_showIndexP = 0;
        }
    }
}

//执行缩放处理。
bool WRWaterfallDataViewElement::doZoom(const WRPoint& begPos, const WRPoint& endPos)
{
    WRWaterfallControl* chart = (WRWaterfallControl*)owner();
    WRChartSampleRange showPointRange(chart->showDataPointRange());
    WRChartSampleRange showFrameRange(chart->showDataFrameRange());
    if (chart->vertical())
    {
        if (hScalable())
        {
            chart->doVMouseZoomH(showPointRange, begPos.x() - left(), endPos.x() - left(), width());
        }
        if (vScalable())
        {
            chart->doVMouseZoomV(showFrameRange, begPos.y() - top(), endPos.y() - top(), height());
        }
    }
    else
    {
        if (hScalable())
        {
            chart->doHMouseZoomH(showFrameRange, begPos.x() - left(), endPos.x() - left(), width());
        }
        if (vScalable())
        {
            chart->doHMouseZoomV(showPointRange, begPos.y() - top(), endPos.y() - top(), height());
        }
    }
    return chart->changeShowDataRange(WRWaterfallDataRange(showPointRange, showFrameRange));
}
//执行移动处理。
bool WRWaterfallDataViewElement::doMove(const WRPoint& begPos, const WRPoint& endPos)
{
    WRWaterfallControl* chart = (WRWaterfallControl*)owner();
    WRChartSampleRange showPointRange(chart->showDataPointRange());
    WRChartSampleRange showFrameRange(chart->showDataFrameRange());
    if (chart->vertical())
    {
        chart->doVMouseMoveH(showPointRange, begPos.x(), endPos.x(), width());
        chart->doVMouseMoveV(showFrameRange, begPos.y(), endPos.y(), height());
    }
    else
    {
        chart->doHMouseMoveH(showFrameRange, begPos.x(), endPos.x(), width());
        chart->doHMouseMoveV(showPointRange, begPos.y(), endPos.y(), height());
    }
    return chart->changeShowDataRange(WRWaterfallDataRange(showPointRange, showFrameRange));
}

//鼠标滚动处理。
bool WRWaterfallDataViewElement::onMouseWheel(const QWheelEvent& e)
{
    WRWaterfallControl* chart = (WRWaterfallControl*)owner();
    WRChartSampleRange showPointRange(chart->showDataPointRange());
    WRChartSampleRange showFrameRange(chart->showDataFrameRange());
    if (chart->vertical())
    {
        if (hScalable())
        {
            chart->doVMouseWheelH(showPointRange, e.x() - left(), e.delta(), width());
        }
        if (vScalable())
        {
            chart->doVMouseWheelV(showFrameRange, e.y() - top(), e.delta(), height());
        }
    }
    else
    {
        if (hScalable())
        {
            chart->doHMouseWheelH(showFrameRange, e.x() - left(), e.delta(), width());
        }
        if (vScalable())
        {
            chart->doHMouseWheelV(showPointRange, e.y() - top(), e.delta(), height());
        }
    }
    return chart->changeShowDataRange(WRWaterfallDataRange(showPointRange, showFrameRange));
}

//初始化横向数据点索引。
void WRWaterfallDataViewElement::initHIndexP(void)
{
    if (!m_showIndexP)
    {
        WRWaterfallControl* chart = (WRWaterfallControl*)owner();
        int showCountP = chart->showDataPointCount();
        if (showCountP > height())
        {
            m_showIndexP = new int[height()];
            for (int y = 0, h = height() - 1; y < h; ++y)
            {
                int i1 = (int)(y * (showCountP - 1LL) / (height() - 1.0) + 0.5);
                int y1 = (int)(i1 * (height() - 1LL) / (showCountP - 1.0) + 0.5);
                if (y1 > y)
                {
                    for (int i = i1 - 1; i >= 0; --i)
                    {
                        y1 = (int)(i * (height() - 1LL) / (showCountP - 1.0) + 0.5);
                        if (y1 == y)
                        {
                            m_showIndexP[y] = i + 1;
                            break;
                        }
                    }
                }
                else
                {
                    int i2 = (int)((y + 1) * (showCountP - 1LL) / (height() - 1.0) + 0.5);
                    int y2 = (int)(i2 * (height() - 1LL) / (showCountP - 1.0) + 0.5);
                    if (y2 == y)
                    {
                        for (int i = i2 + 1; i < showCountP; ++i)
                        {
                            y2 = (int)(i * (height() - 1LL) / (showCountP - 1.0) + 0.5);
                            if (y2 > y)
                            {
                                m_showIndexP[y] = i;
                                break;
                            }
                        }
                    }
                    else
                    {
                        for (int i = i2 - 1; i >= 0; --i)
                        {
                            y2 = (int)(i * (height() - 1LL) / (showCountP - 1.0) + 0.5);
                            if (y2 == y)
                            {
                                m_showIndexP[y] = i + 1;
                                break;
                            }
                        }
                    }
                }
            }
            m_showIndexP[height() - 1] = showCountP;
        }
        else
        {
            m_showIndexP = new int[showCountP];
            for (int i = 1; i < showCountP; ++i)
            {
                m_showIndexP[i] = (int)(i * (height() - 1LL) / (showCountP - 1.0) + 0.5);
            }
            m_showIndexP[0] = 0;
            m_showIndexP[showCountP - 1] = height() - 1;
        }
    }
}
//初始化横向向数据帧索引。
void WRWaterfallDataViewElement::initHIndexF(void)
{
    if (!m_showIndexF)
    {
        WRWaterfallControl* chart = (WRWaterfallControl*)owner();
        int showCountF = chart->showDataFrameCount();
        if (showCountF > width())
        {
            m_showIndexF = new int[width()];
            for (int x = 0, w = width() - 1; x < w; ++x)
            {
                int i1 = (int)(x * (showCountF - 1LL) / (width() - 1.0) + 0.5);
                int x1 = (int)(i1 * (width() - 1LL) / (showCountF - 1.0) + 0.5);
                if (x1 > x)
                {
                    for (int i = i1 - 1; i >= 0; --i)
                    {
                        x1 = (int)(i * (width() - 1LL) / (showCountF - 1.0) + 0.5);
                        if (x1 == x)
                        {
                            m_showIndexF[x] = i + 1;
                            break;
                        }
                    }
                }
                else
                {
                    int i2 = (int)((x + 1) * (showCountF - 1LL) / (width() - 1.0) + 0.5);
                    int x2 = (int)(i2 * (width() - 1LL) / (showCountF - 1.0) + 0.5);
                    if (x2 == x)
                    {
                        for (int i = i2 + 1; i < showCountF; ++i)
                        {
                            x2 = (int)(i * (width() - 1LL) / (showCountF - 1.0) + 0.5);
                            if (x2 > x)
                            {
                                m_showIndexF[x] = i;
                                break;
                            }
                        }
                    }
                    else
                    {
                        for (int i = i2 - 1; i >= 0; --i)
                        {
                            x2 = (int)(i * (width() - 1LL) / (showCountF - 1.0) + 0.5);
                            if (x2 == x)
                            {
                                m_showIndexF[x] = i + 1;
                                break;
                            }
                        }
                    }
                }
            }
            m_showIndexF[width() - 1] = showCountF;
        }
        else
        {
            m_showIndexF = new int[showCountF];
            for (int i = 1; i < showCountF; ++i)
            {
                m_showIndexF[i] = (int)(i * (width() - 1LL) / (showCountF - 1.0) + 0.5);
            }
            m_showIndexF[0] = 0;
            m_showIndexF[showCountF - 1] = (int)(width() - 1);
		}
    }
}
//填充横向位图。
void WRWaterfallDataViewElement::fillHBitmap(void)
{
    initHIndexF();
    initHIndexP();

    int w = getBitmapWidth(width());
    unsigned char* bits = m_bitmap->bits();
    WRWaterfallControl* chart = (WRWaterfallControl*)owner();
	//如果数据源不存在，则用最小值填充图形并返回。
	WRWaterfallDataSource* dataSource = chart->m_currSource;
    if (!dataSource)
    {
        memset(bits, 0, w * height());
        return;
    }
    //执行相应的填充处理
    if (height() > chart->showDataPointCount())//高度大于点数
    {
        if (width() > chart->showDataFrameCount()) //宽度大于帧数
        {
			dataSource->retrieve(m_showBuffer, chart->showDataPointBegin(), chart->showDataPointCount(), chart->showDataFrameBegin(), chart->showDataFrameCount());
            if (chart->showDataPointCount() < 2)
            {
                if (chart->showDataFrameCount() > 2)
                {
                    double* pDat = m_showBuffer;
                    for (int f = 0; f < chart->showDataFrameCount(); ++f, ++pDat)
                    {
                        bits[m_showIndexF[f]] = chart->getShowValue(*pDat);
                    }
                    //执行横向插值处理
                    for (int f = 1; f < chart->showDataFrameCount(); ++f)
                    {
                        int x1 = m_showIndexF[f - 1];
                        int x2 = m_showIndexF[f];
                        int xSpan = x2 - x1;
                        if (xSpan > 1)
                        {
                            unsigned char* pImg1 = bits + x1;
                            unsigned char* pImg2 = bits + x2;
                            for (int x = 1; x < xSpan; ++x)
                            {
                                pImg1[x] = (unsigned char)(*pImg1 + x * (*pImg2 - *pImg1) / (double)xSpan + 0.5);
                            }
                        }
                    }
                    //
                    unsigned char* pImg3 = bits + w;
                    for (int y = 1; y < height(); ++y)
                    {
                        memcpy(pImg3, bits, w);
                        pImg3 += w;
                    }
                }
                else
                {
                    unsigned char pVal = chart->getShowValue(*m_showBuffer);
                    memset(bits, pVal, w * height());
                }
            }
            else if (chart->showDataFrameCount() < 2)
            {
                if (chart->showDataPointCount() > 2)
                {
                    double* pDat = m_showBuffer;
                    int y1 = height() - 1;
                    unsigned char* pImg1 = bits + w * y1;
                    *pImg1 = chart->getShowValue(*pDat);
                    ++pDat;
                    int y2, ySpan;
                    unsigned char* pImg2;
                    for (int p = 1; p < chart->showDataPointCount(); ++p, ++pDat)
                    {
                        y2 = height() - 1 - m_showIndexP[p];
                        ySpan = y1 - y2;
                        pImg2 = pImg1 - ySpan * w;

                        *pImg2 = chart->getShowValue(*pDat);

                        for (int y = 1; y < ySpan; ++y)
                        {
                            pImg2[y * w] = (unsigned char)(*pImg2 + y * (*pImg1 - *pImg2) / (double)ySpan + 0.5);
                        }

                        y1 = y2;
                        pImg1 = pImg2;
                    }

                    unsigned char* pImg = bits;
                    for (int y = 0; y < height(); ++y)
                    {
                        memset(pImg, *pImg, w);
                        pImg += w;
                    }
                }
                else
                {
                    unsigned char pVal = chart->getShowValue(*m_showBuffer);
                    memset(bits, pVal, w * height());
                }
            }
            else
            {
                //执行纵向插值处理
                double* pDat = m_showBuffer;
                for (int f = 0; f < chart->showDataFrameCount(); ++f)
                {
                    int y1 = height() - 1;
                    unsigned char* pImg1 = bits + y1 * w + m_showIndexF[f];
                    *pImg1 = chart->getShowValue(*pDat);
                    ++pDat;

                    int y2, ySpan;
                    unsigned char* pImg2;
                    for (int p = 1; p < chart->showDataPointCount(); ++p, ++pDat)
                    {
                        y2 = height() - 1 - m_showIndexP[p];
                        ySpan = y1 - y2;
                        pImg2 = pImg1 - ySpan * w;

                        *pImg2 = chart->getShowValue(*pDat);

                        for (int y = 1; y < ySpan; ++y)
                        {
                            pImg2[y * w] = (unsigned char)(*pImg2 + y * (*pImg1 - *pImg2) / (double)ySpan + 0.5);
                        }

                        y1 = y2;
                        pImg1 = pImg2;
                    }
                }
                //执行横向插值处理
                for (int f = 1; f < chart->showDataFrameCount(); ++f)
                {
                    int x1 = m_showIndexF[f - 1];
                    int x2 = m_showIndexF[f];
                    int xSpan = x2 - x1;
                    if (xSpan > 1)
                    {
                        unsigned char* pImg1 = bits + x1;
                        unsigned char* pImg2 = bits + x2;
                        for (int y = 0; y < height(); ++y)
                        {
                            for (int x = 1; x < xSpan; ++x)
                            {
                                pImg1[x] = (unsigned char)(*pImg1 + x * (*pImg2 - *pImg1) / (double)xSpan + 0.5);
                            }
                            pImg1 += w;
                            pImg2 += w;
                        }
                    }
                }
            }
        }
        else//宽度小于帧数
        {
			dataSource->retrieve(m_showBuffer, chart->showDataPointBegin(), chart->showDataPointCount(), chart->showDataFrameBegin(), m_showIndexF, width());
            if (chart->showDataPointCount() > 1)
            {
                //执行纵向插值处理
                double* pDat = m_showBuffer;
                for (int x = 0; x < width(); ++x)
                {
                    int y1 = height() - 1;
                    unsigned char* pImg1 = bits + w * y1 + x;
                    *pImg1 = chart->getShowValue(*pDat);
                    ++pDat;

                    int y2, ySpan;
                    unsigned char* pImg2;
                    for (int p = 1; p < chart->showDataPointCount(); ++p, ++pDat)
                    {
                        y2 = height() - 1 - m_showIndexP[p];
                        ySpan = y1 - y2;
                        pImg2 = pImg1 - ySpan * w;

                        *pImg2 = chart->getShowValue(*pDat);

                        for (int y = 1; y < ySpan; ++y)
                        {
                            pImg2[y * w] = (unsigned char)(*pImg2 + y * (*pImg1 - *pImg2) / (double)ySpan + 0.5);
                        }

                        y1 = y2;
                        pImg1 = pImg2;
                    }
                }
            }
            else
            {
                double* pDat = m_showBuffer;
                unsigned char* pImg = bits;
                for (int x = 0; x < width(); ++x, ++pDat)
                {
                    pImg[x] = chart->getShowValue(*pDat);
                }
                unsigned char* pImg2 = pImg + w;
                for (int y = 1; y < height(); ++y)
                {
                    memcpy(pImg2, pImg, w);
                    pImg2 += w;
                }
            }
        }
    }
    else
    {
        if (width() >chart->showDataFrameCount()) //宽度大于帧数
        {
			dataSource->retrieve(m_showBuffer, chart->showDataPointBegin(), m_showIndexP, height(), chart->showDataFrameBegin(), chart->showDataFrameCount());
            if (chart->showDataFrameCount() > 1)
            {
                //将数据复制到相应的位置
                double* pDat = m_showBuffer;
                for (int f = 0; f < chart->showDataFrameCount(); ++f)
                {
                    unsigned char* pImg = bits + m_showIndexF[f] + w * (height() - 1);
                    for (int y = height() - 1; y >= 0; --y, ++pDat)
                    {
                        *pImg = chart->getShowValue(*pDat);
                        pImg -= w;
                    }
                }
                //执行横向插值处理
                for (int f = 1; f < chart->showDataFrameCount(); ++f)
                {
                    int x1 = m_showIndexF[f - 1];
                    int x2 = m_showIndexF[f];
                    int xSpan = x2 - x1;
                    if (xSpan > 1)
                    {
                        unsigned char* pImg1 = bits + x1;
                        unsigned char* pImg2 = bits + x2;
                        for (int y = 0; y < height(); ++y)
                        {
                            for (int x = 1; x < xSpan; ++x)
                            {
                                pImg1[x] = (unsigned char)(*pImg1 + x * (*pImg2 - *pImg1) / (double)xSpan + 0.5);
                            }
                            pImg1 += w;
                            pImg2 += w;
                        }
                    }
                }
            }
            else
            {
                double* pDat = m_showBuffer;
                unsigned char* pImg = bits + w * (height() - 1);
                for (int y = height() - 1; y >= 0; --y, ++pDat)
                {
                    unsigned char pVal = chart->getShowValue(*pDat);
                    memset(pImg, pVal, w);
                    pImg -= w;
                }
            }
        }
        else
        {
			dataSource->retrieve(m_showBuffer, chart->showDataPointBegin(), m_showIndexP, height(), chart->showDataFrameBegin(), m_showIndexF, width());
            //直接进行数据复制
            double* pDat = m_showBuffer;
            unsigned char* pImg = bits;
            for (int x = 0; x < width(); ++x, ++pImg)
            {
                for (int y = height() - 1; y >= 0; --y, ++pDat)
                {
                    pImg[y * w] = chart->getShowValue(*pDat);
                }
            }
        }
    }
}

//初始化纵向数据点索引。
void WRWaterfallDataViewElement::initVIndexP(void)
{
    if (!m_showIndexP)
    {
        WRWaterfallControl* chart = (WRWaterfallControl*)owner();
        int showCountP = chart->showDataPointCount();
        if (showCountP > width())
        {
            m_showIndexP = new int[width()];
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
                            m_showIndexP[x] = i + 1;
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
                                m_showIndexP[x] = i;
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
                                m_showIndexP[x] = i + 1;
                                break;
                            }
                        }
                    }
                }
            }
            m_showIndexP[width() - 1] = showCountP;
        }
        else
        {
            m_showIndexP = new int[showCountP];
            for (int i = 1; i < showCountP; ++i)
            {
                m_showIndexP[i] = (int)(i * (width()- 1LL) / (showCountP - 1.0) + 0.5);
            }
            m_showIndexP[0] = 0;
            m_showIndexP[showCountP - 1] = width() - 1;
        }
    }
}
//初始化纵向数据帧索引。
void WRWaterfallDataViewElement::initVIndexF(void)
{
    if (!m_showIndexF)
    {
        WRWaterfallControl* chart = (WRWaterfallControl*)owner();
        int showCountF = chart->showDataFrameCount();
        if (showCountF > height())
        {
            m_showIndexF = new int[height()];
            for (int y = 0, h = height() - 1; y < h; ++y)
            {
                int i1 = (int)(y * (showCountF- 1LL) / (height() - 1.0) + 0.5);
                int y1 = (int)(i1 * (height()- 1LL) / (showCountF - 1.0) + 0.5);
                if (y1 > y)
                {
                    for (int i = i1 - 1; i >= 0; --i)
                    {
                        y1 = (int)(i * (height()- 1LL) / (showCountF - 1.0) + 0.5);
                        if (y1 == y)
                        {
                            m_showIndexF[y] = i + 1;
                            break;
                        }
                    }
                }
                else
                {
                    int i2 = (int)((y + 1) * (showCountF- 1LL) / (height() - 1.0) + 0.5);
                    int y2 = (int)(i2 * (height()- 1LL) / (showCountF - 1.0) + 0.5);
                    if (y2 == y)
                    {
                        for (int i = i2 + 1; i < showCountF; ++i)
                        {
                            y2 = (int)(i * (height()- 1LL) / (showCountF - 1.0) + 0.5);
                            if (y2 > y)
                            {
                                m_showIndexF[y] = i;
                                break;
                            }
                        }
                    }
                    else
                    {
                        for (int i = i2 - 1; i >= 0; --i)
                        {
                            y2 = (int)(i * (height()- 1LL) / (showCountF - 1.0) + 0.5);
                            if (y2 == y)
                            {
                                m_showIndexF[y] = i + 1;
                                break;
                            }
                        }
                    }
                }
            }
            m_showIndexF[height() - 1] = showCountF;
        }
        else
        {
            m_showIndexF = new int[showCountF];
            for (int i = 1; i < showCountF; ++i)
            {
                m_showIndexF[i] = (int)(i * (height()- 1LL) / (showCountF - 1.0) + 0.5);
            }
            m_showIndexF[0] = 0;
            m_showIndexF[showCountF - 1] = height() - 1;
        }
    }
}
//填充横向位图。
void WRWaterfallDataViewElement::fillVBitmap(void)
{
    initVIndexF();
    initVIndexP();

    int w = getBitmapWidth(width());
    unsigned char* bits = m_bitmap->bits();
    WRWaterfallControl* chart = (WRWaterfallControl*)owner();
    //如果数据源不存在，则用最小值填充图形并返回。
	WRWaterfallDataSource* dataSource = chart->m_currSource;
    if (!dataSource)
    {
        memset(bits, 0, w * height());
        return;
    }
    //执行相应的填充处理
    if (width() > chart->showDataPointCount())//宽度大于点数
    {
        if (height() > chart->showDataFrameCount()) //高度大于帧数
        {
			dataSource->retrieve(m_showBuffer, chart->showDataPointBegin(), chart->showDataPointCount(), chart->showDataFrameBegin(), chart->showDataFrameCount());
            if (chart->showDataPointCount() < 2)
            {
                if (chart->showDataFrameCount() > 1)
                {
                    //
                    double* pDat = m_showBuffer;
                    for (int f = 0; f < chart->showDataFrameCount(); ++f, ++pDat)
                    {
                        unsigned char* pImg1 = bits + m_showIndexF[f] * w;
                        *pImg1 = chart->getShowValue(*pDat);
                    }
                    //执行纵向插值处理
                    for (int f = 1; f < chart->showDataFrameCount(); ++f)
                    {
                        int y1 = m_showIndexF[f - 1];
                        int y2 = m_showIndexF[f];
                        int ySpan = y2 - y1;
                        if (ySpan > 1)
                        {
                            unsigned char* pImg1 = bits + y1 * w;
                            unsigned char* pImg2 = bits + y2 * w;
                            for (int y = 1; y < ySpan; ++y)
                            {
                                pImg1[y * w] = (unsigned char)(*pImg1 + y * (*pImg2 - *pImg1) / (double)ySpan + 0.5);
                            }
                        }
                    }
                    //
                    unsigned char* pImg = bits;
                    for (int y = 0; y < height(); ++y)
                    {
                        memset(pImg, *pImg, w);
                        pImg += w;
                    }
                }
                else
                {
                    unsigned char pVal = chart->getShowValue(*m_showBuffer);
                    memset(bits, pVal, w * height());
                }
            }
            else if (chart->showDataFrameCount() < 2)
            {
                if (chart->showDataPointCount() > 1)
                {
                    //
                    double* pDat = m_showBuffer;
                    int x1 = 0;
                    unsigned char* pImg1 = bits;
                    *pImg1 = chart->getShowValue(*pDat);
                    ++pDat;
                    int x2, xSpan;
                    unsigned char* pImg2;
                    for (int p = 1; p < chart->showDataPointCount(); ++p, ++pDat)
                    {
                        x2 = m_showIndexP[p];
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
                    //
                    pImg1 = bits;
                    pImg2 = bits + w;
                    for (int y = 1; y < height(); ++y)
                    {
                        memcpy(pImg2, pImg1, w);
                        pImg2 += w;
                    }
                }
                else
                {
                    unsigned char pVal = chart->getShowValue(*m_showBuffer);
                    memset(bits, pVal, w * height());
                }
            }
            else
            {
                //执行横向插值处理
                double* pDat = m_showBuffer;
                for (int f = 0; f < chart->showDataFrameCount(); ++f)
                {
                    int x1 = 0;
                    unsigned char* pImg1 = bits + m_showIndexF[f] * w;
                    *pImg1 = chart->getShowValue(*pDat);
                    ++pDat;

                    int x2, xSpan;
                    unsigned char* pImg2;
                    for (int p = 1; p < chart->showDataPointCount(); ++p, ++pDat)
                    {
                        x2 = m_showIndexP[p];
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
                //执行纵向插值处理
                for (int f = 1; f < chart->showDataFrameCount(); ++f)
                {
                    int y1 = m_showIndexF[f - 1];
                    int y2 = m_showIndexF[f];
                    int ySpan = y2 - y1;
                    if (ySpan > 1)
                    {
                        unsigned char* pImg1 = bits + y1 * w;
                        unsigned char* pImg2 = bits + y2 * w;
                        for (int x = 0; x < width(); ++x, ++pImg1, ++pImg2)
                        {
                            for (int y = 1; y < ySpan; ++y)
                            {
                                pImg1[y * w] = (unsigned char)(*pImg1 + y * (*pImg2 - *pImg1) / (double)ySpan + 0.5);
                            }
                        }
                    }
                }
            }
        }
        else//高度小于帧数
        {
			dataSource->retrieve(m_showBuffer, chart->showDataPointBegin(), chart->showDataPointCount(), chart->showDataFrameBegin(), m_showIndexF, height());
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
                        x2 = m_showIndexP[p];
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
    }
    else
    {
        if ((int)height() > chart->showDataFrameCount()) //高度大于帧数
        {
			dataSource->retrieve(m_showBuffer, chart->showDataPointBegin(), m_showIndexP, width(), chart->showDataFrameBegin(), chart->showDataFrameCount());
            if (chart->showDataFrameCount() > 1)
            {
                //将数据复制到相应的位置
                double* pDat = m_showBuffer;
                for (int f = 0; f < chart->showDataFrameCount(); ++f)
                {
                    unsigned char* pImg = bits + m_showIndexF[f] * w;
                    for (int x = 0; x < width(); ++x, ++pDat)
                    {
                        pImg[x] = chart->getShowValue(*pDat);
                    }
                }
                //执行纵向插值处理
                for (int f = 1; f < chart->showDataFrameCount(); ++f)
                {
                    int y1 = m_showIndexF[f - 1];
                    int y2 = m_showIndexF[f];
                    int ySpan = y2 - y1;
                    if (ySpan > 1)
                    {
                        unsigned char* pImg1 = bits + y1 * w;
                        unsigned char* pImg2 = bits + y2 * w;
                        for (int x = 0; x < width(); ++x, ++pImg1, ++pImg2)
                        {
                            for (int y = 1; y < ySpan; ++y)
                            {
                                pImg1[y * w] = (unsigned char)(*pImg1 + y * (*pImg2 - *pImg1) / (double)ySpan + 0.5);
                            }
                        }
                    }
                }
            }
            else
            {
                double* pDat = m_showBuffer;
                unsigned char* pImg = bits;
                for (int x = 0; x < width(); ++x, ++pDat)
                {
                    pImg[x] = chart->getShowValue(*pDat);
                }
                unsigned char* pImg2 = pImg + w;
                for (int y = 1; y < height(); ++y)
                {
                    memcpy(pImg2, pImg, w);
                    pImg2 += w;
                }
            }
        }
        else
        {
			dataSource->retrieve(m_showBuffer, chart->showDataPointBegin(), m_showIndexP, width(), chart->showDataFrameBegin(), m_showIndexF, height());
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
 }

//执行绘制处理。
void WRWaterfallDataViewElement::onPaint(QPainter& painter)
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
		//分情况填充显示图形
        WRWaterfallControl* chart = (WRWaterfallControl*)owner();
        if (chart->vertical())
        {
            fillVBitmap();
        }
        else
        {
            fillHBitmap();
        }

        invalid(false);
    }
    painter.drawImage(rect(), *m_bitmap);
}
