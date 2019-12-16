#include <WRCharting/WRDirMapDataPalette.h>

//初始化颜色表。
void WRDirMapDataPalette::initialize(void)
{
    int index1 = 0;
    for(int c = 0; c < m_size; ++c)
    {
        int index2 = (int)(c * 255 / (m_size - 1.0));
        WRColor* color2 = &m_list[c];
        int r2 = color2->red();
        int g2 = color2->green();
        int b2 = color2->blue();
        m_table[index2] = qRgb(r2, g2, b2);
        int span = index2 - index1;
        if (span > 1)
        {
            WRColor* color1 = color2 - 1;
            for(int m = 1; m < span; ++m)
            {
                int r1 = color1->red();
                int g1 = color1->green();
                int b1 = color1->blue();
                m_table[index1 + m] = qRgb(
                            (char)(r1 + m * (r2 - r1) / (double)span + 0.5),
                            (char)(g1 + m * (g2- g1) / (double)span + 0.5),
                            (char)(b1+ m * (b2 - b1) / (double)span + 0.5));
            }
        }
        index1 = index2;
    }
}
//清理当前对象所占用的相关资源。
WRDirMapDataPalette::~WRDirMapDataPalette()
{
	delete[] m_list;
}
//获取默认颜色。
WRDirMapDataPalette* WRDirMapDataPalette::defaultPalette(void)
{
	static WRDirMapDataPalette value;
	return &value;
}
