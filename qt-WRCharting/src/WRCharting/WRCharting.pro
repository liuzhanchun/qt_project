greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
CONFIG += staticlib
CONFIG += debug_and_release

CONFIG(debug, debug|release) {
    TARGET = WRChartingd
    OBJECTS_DIR = $$PWD/../../obj/WRCharting/debug
}
CONFIG(release, debug|release) {
    TARGET = WRCharting
    OBJECTS_DIR = $$PWD/../../obj/WRCharting/release
}
VERSION = 1.0.0.0

DESTDIR = $$PWD/../../lib/WRCharting
MOC_DIR = $$PWD/../../moc/WRCharting

#DEFINES += WRCHARTING_LIBRARY
DEFINES += WRCHARTING_STATICLIB

HEADERS += \
    ../../include/WRCharting/WRChartAxisElement.h \
    ../../include/WRCharting/WRChartControl.h \
    ../../include/WRCharting/WRChartDataViewElement.h \
    ../../include/WRCharting/WRChartDValueRange.h \
    ../../include/WRCharting/WRChartElement.h \
    ../../include/WRCharting/WRChartPrivate.h \
    ../../include/WRCharting/WRChartSampleRange.h \
    ../../include/WRCharting/WRChartScrollElement.h \
    ../../include/WRCharting/WRColor.h \
    ../../include/WRCharting/WRGlobal.h \
    ../../include/WRCharting/WRLine.h \
    ../../include/WRCharting/WRMath.h \
    ../../include/WRCharting/WRMutex.h \
    ../../include/WRCharting/WRPoint.h \
    ../../include/WRCharting/WRRect.h \
    ../../include/WRCharting/WRSize.h \
    ../../include/WRCharting/WRText.h \
    ../../include/WRCharting/WRDirMapAxisElement.h \
    ../../include/WRCharting/WRDirMapControl.h \
    ../../include/WRCharting/WRDirMapDataPalette.h \
    ../../include/WRCharting/WRDirMapDataRange.h \
    ../../include/WRCharting/WRDirMapDataSource.h \
    WRDirMapDataSourceT.h \
    ../../include/WRCharting/WRDirMapDataViewElement.h \
    ../../include/WRCharting/WRDirMapGaugeElement.h \
    ../../include/WRCharting/WRDirMapInitParams.h \
    ../../include/WRCharting/WRDirMapLineElement.h \
    ../../include/WRCharting/WRDirMapScrollElement.h \
    ../../include/WRCharting/WRGlobal.h \
    ../../include/WRCharting/WRGlobal.h \
    ../../include/WRCharting/WRSpectroAxisElement.h \
    ../../include/WRCharting/WRSpectroChannel.h \
    ../../include/WRCharting/WRSpectroControl.h \
    ../../include/WRCharting/WRSpectroDataRange.h \
    ../../include/WRCharting/WRSpectroDataSource.h \
    WRSpectroDataSourceT.h \
    ../../include/WRCharting/WRSpectroDataViewElement.h \
    ../../include/WRCharting/WRSpectroGaugeElement.h \
    ../../include/WRCharting/WRSpectroInitParams.h \
    ../../include/WRCharting/WRSpectroLineElement.h \
    ../../include/WRCharting/WRSpectroScrollElement.h \
    ../../include/WRCharting/WRWaterfallAxisElement.h \
    ../../include/WRCharting/WRWaterfallControl.h \
    ../../include/WRCharting/WRWaterfallDataPalette.h \
    ../../include/WRCharting/WRWaterfallDataRange.h \
    ../../include/WRCharting/WRWaterfallDataSource.h \
    WRWaterfallDataSourceT.h \
    ../../include/WRCharting/WRWaterfallDataViewElement.h \
    ../../include/WRCharting/WRWaterfallGaugeElement.h \
    ../../include/WRCharting/WRWaterfallInitParams.h \
    ../../include/WRCharting/WRWaterfallLineElement.h \
    ../../include/WRCharting/WRWaterfallScrollElement.h \
    ../../include/WRCharting/WRGlobal.h \
    ../../include/WRCharting/WROscilloAxisElement.h \
    ../../include/WRCharting/WROscilloControl.h \
    ../../include/WRCharting/WROscilloDataRange.h \
    ../../include/WRCharting/WROscilloDataSource.h \
    WROscilloDataSourceT.h \
    ../../include/WRCharting/WROscilloDataViewElement.h \
    ../../include/WRCharting/WROscilloGaugeElement.h \
    ../../include/WRCharting/WROscilloInitParams.h \
    ../../include/WRCharting/WROscilloLineElement.h \
    ../../include/WRCharting/WROscilloScrollElement.h

SOURCES += \
    WRChartAxisElement.cpp \
    WRChartControl.cpp \
    WRChartDataViewElement.cpp \
    WRChartElement.cpp \
    WRChartPrivate.cpp \
    WRChartScrollElement.cpp \
    WRDirMapAxisElement.cpp \
    WRDirMapControl.cpp \
    WRDirMapDataPalette.cpp \
    WRDirMapDataViewElement.cpp \
    WRDirMapLineElement.cpp \
    WRDirMapScrollElement.cpp \
    WRSpectroAxisElement.cpp \
    WRSpectroChannel.cpp \
    WRSpectroControl.cpp \
    WRSpectroDataViewElement.cpp \
    WRSpectroLineElement.cpp \
    WRSpectroScrollElement.cpp \
    WRWaterfallAxisElement.cpp \
    WRWaterfallControl.cpp \
    WRWaterfallDataPalette.cpp \
    WRWaterfallDataViewElement.cpp \
    WRWaterfallLineElement.cpp \
    WRWaterfallScrollElement.cpp \
    WROscilloAxisElement.cpp \
    WROscilloControl.cpp \
    WROscilloDataViewElement.cpp \
    WROscilloLineElement.cpp \
    WROscilloScrollElement.cpp

INCLUDEPATH += $$PWD/../../include
