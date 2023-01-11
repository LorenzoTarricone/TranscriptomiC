QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bioprocesswindow.cpp \
    colocalisation.cpp \
    colocalisation_steps.cpp \
    colocalizationwindow.cpp \
    filedata.cpp \
    genename.cpp \
    main.cpp \
    mainwindow.cpp \
    matrixeigen.cpp \
    parsemtx.cpp \
    parsetxtbeams.cpp \
    parsing.cpp \
    qcustomplot.cpp \
    secondwindow.cpp \
    SparseMatrix.cpp \
    colocalization_matrix.cpp

HEADERS += \
    bioprocesswindow.h \
    colocalisation.h \
    colocalizationwindow.h \
    filedata.h \
    genename.h \
    mainwindow.h \
    matrixeigen.h \
    parsemtx.h \
    parsetxtbeams.h \
    parsing.h \
    qcustomplot.h \
    colocalization_matrix.h \
    SecondWindow.h

FORMS += \
    SecondWindow.ui \
    bioprocesswindow.ui \
    colocalizationwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:INCLUDEPATH += "eigen-3.4.0/eigen-3.4.0"
macx:INCLUDEPATH += "$$PWD/eigen_mac"

#INCLUDEPATH += "/Users/alanpicucci/Desktop/Programming/Includes/eigen-3.4.0"


