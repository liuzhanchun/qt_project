#ifndef WBSPECWINDOW_H
#define WBSPECWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QSplitter>
#include <QPushButton>
#include <QCheckBox>
#include <WRCharting/WRSpectroControl.h>
#include <WRCharting/WRWaterfallControl.h>

//声明宽带频谱线程。
class WBSpecThread;

//表示宽带频谱窗体。
class WBSpecWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WBSpecWindow(QWidget *parent = 0);
    ~WBSpecWindow();

private:
    WBSpecThread* m_thread;
    QSplitter* m_splitter;
    QWidget* m_spectroWidget;
    QWidget* m_waterfallWidget;
    WRSpectroControl* m_spectro;
    WRSpectroDataPointLineElement* m_spectroVLine;
    WRWaterfallControl* m_waterfall;
    WRWaterfallDataPointLineElement* m_waterfallVLine;
    QLabel* m_freqLabel;
    QLabel* m_infoLabel;
    QCheckBox* m_showVAxisBox;
    QCheckBox* m_showApexBox;
    QPushButton* m_resetApexButton;

private slots:
    void onSpectroVLinePositionChanged(int value);

    void onSpectroDataViewMouseDown(QMouseEvent* e);
    void onWaterfallDataViewMouseDown(QMouseEvent* e);
    void onSpectroHAxisMouseDown(QMouseEvent* e);
    void onWaterfallHAxisMouseDown(QMouseEvent* e);

    void onSpectroMouseDragChanged(const WRPoint& begPos, const WRPoint& endPos);
    void onSpectroMouseDragReleased(const WRPoint& begPos, const WRPoint& endPos);

    void onWaterfallMouseDragChanged(const WRPoint& begPos, const WRPoint& endPos);
    void onWaterfallMouseDragReleased(const WRPoint& begPos, const WRPoint& endPos);

    void onShowVAxisBoxStateChanged(int);
    void onShowApexBoxStateChanged(int);
    void onResetApexButtonClick(bool);
};

#endif // WBSPECWINDOW_H
