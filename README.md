# qt_project
Qt单元模块，使用示例

pcm 示例 
方法一 AudioPlayer  播放pcm文件
方法二 AudioPlayerStream  播放PCM数据流
这两种方法都需要在.pro文件中加入multimedia模块。
方法一是通过QAudioOutput实现的，先用QFile打开PCM文件，然后进行音频参数设置，最后调用QAudioOutput的start函数进行播放；
方法二也用到了QAudioOutput，先将PCM文件读取到内存，然后进行音频参数设置，最后从内存中定时读取部分数据，调用QIODevice的write函数将这部分数据写入到扬声器。
与方法一相比，方法二虽然麻烦，但是这种方法是进行语音编解码和语音网络传输的基础。


