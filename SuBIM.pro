#-------------------------------------------------
#
# Project created by QtCreator 2017-01-27T20:47:26
#
#-------------------------------------------------

QT     += core gui xml opengl
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuBIM
TEMPLATE = app

SOURCES += main.cpp\
           subim_main.cpp \
           viewer.cpp \
    IfcDealer.cpp

HEADERS  += subim_main.h \
            viewer.h \
    IfcDealer.h

FORMS    += subim_main.ui


# Importing the NetCDF-C++ library (version 4-4.3.0)
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


# Importing the QGLViewer library (version 2.6.4)
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



# Importing the IfcOpenshell library
packagesExist( IfcParse & IfcGeom )
{
    message( "Found IFC library!" )
    unix|win32: LIBS += -L/usr/local/lib -lIfcParse -lIfcGeom \
                        # All the Open Cascade libraries .... -_-!
                        -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep \
                        -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR \
                        -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet \
                        -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKOpenGl -lTKMeshVS \
                        -lTKNIS -lTKVoxel -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin \
                        -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema \
                        -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj \
                        -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase \
                        -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF \
                        -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
    unix|win32: LIBS += -L/usr/lib/x86_64-linux-gnu -licuuc
    INCLUDEPATH += /usr/local/include/oce
    INCLUDEPATH += /usr/local/include
    DEFINES += "BOOST_OPTIONAL_USE_OLD_DEFINITION_OF_NONE"

    DEFINES += HANDLES_IFC
}

