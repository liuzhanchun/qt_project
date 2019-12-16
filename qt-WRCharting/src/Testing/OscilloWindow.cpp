#include "OscilloWindow.h"
#include "ui_OscilloWindow.h"

#include <qstring.h>
#ifndef QStringLiteral
// no lambdas, not GCC, or GCC in C++98 mode with 4-byte wchar_t
// fallback, return a temporary QString
// source code is assumed to be encoded in UTF-8

# define QStringLiteral(str) QString::fromUtf8("" str "", sizeof(str) - 1)
#endif

//表示波形图线程。
class OscilloThread : public QThread
{
private:
    QFile m_file;
    bool m_status;
    WROscilloControl* m_chart;

public:
    //
    OscilloThread(WROscilloControl* chart)
        : m_file(QStringLiteral(":/WRCharting-Testing/wave.dat")), m_status(false)
     {
        m_chart = chart;
        m_chart->addRef();

        WROscilloInitParams<short> initArgs(-32767, 32767, 8000, 8000, 32000);
        m_chart->initialize(initArgs);
        m_status = true;
        start();
     }
    //
    ~OscilloThread()
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
        int length = 2000;
        char* buffer = new char[length];
        while (m_status) {
           if (m_file.read(buffer, length) != length)
           {
               m_file.seek(0);
               continue;
           }
           m_chart->writeData(buffer, length / 2, ticks);
           ticks += 10000 * length / 2;
           QThread::msleep(200);
        }
        delete[] buffer;

        m_file.close();
    }
};

OscilloWindow::OscilloWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OscilloWindow)
{
    ui->setupUi(this);
    chart = new WROscilloControl();
    thread = new OscilloThread(chart);
    chart->attach(this);
    WROscilloDataPointLineElement* vLine = chart->addDataPointLine(10);
    vLine->color(QColor(Qt::red));
    WROscilloDataValueLineElement* hLine = chart->addDataValueLine(100);
    hLine->color(QColor(Qt::red));
    chart->dataView()->mouseDragMode(WROscilloDataViewElement::MouseDragZoom);
    chart->dataView()->gridVisible(true);
    chart->vAxis()->dockLeft(false);
    chart->hAxis()->dockBottom(true);
}

OscilloWindow::~OscilloWindow()
{
    if (thread)
    {
        delete thread;
        thread = 0;
    }
    chart->release();
    delete ui;
}
