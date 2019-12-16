#include "VWaterfallWindow.h"
#include "ui_VWaterfallWindow.h"
#include "SpecParams.h"
#include <qstring.h>
#ifndef QStringLiteral
// no lambdas, not GCC, or GCC in C++98 mode with 4-byte wchar_t
// fallback, return a temporary QString
// source code is assumed to be encoded in UTF-8

# define QStringLiteral(str) QString::fromUtf8("" str "", sizeof(str) - 1)
#endif

//表示频谱图线程。
class VWaterfallThread : public QThread
{
private:
    QFile m_file;
    bool m_status;
    WRWaterfallControl* m_chart;
    SpecParams m_params;

public:
    //
    VWaterfallThread(WRWaterfallControl* chart)
        : m_file(QStringLiteral(":/WRCharting-Testing/spec.dat")), m_status(false)
     {
        m_chart = chart;
        m_chart->addRef();

        m_params.freqBegin = 30000000LL;
        m_params.freqEnd = 3610000000LL;
        m_params.dataSize = 143200;
        m_params.minValue = 36;
        m_params.maxValue = 226;
        m_params.offValue = -196;
        m_params.isClosed = false;

        WRWaterfallInitParams<unsigned char> initArgs(m_params.minValue,
                                                      m_params.maxValue,
                                                      m_params.offValue,
                                                      m_params.dataSize,
                                                      m_params.isClosed,
                                                      m_params.freqBegin,
                                                      m_params.freqEnd, 40, 100);
        m_chart->initialize(initArgs);

        m_status = true;
        start();
     }
    //
    ~VWaterfallThread()
    {
        if (m_status)
        {
            m_status = false;
            wait();
        }
        m_chart->release();
    }

protected:
    //执行线程处理。
    void run(void)
    {
        m_file.open(QIODevice::ReadOnly);

        long long ticks = 0;
        int length = m_params.dataSize;
        unsigned char* buf = new unsigned char[length];
        while (m_status) {
           if (m_file.read((char*)buf, length) != length)
           {
               m_file.seek(0);
               continue;
           }
           m_chart->writeData(buf, (long long*)buf, 1);

           QThread::msleep(40);
           ticks += 40 * 10000;
        }
        delete[] buf;

        m_file.close();
    }
};

VWaterfallWindow::VWaterfallWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VWaterfallWindow)
{
    ui->setupUi(this);
    chart = new WRWaterfallControl();
    thread = new VWaterfallThread(chart);
    chart->attach(this);
    WRWaterfallDataPointLineElement* vLine = chart->addDataPointLine(10);
    vLine->color(QColor(Qt::red));
    WRWaterfallDataFrameLineElement* hLine = chart->addDataFrameLine(10);
    hLine->color(QColor(Qt::red));
    chart->dataView()->mouseDragMode(WRWaterfallDataViewElement::MouseDragZoom);
//    chart->vAxis()->dockLeft(false);
//    chart->hAxis()->dockBottom(false);
}

VWaterfallWindow::~VWaterfallWindow()
{
    if (thread)
    {
        delete thread;
        thread = 0;
    }
    chart->release();
    delete ui;
}
