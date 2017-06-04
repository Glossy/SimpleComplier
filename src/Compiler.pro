#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T17:10:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


TARGET = Compiler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    draw_form.cpp \
    Parser.cpp \
    Scanner.cpp \
    about_form.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    draw_form.h \
    Parser.h \
    Scanner.h \
    about_form.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    draw_form.ui \
    about_form.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    images/overwatch.ico \
    images/overwatch.rc
RC_FILE = overwatch.rc
