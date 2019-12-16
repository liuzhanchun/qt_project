#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_dirMapButton_clicked();

    void on_oscilloButton_clicked();

    void on_spectroButton_clicked();

    void on_vWaterfallButton_clicked();

    void on_hWaterfallButton_clicked();

    void on_wbSpecButton_clicked();

protected:

    void resizeEvent ( QResizeEvent * e);

private:
    Ui::MainWindow *ui;

    void showChildWindow(QWidget* window );
};

#endif // MAINWINDOW_H
