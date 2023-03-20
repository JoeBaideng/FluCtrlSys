QT       += core gui serialport xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#Edited by Qt5.14.2
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    delegates/combodelegate.cpp \
    delegates/readonlydelegate.cpp \
    delegates/spindelegate.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    selectionview.cpp \
    serialcontrol.cpp \
    xmleditor.cpp

HEADERS += \
    delegates/combodelegate.h \
    delegates/readonlydelegate.h \
    delegates/spindelegate.h \
    dialog.h \
    mainwindow.h \
    mystructs.h \
    selectionview.h \
    serialcontrol.h \
    xmleditor.h

FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
