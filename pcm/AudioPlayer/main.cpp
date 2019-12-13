#include "dialog.h"
#include <QApplication>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QFile>
#include <QDebug>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const QString fileName = "..\\AudioPlayer\\test.pcm";

    if(QFile::exists(fileName))
    {
        qDebug() << "PCM file exist.";
    }
    else
    {
        qDebug() << "PCM file not exist.";
        return -1;
    }
    QFile inputFile(fileName);

    inputFile.open(QIODevice::ReadOnly);

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

    QAudioOutput *audio = new QAudioOutput(audioFormat, 0);
    //开始播放
    audio->start(&inputFile);

    return a.exec();
}
