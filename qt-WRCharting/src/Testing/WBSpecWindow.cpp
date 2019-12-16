#include "WBSpecWindow.h"
#include "SpecParams.h"
#include <WRCharting/WRText.h>
#include <QThread>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <qstring.h>
#ifndef QStringLiteral
// no lambdas, not GCC, or GCC in C++98 mode with 4-byte wchar_t
// fallback, return a temporary QString
// source code is assumed to be encoded in UTF-8

# define QStringLiteral(str) QString::fromUtf8("" str "", sizeof(str) - 1)
#endif

//表示宽带频谱线程。
class WBSpecThread : public QThread
{
private:
    QFile m_file;
    bool m_status;
    WRSpectroControl* m_spectro;
    WRWaterfallControl* m_waterfall;
    SpecParams m_params;
    bool m_resetApex;

public:
    //
    WBSpecThread(WRSpectroControl* spectro, WRWaterfallControl* waterfall)
        : m_file(QStringLiteral(":/WRCharting-Testing/spec.dat")), m_status(false)
     {
        m_spectro = spectro;
        m_spectro->addRef();
        m_waterfall = waterfall;
        m_waterfall->addRef();

        m_params.freqBegin = 30000000LL;
        m_params.freqEnd = 3610000000LL;
        m_params.dataSize = 143200;
        m_params.minValue = 36;
        m_params.maxValue = 226;
        m_params.offValue = -196;
        m_params.isClosed = false;

        WRSpectroInitParams<unsigned char> spectroArgs(m_params.minValue,
                                                       m_params.maxValue,
                                                       m_params.offValue,
                                                       m_params.dataSize, m_params.isClosed,
                                                       m_params.freqBegin, m_params.freqEnd);
        WRWaterfallInitParams<unsigned char> waterfallArgs(m_params.minValue,
                                                           m_params.maxValue,
                                                           m_params.offValue,
                                                           m_params.dataSize, m_params.isClosed,
                                                           m_params.freqBegin, m_params.freqEnd, 40, 100);
        m_spectro->initialize(spectroArgs);
        m_waterfall->initialize(waterfallArgs);

        m_status = true;
        start();

        m_resetApex = true;
    }
    //
    ~WBSpecThread()
    {
        if (m_status)
        {
            m_status = false;
            wait();
        }
        m_spectro->release();
        m_waterfall->release();
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

        long long ticks = 0;
        int length = m_params.dataSize;
        unsigned char* buf = new unsigned char[length];
        unsigned char * apexBuffer = new unsigned char[length];
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
               for (int i = 0; i < length; ++i)
               {
                   if (buf[i] > apexBuffer[i])
                   {
                       apexBuffer[i] = buf[i];
                       apexChanged = true;
                   }
               }
           }
           m_spectro->lock();
           {
               if (apexChanged)
               {
                   m_spectro->alterData(0, apexBuffer);
               }
               m_spectro->alterData(1, buf);
           }
           m_spectro->unlock();
           m_waterfall->writeData(buf, &ticks, 1);

           QThread::msleep(40);
           ticks += 40 * 10000;
        }
        delete[] buf;
        delete[] apexBuffer;

        m_file.close();
    }
};


WBSpecWindow::WBSpecWindow(QWidget *parent) :
    QWidget(parent)
{
    m_splitter = new QSplitter(Qt::Vertical, this);
    m_waterfallWidget = new QWidget(m_splitter);
    m_spectroWidget = new QWidget(m_splitter);

    m_spectro = new WRSpectroControl();
    m_spectro->vAxis()->visible(false);
    m_spectro->dataView()->vScalable(false);
    m_spectro->dataView()->mouseDragMode(WRSpectroDataViewElement::MouseDragZoom);
    m_spectro->channel(0)->lineColor(WRColor(0xF5, 0xF5, 0xF5));
    m_spectro->channel(1)->lineColor(WRColor(173, 255, 48));
    m_spectro->channel(1)->markColor(QColor(Qt::red));
    m_spectro->channel(1)->dataZoomMethod(WRSpectroChannel::ShowDataRange);
    for(int i = 2; i < WRSPECTROCHANNELS; ++i)
    {
        m_spectro->channel(0)->visible(false);
    }
    m_spectro->attach(m_spectroWidget);

    m_spectroVLine = m_spectro->addDataPointLine(0);
    m_spectroVLine->color(WRColor(0xF5, 0xF5, 0xF5));

    m_waterfall = new WRWaterfallControl();
    m_waterfall->vAxis()->visible(false);
    m_waterfall->hAxis()->visible(false);
    m_waterfall->dataView()->vScalable(false);
    m_waterfall->dataView()->mouseDragMode(WRWaterfallDataViewElement::MouseDragZoom);
    m_waterfall->attach(m_waterfallWidget);

    m_waterfallVLine = m_waterfall->addDataPointLine(0);
    m_waterfallVLine->color(WRColor(0xF5, 0xF5, 0xF5));

    m_freqLabel = new QLabel(this);
    m_infoLabel = new QLabel(QStringLiteral("显示拖动信息"), this);

    m_showVAxisBox = new QCheckBox(QStringLiteral("显示纵坐标"), this);
    m_showVAxisBox->setChecked(false);
    QObject::connect(m_showVAxisBox, SIGNAL(stateChanged(int)), this, SLOT(onShowVAxisBoxStateChanged(int)));

    m_showApexBox = new QCheckBox(QStringLiteral("显示峰值曲线"), this);
    m_showVAxisBox->setChecked(true);
    QObject::connect(m_showApexBox, SIGNAL(stateChanged(int)), this, SLOT(onShowApexBoxStateChanged(int)));

    m_resetApexButton = new QPushButton(QStringLiteral("重置峰值曲线"), this);
    m_resetApexButton->setFlat(true);

    QObject::connect(m_resetApexButton, SIGNAL(clicked(bool)), this, SLOT(onResetApexButtonClick(bool)));

    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_splitter,1, 0);

    QHBoxLayout* headLayout = new QHBoxLayout();
    headLayout->setMargin(0);

    headLayout->addWidget(m_showVAxisBox);
    headLayout->addWidget(m_showApexBox);
    headLayout->addWidget(m_resetApexButton);
    headLayout->addStretch();
    headLayout->addWidget(m_freqLabel);
    headLayout->addWidget(m_infoLabel);

    mainLayout->addLayout(headLayout, 0, 0);
    this->setLayout(mainLayout);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, m_waterfall->backColor());
    palette.setColor(QPalette::WindowText, m_waterfall->vAxis()->textColor());
    palette.setColor(QPalette::Button, m_waterfall->backColor());
    palette.setColor(QPalette::ButtonText, m_waterfall->vAxis()->textColor());
    this->setPalette(palette);

    this->setWindowTitle(QStringLiteral("宽带频谱窗体"));
    this->resize(800, 600);

    QObject::connect(m_spectro, SIGNAL(showDataPointRangeUpdated(WRChartSampleRange)), m_waterfall, SLOT(setShowDataPointRange(WRChartSampleRange)));
    QObject::connect(m_waterfall, SIGNAL(showDataPointRangeUpdated(WRChartSampleRange)), m_spectro, SLOT(setShowDataPointRange(WRChartSampleRange)));

    QObject::connect(m_spectro->dataView(), SIGNAL(mouseDragChanged(WRPoint,WRPoint)), this, SLOT(onSpectroMouseDragChanged(WRPoint,WRPoint)));
    QObject::connect(m_spectro->dataView(), SIGNAL(mouseDragReleased(WRPoint,WRPoint)), this, SLOT(onSpectroMouseDragReleased(WRPoint,WRPoint)));

    QObject::connect(m_waterfall->dataView(), SIGNAL(mouseDragChanged(WRPoint,WRPoint)), this, SLOT(onWaterfallMouseDragChanged(WRPoint,WRPoint)));
    QObject::connect(m_waterfall->dataView(), SIGNAL(mouseDragReleased(WRPoint,WRPoint)), this, SLOT(onWaterfallMouseDragReleased(WRPoint,WRPoint)));

    QObject::connect(m_spectro->dataView(), SIGNAL(mouseDown(QMouseEvent*)), this, SLOT(onSpectroDataViewMouseDown(QMouseEvent*)));
    QObject::connect(m_spectro->hAxis(), SIGNAL(mouseDown(QMouseEvent*)), this, SLOT(onSpectroHAxisMouseDown(QMouseEvent*)));

    QObject::connect(m_waterfall->dataView(), SIGNAL(mouseDown(QMouseEvent*)), this, SLOT(onWaterfallDataViewMouseDown(QMouseEvent*)));
    QObject::connect(m_waterfall->hAxis(), SIGNAL(mouseDown(QMouseEvent*)), this, SLOT(onWaterfallHAxisMouseDown(QMouseEvent*)));

    QObject::connect(m_spectroVLine, SIGNAL(positionChanged(int)), this, SLOT(onSpectroVLinePositionChanged(int)));
    QObject::connect(m_spectroVLine, SIGNAL(positionUpdated(int)), m_waterfallVLine, SLOT(setPosition(int)));
    QObject::connect(m_waterfallVLine, SIGNAL(positionUpdated(int)), m_spectroVLine, SLOT(setPosition(int)));

    m_thread = new WBSpecThread(m_spectro, m_waterfall);
}

WBSpecWindow::~WBSpecWindow()
{
    if (m_thread)
    {
        delete m_thread;
    }
    m_spectro->release();
    m_waterfall->release();
}

void WBSpecWindow::onSpectroDataViewMouseDown(QMouseEvent* e)
{
    int i = 0;
    if (m_spectro->getDataPointAt(e->pos(), &i))
    {
        m_spectroVLine->position(i);
        m_waterfallVLine->position(i);
    }
}
void WBSpecWindow::onWaterfallDataViewMouseDown(QMouseEvent* e)
{
    int i = 0;
    if (m_waterfall->getDataPointAt(e->pos(), &i))
    {
        m_spectroVLine->position(i);
        m_waterfallVLine->position(i);
    }
}
void WBSpecWindow::onSpectroHAxisMouseDown(QMouseEvent* e)
{
    int i = 0;
    if (m_spectro->getDataPointAt(e->pos(), &i))
    {
        m_spectroVLine->position(i);
        m_waterfallVLine->position(i);
    }
}
void WBSpecWindow::onWaterfallHAxisMouseDown(QMouseEvent* e)
{
    int i = 0;
    if (m_waterfall->getDataPointAt(e->pos(), &i))
    {
        m_spectroVLine->position(i);
        m_waterfallVLine->position(i);
    }
}

void WBSpecWindow::onSpectroVLinePositionChanged(int value)
{
    if (value >= 0 && value < m_spectro->dataPointCount())
    {
        char buffer[256];
        int length = WRText::toFreqString(m_spectro->getFreqValueAt(value), buffer);
        m_freqLabel->setText(QString::fromLatin1(buffer, length));
    }
    else
    {
        static QString empty = QStringLiteral("频率未知");
        m_freqLabel->setText(empty);
    }
}

void WBSpecWindow::onSpectroMouseDragChanged(const WRPoint& begPos, const WRPoint& endPos)
{
    m_infoLabel->setVisible(true);
    if (m_spectro->dataView()->mouseDragMode() == WRChartDataViewElement::MouseDragLine)
    {

    }
    else
    {
        long long freqBegin, freqEnd;
        if (begPos.x() < endPos.x())
        {
            m_spectro->getFreqValueAt(begPos, &freqBegin);
            m_spectro->getFreqValueAt(endPos, &freqEnd);
        }
        else
        {
            m_spectro->getFreqValueAt(endPos, &freqBegin);
            m_spectro->getFreqValueAt(begPos, &freqEnd);
        }
        char buffer[256];
        int length = WRText::toFreqString(freqBegin, buffer);
        buffer[length] = '-';
        ++length;
        length += WRText::toFreqString(freqEnd, buffer + length);
        m_infoLabel->setText(QString::fromLatin1(buffer, length));
    }
}
void WBSpecWindow::onSpectroMouseDragReleased(const WRPoint&, const WRPoint&)
{
    m_infoLabel->setVisible(false);
}

void WBSpecWindow::onWaterfallMouseDragChanged(const WRPoint& begPos, const WRPoint& endPos)
{
    m_infoLabel->setVisible(true);
    if (m_waterfall->dataView()->mouseDragMode() == WRChartDataViewElement::MouseDragLine)
    {

    }
    else
    {
        long long freqBegin, freqEnd;
        if (begPos.x() < endPos.x())
        {
            m_waterfall->getFreqValueAt(begPos, &freqBegin);
            m_waterfall->getFreqValueAt(endPos, &freqEnd);
        }
        else
        {
            m_waterfall->getFreqValueAt(endPos, &freqBegin);
            m_waterfall->getFreqValueAt(begPos, &freqEnd);
        }
        char buffer[256];
        int length = WRText::toFreqString(freqBegin, buffer);
        buffer[length] = '-';
        ++length;
        length += WRText::toFreqString(freqEnd, buffer + length);
        m_infoLabel->setText(QString::fromLatin1(buffer, length));
    }
}
void WBSpecWindow::onWaterfallMouseDragReleased(const WRPoint&, const WRPoint&)
{
    m_infoLabel->setVisible(false);
}

void WBSpecWindow::onShowVAxisBoxStateChanged(int)
{
    bool visible = m_showVAxisBox->checkState() == Qt::Checked;
    m_spectro->vAxis()->visible(visible);
    m_waterfall->vAxis()->visible(visible);
}
void WBSpecWindow::onShowApexBoxStateChanged(int)
{
    m_spectro->channel(0)->visible(m_showApexBox->checkState() == Qt::Checked);
}
void WBSpecWindow::onResetApexButtonClick(bool)
{
    m_thread->resetApex();
}
