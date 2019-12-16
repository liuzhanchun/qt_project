#ifndef VWATERFALLWINDOW
#define VWATERFALLWINDOW

#include <QWidget>
#include <QThread>

#include <WRCharting/WRWaterfallControl.h>

namespace Ui {
class VWaterfallWindow;
}

class VWaterfallThread;

class VWaterfallWindow : public QWidget
{
    Q_OBJECT

public:
    explicit VWaterfallWindow(QWidget *parent = 0);
    ~VWaterfallWindow();

private:
    Ui::VWaterfallWindow *ui;
    WRWaterfallControl* chart;
    VWaterfallThread* thread;
};

#endif // VWATERFALLWINDOW
