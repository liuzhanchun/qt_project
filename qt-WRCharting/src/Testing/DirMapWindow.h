#ifndef DIRMAPWINDOW
#define DIRMAPWINDOW

#include <QWidget>
#include <QThread>

#include <WRCharting/WRDirMapControl.h>

namespace Ui {
class DirMapWindow;
}

class DirMapThread;

class DirMapWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DirMapWindow(QWidget *parent = 0);
    ~DirMapWindow();

private:
    Ui::DirMapWindow *ui;
    WRDirMapControl* chart;
    DirMapThread* thread;
};

#endif // DIRMAPWINDOW
