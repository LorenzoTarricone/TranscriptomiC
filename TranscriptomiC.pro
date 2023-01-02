QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bioprocesswindow.cpp \
    colocalizationwindow.cpp \
    create_fake_colocalization_matrix.cpp \
    filedata.cpp \
    genename.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    secondwindow.cpp

HEADERS += \
    bioprocesswindow.h \
    colocalizationwindow.h \
    create_fake_colocalization_matrix.h \
    filedata.h \
    genename.h \
    mainwindow.h \
    qcustomplot.h \
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

win32:INCLUDEPATH += "/Users/adrianduesselberg/CSE201Pro/eigen-3.4.0" # on Adrians MAC
macx:INCLUDEPATH += "/Users/adrianduesselberg/CSE201Pro/eigen-3.4.0" # on Adrians MAC


#INCLUDEPATH += "/Users/ninapeuker/Desktop/General_Engineering/5th_semester_2022:23_Ecole/CSE201_Object_Oriented_Programming_in_C++/Transcriptomic++/transcriptomics_test_matrix/eigen"


