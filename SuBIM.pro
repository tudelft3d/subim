#-------------------------------------------------
#
# Project created by QtCreator 2017-01-27T20:47:26
#
#-------------------------------------------------

QT       += core gui xml opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuBIM
TEMPLATE = app

SOURCES += main.cpp\
        subim_main.cpp \
    viewer.cpp

HEADERS  += subim_main.h \
    viewer.h

FORMS    += subim_main.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/netcdf-cxx4-4.3.0/build/cxx4/.libs/release/ -lnetcdf_c++4
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/netcdf-cxx4-4.3.0/build/cxx4/.libs/debug/ -lnetcdf_c++4
else:unix: LIBS += -L$$PWD/lib/netcdf-cxx4-4.3.0/build/cxx4/.libs/ -lnetcdf_c++4

INCLUDEPATH += $$PWD/lib/netcdf-cxx4-4.3.0/build/cxx4/.libs
INCLUDEPATH += $$PWD/lib/netcdf-cxx4-4.3.0/cxx4
DEPENDPATH += $$PWD/lib/netcdf-cxx4-4.3.0/build/cxx4/.libs

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/netcdf-cxx4-4.3.0/build/cxx4/.libs/release/libnetcdf_c++4.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/netcdf-cxx4-4.3.0/build/cxx4/.libs/debug/libnetcdf_c++4.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/netcdf-cxx4-4.3.0/build/cxx4/.libs/release/netcdf_c++4.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/netcdf-cxx4-4.3.0/build/cxx4/.libs/debug/netcdf_c++4.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/netcdf-cxx4-4.3.0/build/cxx4/.libs/libnetcdf_c++4.a



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/libQGLViewer-2.6.4/QGLViewer/release/ -lQGLViewer-qt5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/libQGLViewer-2.6.4/QGLViewer/debug/ -lQGLViewer-qt5
else:unix: LIBS += -L$$PWD/lib/libQGLViewer-2.6.4/QGLViewer/ -lQGLViewer-qt5

INCLUDEPATH += $$PWD/lib/libQGLViewer-2.6.4/QGLViewer
DEPENDPATH += $$PWD/lib/libQGLViewer-2.6.4/QGLViewer

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/libQGLViewer-2.6.4/QGLViewer/release/libQGLViewer-qt5.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/libQGLViewer-2.6.4/QGLViewer/debug/libQGLViewer-qt5.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/libQGLViewer-2.6.4/QGLViewer/release/QGLViewer-qt5.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/libQGLViewer-2.6.4/QGLViewer/debug/QGLViewer-qt5.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/libQGLViewer-2.6.4/QGLViewer/libQGLViewer-qt5.a
