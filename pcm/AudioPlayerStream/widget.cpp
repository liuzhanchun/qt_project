#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //获取文件的指针
    FILE *file=fopen("..\\test.pcm","rb");
    if(!file)
    {
        qDebug()<<"Open Failed";
        return;
    }
    //把指针移动到文件的结尾 ，获取文件长度
    fseek(file,0,SEEK_END);
    //获取文件长度
    fileLength=ftell(file);
    //定义数组长度
    fileBuffer=new char[fileLength+1];
    //把指针移动到文件开头 因为我们一开始把指针移动到结尾，如果不移动回来 会出错
    rewind(file);
    //读文件
    fread(fileBuffer,1,fileLength,file);
    //把读到的文件最后一位 写为0 要不然系统会一直寻找到0后才结束
    fileBuffer[fileLength]=0;
    //关闭文件
    fclose(file);
    qDebug()<<fileLength;

    //设置采样格式
    QAudioFormat audioFormat;
    //设置采样率
    audioFormat.setSampleRate(44100);
    //设置通道数
    audioFormat.setChannelCount(2);
    //设置采样大小，一般为8位或16位
    audioFormat.setSampleSize(16);
    //设置编码方式
    audioFormat.setCodec("audio/pcm");
    //设置字节序
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    //设置样本数据类型
    audioFormat.setSampleType(QAudioFormat::UnSignedInt);
    //音频设备信息
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultOutputDevice();
    if (!info.isFormatSupported(audioFormat)) {
        qDebug()<<"default format not supported try to use nearest";
        audioFormat = info.nearestFormat(audioFormat);
    }
    audioOutput = new QAudioOutput(audioFormat, this);
    streamOut = audioOutput->start();
    //定时器
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(slotTimeout()));
}

Widget::~Widget()
{
    delete ui;
    if(timer->isActive())
    {
        timer->stop();
    }
}

void Widget::slotTimeout()
{
    static int i=0;
    if(i<fileLength/1764)
    {
        tempBuffer.append(fileBuffer+i*1764,1764);

        if(audioOutput&&audioOutput->state()!=QAudio::StoppedState&&
                audioOutput->state()!=QAudio::SuspendedState)
        {
            int chunks = audioOutput->bytesFree()/audioOutput->periodSize();
            while (chunks)
            {
                if (tempBuffer.length() >= audioOutput->periodSize())
                {
                    //写入到扬声器
                    streamOut->write(tempBuffer.data(),audioOutput->periodSize());
                    tempBuffer = tempBuffer.mid(audioOutput->periodSize());
                }
                else
                {
                    //写入到扬声器
                    streamOut->write(tempBuffer);
                    tempBuffer.clear();
                    break;
                }
                --chunks;
            }
        }
    }
    i++;
}

void Widget::on_pushButton_clicked()
{
     static bool flag=true;
     if(flag)
     {
         timer->start(10);
         ui->pushButton->setText(QStringLiteral("暂停"));
     }
     else
     {
         timer->stop();
         ui->pushButton->setText(QStringLiteral("播放"));
     }
     flag=!flag;
}
