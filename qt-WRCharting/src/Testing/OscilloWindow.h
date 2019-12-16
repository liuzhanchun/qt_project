#ifndef OSCILLOWINDOW
#define OSCILLOWINDOW

#include <QWidget>
#include <QThread>

#include <WRCharting/WROscilloControl.h>

namespace Ui {
class OscilloWindow;
}

class OscilloThread;

class OscilloWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OscilloWindow(QWidget *parent = 0);
    ~OscilloWindow();

private:
    Ui::OscilloWindow *ui;
    WROscilloControl* chart;
    OscilloThread* thread;
};

#endif // OSCILLOWINDOW
