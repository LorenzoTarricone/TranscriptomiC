QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MenuWindow.cpp \
    UploadWindow.cpp \
    bioprocesswindow.cpp \
    colocalisation.cpp \
    colocalisation_steps.cpp \
    colocalizationwindow.cpp \
    filedata.cpp \
    genename.cpp \
    main.cpp \
    matrixeigen.cpp \
    parsemtx.cpp \
    parsetxtbeams.cpp \
    parsing.cpp \
    qcustomplot.cpp \
#    SparseMatrix.cpp \
    colocalization_matrix.cpp \
    search.cpp

HEADERS += \
    MenuWindow.h \
    UploadWindow.h \
    bioprocesswindow.h \
    colocalisation.h \
    colocalizationwindow.h \
    filedata.h \
    genename.h \
    matrixeigen.h \
    parsemtx.h \
    qcustomplot.h \
#    SparseMatrix.h \
    parsetxtbeams.h \
    parsing.h \
    qcustomplot.h \
    colocalization_matrix.h \
    SecondWindow.h \
    search.h

FORMS += \
    MenuWindow.ui \
    UploadWindow.ui \
    bioprocesswindow.ui \
    colocalizationwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:INCLUDEPATH += "eigen-3.4.0/eigen-3.4.0"
#macx:INCLUDEPATH += "$$PWD/eigen_mac"

#INCLUDEPATH += "C:\Users\ritux\OneDrive - Danmarks Tekniske Universitet\Skrivebord\Rita's Stuff\l'X\1 2 CSE201\eigen-3.4.0\eigen-3.4.0"
#INCLUDEPATH += "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_test_matrix/eigen"
#INCLUDEPATH += "/Users/alanpicucci/Desktop/Programming/Includes/eigen-3.4.0"



