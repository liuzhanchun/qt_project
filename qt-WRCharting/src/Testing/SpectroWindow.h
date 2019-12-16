#ifndef SPECTROWINDOW
#define SPECTROWINDOW

#include <QWidget>
#include <QThread>

#include <WRCharting/WRSpectroControl.h>

namespace Ui {
class SpectroWindow;
}

class SpectroThread;

class SpectroWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SpectroWindow(QWidget *parent = 0);
    ~SpectroWindow();

private:
    Ui::SpectroWindow *ui;
    WRSpectroControl* chart;
    SpectroThread* thread;
};

#endif // SPECTROWINDOW
