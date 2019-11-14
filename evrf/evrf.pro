#-------------------------------------------------
#
# Project created by QtCreator 2018-10-12T01:42:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = evrf
TEMPLATE = app

# LIBS += -L/home/pi/Downloads/WiringPi-master/wiringPi -lwiringPi
# LIBS += -L/home/pi/fc2/build-evrf-Desktop-Debug -lwiringPi
# LIBS += -L/home/pi/fc/
# LIBS += -lwiringPi


# The following define makes your compiler emit warnings if you use#
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include


SOURCES += main.cpp\
        mainwindow.cpp \
    src/configwindow.cpp \
    src/accessoryscan.cpp \
    src/care.cpp \
    src/endoveinous.cpp \
    src/mainmenu.cpp \
    src/param.cpp \
    src/patientlist.cpp \
    src/phlebology.cpp \
    src/proctology.cpp \
    src/protocol.cpp \
    src/quickuserinfo.cpp \
    src/rfidreader.cpp \
    src/userinfo.cpp \
    src/util.cpp \
    src/wkeyboard.cpp \
    src/dataio.cpp \
    src/run_cr45i.cpp \
    src/run_cr40i.cpp \
    src/run_cr30i.cpp \
    src/run_trancutaneous.cpp \
    src/run_hpr45i.cpp \
    src/run_fistula.cpp \
    src/run.cpp \
    src/database.cpp \
    src/patient.cpp \
    src/treatmentdetail.cpp \
    src/fileio.cpp \
    src/powerqualibration.cpp \
    src/autocheck.cpp

HEADERS  += mainwindow.h \
    include/configwindow.h \
    include/util.h \
    include/accessoryscan.h \
    include/care.h \
    include/config.h \
    include/endoveinous.h \
    include/mainmenu.h \
    include/param.h \
    include/patientlist.h \
    include/phlebology.h \
    include/proctology.h \
    include/protocol.h \
    include/quickuserinfo.h \
    include/rfidreader.h \
    include/userinfo.h \
    include/wkeyboard.h \
    include/wiringPi.h \
    include/dataio.h \
    include/wiringPi.h \
    include/wiringPiSPI.h \
    include/wiringSerial.h \
    include/database.h \
    include/patient.h \
    include/treatmentdetail.h \
    include/fileio.h \
    src/powerqualibration.h \
    src/powerqualibration.h \
    src/autocheck.h

FORMS    += mainwindow.ui \
    src/configwindow.ui \
    src/accessoryscan.ui \
    src/endoveinous.ui \
    src/mainmenu.ui \
    src/patientcreate.ui \
    src/patientlist.ui \
    src/phlebology.ui \
    src/proctology.ui \
    src/protocol.ui \
    src/quickuserinfo.ui \
    src/rfidreader.ui \
    src/transcutaneous.ui \
    src/userinfo.ui \
    src/wkeyboard.ui \
    src/treatmentdetail.ui \
    src/powerqualibration.ui \
    src/autocheck.ui
