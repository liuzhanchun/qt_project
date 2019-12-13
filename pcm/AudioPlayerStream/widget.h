#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAudioOutput>
#include <QByteArray>
#include <QTimer>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QAudioOutput* audioOutput;
    QIODevice * streamOut;
    QByteArray tempBuffer;
    QTimer *timer;
    //定义文件指针
    char *fileBuffer;
    int fileLength;
private slots:
    void slotTimeout();
    void on_pushButton_clicked();
};

#endif // WIDGET_H
