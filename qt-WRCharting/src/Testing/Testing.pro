QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Testing
TEMPLATE = app

DEFINES += WRCHARTING_STATICLIB

SOURCES += main.cpp\
        MainWindow.cpp \
    OscilloWindow.cpp \
    DirMapWindow.cpp \
    SpectroWindow.cpp \
    VWaterfallWindow.cpp \
    HWaterfallWindow.cpp \
    WBSpecWindow.cpp

HEADERS  += MainWindow.h \
    OscilloWindow.h \
    DirMapWindow.h \
    SpecParams.h \
    SpectroWindow.h \
    VWaterfallWindow.h \
    HWaterfallWindow.h \
    WBSpecWindow.h

FORMS    += MainWindow.ui \
    DirMapWindow.ui \
    OscilloWindow.ui \
    SpectroWindow.ui \
    VWaterfallWindow.ui \
    HWaterfallWindow.ui

RESOURCES += \
    SpecFile.qrc \
    WaveFile.qrc

CONFIG(release, debug|release){
    LIBS += -L$$PWD/../../lib/WRCharting -lWRCharting
}
CONFIG(debug, debug|release){
    LIBS += -L$$PWD/../../lib/WRCharting -lWRChartingd
}

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
