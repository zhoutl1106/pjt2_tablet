#-------------------------------------------------
#
# Project created by QtCreator 2015-07-09T14:58:48
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

TARGET = pjt2_tablet
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dialogautoclosemessagebox.cpp \
    forms/formmain.cpp \
    dialog.cpp \
    filemanager.cpp \
    forms/formvibrationadjust.cpp \
    longclicktoolbutton.cpp \
    forms/formmodeselect.cpp \
    forms/formaccuracyadjust.cpp \
    multistatustoolbutton.cpp \
    forms/formall.cpp

HEADERS  += widget.h \
    dialogautoclosemessagebox.h \
    forms/formmain.h \
    dialog.h \
    filemanager.h \
    forms/formvibrationadjust.h \
    longclicktoolbutton.h \
    forms/formmodeselect.h \
    forms/formaccuracyadjust.h \
    multistatustoolbutton.h \
    forms/formall.h

FORMS    += widget.ui \
    dialogautoclosemessagebox.ui \
    forms/formmain.ui \
    dialog.ui \
    forms/formvibrationadjust.ui \
    forms/formmodeselect.ui \
    forms/formaccuracyadjust.ui \
    forms/formall.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resource.qrc

DISTFILES += \
    qss.qss \
    android/AndroidManifest.xml

