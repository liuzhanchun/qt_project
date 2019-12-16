#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "DirMapWindow.h"
#include "OscilloWindow.h"
#include "SpectroWindow.h"
#include "VWaterfallWindow.h"
#include "HWaterfallWindow.h"

#include "WBSpecWindow.h"

#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent (QResizeEvent * e)
{
    ui->horizontalLayoutWidget->resize(e->size().width(), ui->horizontalLayoutWidget->height());
}

//显示子窗体。
void MainWindow::showChildWindow(QWidget* window )
{
    window->setParent(this, Qt::Window);
    window->setAttribute(Qt::WA_DeleteOnClose, true);
    window->show();
}

void MainWindow::on_dirMapButton_clicked()
{
    showChildWindow(new DirMapWindow());
}

void MainWindow::on_oscilloButton_clicked()
{
    showChildWindow(new OscilloWindow());
}

void MainWindow::on_spectroButton_clicked()
{
    showChildWindow(new SpectroWindow());
}

void MainWindow::on_vWaterfallButton_clicked()
{
    showChildWindow(new VWaterfallWindow());
}

void MainWindow::on_hWaterfallButton_clicked()
{
    showChildWindow(new HWaterfallWindow());
}

void MainWindow::on_wbSpecButton_clicked()
{
    showChildWindow(new WBSpecWindow());
}
