QT += core gui

CONFIG += c++17 console
CONFIG -= app_bundle
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        SparseMatrix.cpp \
        Visualize.cpp \
        main.cpp \
        mainwindow.cpp \
        qcustomplot.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Visualize.hpp \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui
