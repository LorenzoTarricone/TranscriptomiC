QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

<<<<<<< Updated upstream
=======
<<<<<<< HEAD
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

>>>>>>> Stashed changes
SOURCES += \
    api.cpp \
    api_gene_name.cpp \
    bioprocesswindow.cpp \
    colocalizationwindow.cpp \
    filedata.cpp \
    genename.cpp \
    intersection_sets.cpp \
    main.cpp \
    main_API_bio_pro_to_gene.cpp \
    main_API_gene_name.cpp \
    mainwindow.cpp \
    matrixeigen.cpp \
    parsemtx.cpp \
    qcustomplot.cpp \
<<<<<<< Updated upstream
=======
=======
SOURCES += \
    api.cpp \
    api_gene_name.cpp \
    bioprocesswindow.cpp \
    colocalizationwindow.cpp \
    filedata.cpp \
    genename.cpp \
    intersection_sets.cpp \
    main.cpp \
    main_API_bio_pro_to_gene.cpp \
    main_API_gene_name.cpp \
    mainwindow.cpp \
    matrixeigen.cpp \
    parsemtx.cpp \
    qcustomplot.cpp \
>>>>>>> Stashed changes
    secondwindow.cpp \
    SparseMatrix.cpp \
    colocalization_matrix.cpp \
    readgenetxt.cpp \
    only_gene_name.cpp \
    read_tsv_set.cpp

HEADERS += \
    api.hpp \
    api_gene_name.h \
    bioprocesswindow.h \
    colocalizationwindow.h \
    filedata.h \
    genename.h \
    intersection_sets.h \
    mainwindow.h \
    matrixeigen.h \
    parsemtx.h \
    qcustomplot.h \
    SparseMatrix.h \
    SecondWindow.h \
    readgenetxt.h \
    only_gene_name.h \
    read_tsv_set.h

<<<<<<< Updated upstream
=======
>>>>>>> API
>>>>>>> Stashed changes

FORMS += \
    SecondWindow.ui \
    bioprocesswindow.ui \
    colocalizationwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

<<<<<<< Updated upstream
INCLUDEPATH += "eigen-3.4.0"

macx: LIBS += -lcurl
=======
<<<<<<< HEAD
win32:INCLUDEPATH += "eigen-3.4.0/eigen-3.4.0"
macx:INCLUDEPATH += "$$PWD/eigen_mac"

#INCLUDEPATH += /Users/adrianduesselberg/CSE201Pro/eigen-3.4.0

#INCLUDEPATH += "C:\Users\ritux\OneDrive - Danmarks Tekniske Universitet\Skrivebord\Rita's Stuff\l'X\1 2 CSE201\eigen-3.4.0\eigen-3.4.0"
#INCLUDEPATH += "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_test_matrix/eigen"

#LinkParameterWindow.cpp \
=======
INCLUDEPATH += "eigen-3.4.0"

macx: LIBS += -lcurl
>>>>>>> API
>>>>>>> Stashed changes
