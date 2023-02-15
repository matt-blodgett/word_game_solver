message("word_game_solver.pro")
message("Build Target = $$BUILD_TARGET")
message("Build File = $$_PRO_FILE_")
message("Build Dest Dir = $$DESTDIR")
message("Qt Version = $$[QT_VERSION]")
message("Qt Bin Dir = $$[QT_INSTALL_BINS]")
message("Qt Docs Dir = $$[QT_INSTALL_DOCS]")
message("Qt Libs Dir = $$[QT_INSTALL_LIBS]")
message("Qt Headers Dir = $$[QT_INSTALL_HEADERS]")
message("qmake = $$QMAKE_QMAKE")
message("qmakespec = $$QMAKESPEC")
message("Host OS = $$QMAKE_HOST.os v$$QMAKE_HOST.version")
message("Host Name = $$QMAKE_HOST.name")
message("Host Arch = $$QMAKE_HOST.arch")
message("Host Cores = $$QMAKE_HOST.cpu_count")


DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
DEFINES += QT_NO_NARROWING_CONVERSIONS_IN_CONNECT
DEFINES += QT_DEPRECATED_WARNINGS


TEMPLATE = app


QT += core
QT += gui
QT += widgets


CONFIG += c++17



SOURCES += main.cpp

HEADERS += components/mainwindow.h
HEADERS += components/wordlistview.h
HEADERS += components/boardview.h
HEADERS += components/controlsview.h

SOURCES += components/mainwindow.cpp
SOURCES += components/wordlistview.cpp
SOURCES += components/boardview.cpp
SOURCES += components/controlsview.cpp

HEADERS += utils/board.h
HEADERS += utils/solver.h

SOURCES += utils/board.cpp
SOURCES += utils/solver.cpp

#RESOURCES += assets/assets.qrc
