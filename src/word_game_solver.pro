DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
DEFINES += QT_NO_NARROWING_CONVERSIONS_IN_CONNECT
DEFINES += QT_DEPRECATED_WARNINGS


QT += core
QT += gui
QT += widgets


CONFIG += c++17


TEMPLATE = app


SOURCES += main.cpp \
    utils/worker.cpp
HEADERS += version.h \
    utils/worker.h

HEADERS += mainwindow.h
SOURCES += mainwindow.cpp

HEADERS += utils/board.h
HEADERS += utils/solver.h

SOURCES += utils/board.cpp
SOURCES += utils/solver.cpp

HEADERS += frames/frameboard.h
HEADERS += frames/framecontrols.h
HEADERS += frames/framewordlist.h

SOURCES += frames/frameboard.cpp
SOURCES += frames/framecontrols.cpp
SOURCES += frames/framewordlist.cpp

RESOURCES += assets/assets.qrc


TARGET = wgsolver

win32 {
    RC_FILE = assets/windows.rc
    QMAKE_TARGET_PRODUCT = "wgsolver"
    QMAKE_TARGET_DESCRIPTION = "Word Game Solver"
}










