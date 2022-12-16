QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bioprocesswindow.cpp \
    colocalizationwindow.cpp \
    filedata.cpp \
    genename.cpp \
    main.cpp \
    mainwindow.cpp \
    matrixeigen.cpp \
    parsemtx.cpp \
    parsetxtbeams.cpp \
    qcustomplot.cpp \
    secondwindow.cpp \
    SparseMatrix.cpp \
    colocalization_matrix.cpp

HEADERS += \
    bioprocesswindow.h \
    colocalizationwindow.h \
    filedata.h \
    genename.h \
    mainwindow.h \
    matrixeigen.h \
    parsemtx.h \
    parsetxtbeams.h \
    qcustomplot.h \
    SparseMatrix.h \
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

#INCLUDEPATH += "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_test_matrix/eigen"


