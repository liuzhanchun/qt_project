#include "DirMapWindow.h"
#include "ui_DirMapWindow.h"
#include "SpecParams.h"
#include <qstring.h>
#ifndef QStringLiteral
// no lambdas, not GCC, or GCC in C++98 mode with 4-byte wchar_t
// fallback, return a temporary QString
// source code is assumed to be encoded in UTF-8

# define QStringLiteral(str) QString::fromUtf8("" str "", sizeof(str) - 1)
#endif

//表示向频图线程。
class DirMapThread : public QThread
{
private:
    QFile m_file;
    bool m_status;
    WRDirMapControl* m_chart;
    SpecParams m_params;

public:
    //
    DirMapThread(WRDirMapControl* chart, QString fileName)
        : m_file(fileName), m_status(false)
     {
        m_chart = chart;
        m_chart->addRef();
        if (m_file.open(QIODevice::ReadOnly))
        {
            char buf[64];
            if (m_file.read(buf,64) == 64 && m_params.initilize(buf))
            {
                WRDirMapInitParams<unsigned char, float> initArgs(m_params.minValue,
                                                         m_params.maxValue,
                                                         m_params.offValue,
                                                         1.0,
                                                         0,
                                                         360,
                                                         m_params.dataSize, m_params.isClosed, m_params.freqBegin,
                                                         m_params.freqEnd, 100, 1000);
                m_chart->initialize(initArgs);
                m_status = true;
                start();
            }
        }
     }
    //
    ~DirMapThread()
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
        int length = m_params.dataSize + 8;
        char* buf = new char[length];
        float* dir = new float[m_params.dataSize];
        while (m_status) {
           if (m_file.read(buf, length) != length)
           {
               m_file.seek(64);
               continue;
           }
           for(int i=0; i < m_params.dataSize; ++i)
           {
               dir[i] = (float)(((unsigned short)(i * 10 % 3600)) / 10.0);
               dir[i] += (float)((qrand() % 1000) / 1000.0);
           }
           m_chart->writeData(buf + 8, dir, 1);
           QThread::msleep(20);
        }
        delete[] buf;
        delete[] dir;
    }
};

DirMapWindow::DirMapWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirMapWindow)
{
    ui->setupUi(this);
    chart = new WRDirMapControl();
    thread = new DirMapThread(chart, QStringLiteral("D:\\1400110781.80000000_100000000.spec"));
    //thread = new DirMapThread(chart, QStringLiteral("D:\\1359180937.30000000_3610000000.spec"));
    chart->attach(this);
    WRDirMapDataPointLineElement* vLine = chart->addDataPointLine(10);
    vLine->color(QColor(Qt::red));
    WRDirMapDataAngleLineElement* hLine = chart->addDataAngleLine(100);
    hLine->color(QColor(Qt::red));
    chart->dataView()->mouseDragMode(WRDirMapDataViewElement::MouseDragZoom);
//    chart->vAxis()->dockLeft(false);
//    chart->hAxis()->dockBottom(false);
}

DirMapWindow::~DirMapWindow()
{
    if (thread)
    {
        delete thread;
        thread = 0;
    }
    chart->release();
    delete ui;
}
