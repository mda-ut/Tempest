#-------------------------------------------------
#
# Project created by QtCreator 2016-02-08T22:44:39
#
#-------------------------------------------------

LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_imgcodecs

CONFIG += c++11
QT += widgets testlib opengl

#FOR THE FOLLOWING, CHANGE TO WHERE EVER YOUR IRRLICHT FILES ARE
#IF YOU GET ALOT OF QT ERRORS, YOU WILL NEED THE MODIFIED IRRLICHT FILES THAT I HAVE
LIBS += -L/usr/lib/x86_64-linux-gnu/ -L/home/james/Downloads/irrlicht-1.8.3/lib/Linux/ -lIrrlicht -lGLU -lGL -lXrandr -lXext -lX11
INCLUDEPATH += /home/james/Downloads/irrlicht-1.8.3/lib/Linux
unix:!macx: PRE_TARGETDEPS += $$PWD/../../Downloads/irrlicht-1.8.3/lib/Linux/libIrrlicht.a

SOURCES += main.cpp \
    Objects/Buoy.cpp \
    Objects/SimObject.cpp \
    DataStorage.cpp \
    InputHandler.cpp \
    Logger.cpp \
    Sim.cpp

HEADERS += \
    Objects/Buoy.h \
    Objects/SimObject.h \
    DataStorage.h \
    InputHandler.h \
    Logger.h \
    Sim.h
