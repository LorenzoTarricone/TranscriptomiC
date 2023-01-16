QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    #Back-End
    #genename.h \
    #parsemtx.h \
    filedata.h \
    #matrixeigen.h \
    #SparseMatrix.h \
    #Front-End
    MenuWindow.h \
    UploadWindow.h \
    bioprocesswindow.h \
    heatmapwindow.h \
    colocalizationwindow.h \
    colocalizationheatmapwindow.h \
    #Package
    qcustomplot.h

SOURCES += \
    main.cpp \
    #Back-End
    #parsemtx.cpp \
    filedata.cpp \
    #genename.cpp \
    #matrixeigen.cpp \
    #SparseMatrix.cpp \
    #colocalization_matrix.cpp\
    #Front-End
    MenuWindow.cpp \
    UploadWindow.cpp \
    bioprocesswindow.cpp \
    heatmapwindow.cpp \
    colocalizationwindow.cpp \
    colocalizationheatmapwindow.cpp \
    #Package
    qcustomplot.cpp \

FORMS += \
    MenuWindow.ui \
    UploadWindow.ui \
    bioprocesswindow.ui \
    heatmapwindow.ui\
    colocalizationheatmapwindow.ui \
    colocalizationwindow.ui \


INCLUDEPATH += "C:\Users\ritux\OneDrive - Danmarks Tekniske Universitet\Skrivebord\Rita's Stuff\l'X\1 2 CSE201\Project\eigen-3.4.0\eigen-3.4.0"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:INCLUDEPATH += "eigen-3.4.0/eigen-3.4.0"
#macx:INCLUDEPATH += "$$PWD/eigen_mac"



#INCLUDEPATH += "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_test_matrix/eigen"

#LinkParameterWindow.cpp \
