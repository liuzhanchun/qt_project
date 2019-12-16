#include "SpectroWindow.h"
#include "ui_SpectroWindow.h"
#include "SpecParams.h"
#include <qstring.h>
#ifndef QStringLiteral
// no lambdas, not GCC, or GCC in C++98 mode with 4-byte wchar_t
// fallback, return a temporary QString
// source code is assumed to be encoded in UTF-8

# define QStringLiteral(str) QString::fromUtf8("" str "", sizeof(str) - 1)
#endif

//表示频谱图线程。
class SpectroThread : public QThread
{
private:
    QFile m_file;
    bool m_status;
    WRSpectroControl* m_chart;
    SpecParams m_params;
    bool m_resetApex;

public:
    //
    SpectroThread(WRSpectroControl* chart)
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

        WRSpectroInitParams<unsigned char> initArgs(m_params.minValue,
                                                    m_params.maxValue,
                                                    m_params.offValue,
                                                    m_params.dataSize,
                                                    m_params.isClosed,
                                                    m_params.freqBegin,
                                                    m_params.freqEnd);

        m_chart->initialize(initArgs);

        m_status = true;
        start();

        m_resetApex = true;
     }
    //
    ~SpectroThread()
    {
        if (m_status)
        {
            m_status = false;
            wait();
        }
        m_chart->release();
    }

    void resetApex(void)
    {
        m_resetApex = true;
    }

protected:
    //执行线程处理。
    void run(void)
    {
        m_file.open(QIODevice::ReadOnly);

        int length = m_params.dataSize;
        unsigned char* buf = new unsigned char[length];
        unsigned char * apexBuffer = new unsigned char[length];
        int* markBuffer = new int[m_params.dataSize];
        for (int i = 0; i < m_params.dataSize; ++i)
        {
            markBuffer[i] = i;
        }
        while (m_status) {
           if (m_file.read((char*)buf, length) != length)
           {
               m_file.seek(0);
               continue;
           }
           bool apexChanged = false;
           if (m_resetApex)
           {
               for (int i = 0; i < length; ++i)
               {
                   apexBuffer[i] = buf[i];
               }
               m_resetApex = false;
               apexChanged = true;
           }
           else
           {
               for (int i = 8; i < length; ++i)
               {
                   if (buf[i] > apexBuffer[i])
                   {
                       apexBuffer[i] = buf[i];
                       apexChanged = true;
                   }
               }
           }
           m_chart->lock();
           {
               if (apexChanged)
               {
                   m_chart->alterData(0, apexBuffer);
               }
               m_chart->alterData(1, buf , markBuffer, m_params.dataSize);
           }
           m_chart->unlock();

           QThread::msleep(20);
        }
        delete[] buf;
        delete[] apexBuffer;
        delete[] markBuffer;

        m_file.close();
    }
};

SpectroWindow::SpectroWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpectroWindow)
{
    ui->setupUi(this);
    chart = new WRSpectroControl();
    chart->channel(0)->lineColor(WRColor(0xF5, 0xF5, 0xF5));
    chart->channel(1)->lineColor(QColor(Qt::green));
    chart->channel(1)->markColor(QColor(Qt::red));
    chart->channel(1)->dataZoomMethod(WRSpectroChannel::ShowDataRange);
    thread = new SpectroThread(chart);
    chart->attach(this);
    WRSpectroDataPointLineElement* vLine = chart->addDataPointLine(10);
    vLine->color(QColor(Qt::red));
    WRSpectroDataValueLineElement* hLine = chart->addDataValueLine(100);
    hLine->color(QColor(Qt::red));
    chart->dataView()->mouseDragMode(WRSpectroDataViewElement::MouseDragZoom);
//    chart->vAxis()->dockLeft(false);
//    chart->hAxis()->dockBottom(false);
}

SpectroWindow::~SpectroWindow()
{
    if (thread)
    {
        delete thread;
        thread = 0;
    }
    chart->release();
    delete ui;
}
