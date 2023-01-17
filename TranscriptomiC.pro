QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< HEAD
    MenuWindow.cpp \
    UploadWindow.cpp \
    biologicalprocess.cpp \
=======
    api.cpp \
    api_gene_name.cpp \
>>>>>>> 49aef06a8a9495f98007cd45b6805df065043d34
    bioprocesswindow.cpp \
    colocalisation.cpp \
    colocalisation_steps.cpp \
    colocalizationwindow.cpp \
    computation.cpp \
    filedata.cpp \
    genename.cpp \
    intersection_sets.cpp \
    main.cpp \
<<<<<<< HEAD
=======
    main_API_bio_pro_to_gene.cpp \
    main_API_gene_name.cpp \
    mainwindow.cpp \
>>>>>>> 49aef06a8a9495f98007cd45b6805df065043d34
    matrixeigen.cpp \
    parsefile.cpp \
    parsemtx.cpp \
    parsetxtbeams.cpp \
    parsing.cpp \
    qcustomplot.cpp \
<<<<<<< HEAD
#    SparseMatrix.cpp \
    colocalization_matrix.cpp

HEADERS += \
    MenuWindow.h \
    UploadWindow.h \
    biologicalprocess.h \
=======
    secondwindow.cpp \
    SparseMatrix.cpp \
    colocalization_matrix.cpp \
    readgenetxt.cpp \
    only_gene_name.cpp \
    read_tsv_set.cpp

HEADERS += \
    api.hpp \
    api_gene_name.h \
>>>>>>> 49aef06a8a9495f98007cd45b6805df065043d34
    bioprocesswindow.h \
    colocalisation.h \
    colocalizationwindow.h \
    computation.h \
    filedata.h \
    genename.h \
<<<<<<< HEAD
=======
    intersection_sets.h \
    mainwindow.h \
>>>>>>> 49aef06a8a9495f98007cd45b6805df065043d34
    matrixeigen.h \
    parsefile.h \
    parsemtx.h \
    qcustomplot.h \
<<<<<<< HEAD
#    SparseMatrix.h \
    parsetxtbeams.h \
    parsing.h \
    qcustomplot.h \
    colocalization_matrix.h \
    SecondWindow.h \
=======
    SparseMatrix.h \
    SecondWindow.h \
    readgenetxt.h \
    only_gene_name.h \
    read_tsv_set.h

>>>>>>> 49aef06a8a9495f98007cd45b6805df065043d34

FORMS += \
    MenuWindow.ui \
    UploadWindow.ui \
    bioprocesswindow.ui \
    colocalizationwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

<<<<<<< HEAD
win32:INCLUDEPATH += "eigen-3.4.0/eigen-3.4.0"
macx:INCLUDEPATH += "$$PWD/eigen_mac"

#INCLUDEPATH += "C:\Users\ritux\OneDrive - Danmarks Tekniske Universitet\Skrivebord\Rita's Stuff\l'X\1 2 CSE201\eigen-3.4.0\eigen-3.4.0"
#INCLUDEPATH += "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_test_matrix/eigen"
#INCLUDEPATH += "/Users/alanpicucci/Desktop/Programming/Includes/eigen-3.4.0"


=======
INCLUDEPATH += "eigen-3.4.0"
>>>>>>> 49aef06a8a9495f98007cd45b6805df065043d34

macx: LIBS += -lcurl
