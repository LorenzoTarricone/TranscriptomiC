QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    #general
    main.cpp \
    #API
    api.cpp \
    api_gene_name.cpp \
    genename.cpp \
    intersection_sets.cpp \
    main_API_bio_pro_to_gene.cpp \
    main_API_gene_name.cpp \
    readgenetxt.cpp \
    only_gene_name.cpp \
    read_tsv_set.cpp \
    #Back-End
    parsefile.cpp \
    parsemtx.cpp \
    parsetxtbeams.cpp \
    parsing.cpp \
    matrixeigen.cpp \
    SparseMatrix.cpp \
    colocalization_matrix.cpp\
    colocalisation.cpp \
    colocalisation_steps.cpp \
    biologicalprocess.cpp \
    computation.cpp \
    #Front-End
    MenuWindow.cpp \
    UploadWindow.cpp \
    bioprocesswindow.cpp \
    heatmapwindow.cpp \
    colocalizationwindow.cpp \
    colocalizationheatmapwindow.cpp \
    filedata.cpp \
    mainwindow.cpp \
    secondwindow.cpp \
    #Package
    qcustomplot.cpp \

HEADERS += \
    #API
    api.h \
    api_gene_name.h \
    genename.h \
    intersection_sets.h \
    main_API_bio_pro_to_gene.h \
    main_API_gene_name.h \
    readgenetxt.h \
    only_gene_name.h \
    read_tsv_set.h \
    #Back-End
    parsefile.h \
    parsemtx.h \
    parsetxtbeams.h \
    parsing.h \
    matrixeigen.h \
    SparseMatrix.h \
    colocalization_matrix.h\
    colocalisation.h \
    biologicalprocess.h \
    computation.h \
    #Front-End
    MenuWindow.h \
    UploadWindow.h \
    bioprocesswindow.h \
    heatmapwindow.h \
    colocalizationwindow.h \
    colocalizationheatmapwindow.h \
    filedata.h \
    SecondWindow.h \
    mainwindow.h \
    #Package
    qcustomplot.h \
    SparseMatrix.h \
    SecondWindow.h

FORMS += \
    MenuWindow.ui \
    UploadWindow.ui \
    bioprocesswindow.ui \
    heatmapwindow.ui\
    colocalizationheatmapwindow.ui \
    colocalizationwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:INCLUDEPATH += "eigen-3.4.0/eigen-3.4.0"
macx:INCLUDEPATH += "$$PWD/eigen_mac"

macx: LIBS += -lcurl


#INCLUDEPATH += /Users/adrianduesselberg/CSE201Pro/eigen-3.4.0

#INCLUDEPATH += "C:\Users\ritux\OneDrive - Danmarks Tekniske Universitet\Skrivebord\Rita's Stuff\l'X\1 2 CSE201\eigen-3.4.0\eigen-3.4.0"
#INCLUDEPATH += "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_test_matrix/eigen"

#LinkParameterWindow.cpp \

#INCLUDEPATH += "C:\Users\ritux\OneDrive - Danmarks Tekniske Universitet\Skrivebord\Rita's Stuff\l'X\1 2 CSE201\eigen-3.4.0\eigen-3.4.0"
#INCLUDEPATH += "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_test_matrix/eigen"
#INCLUDEPATH += "/Users/alanpicucci/Desktop/Programming/Includes/eigen-3.4.0"



