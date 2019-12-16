#ifndef HWATERFALLWINDOW
#define HWATERFALLWINDOW

#include <QWidget>
#include <QThread>

#include <WRCharting/WRWaterfallControl.h>

namespace Ui {
class HWaterfallWindow;
}

class HWaterfallThread;

class HWaterfallWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HWaterfallWindow(QWidget *parent = 0);
    ~HWaterfallWindow();

private:
    Ui::HWaterfallWindow *ui;
    WRWaterfallControl* chart;
    HWaterfallThread* thread;
};

#endif // HWATERFALLWINDOW
