#include <QApplication>
#include "subim_main.h"
#include <iostream>
#include "viewer.h"
#include "IfcDealer.h"

float x_in, y_in, z_in;
int sz_x, sz_y, sz_z;

int main(int argc, char *argv[])
{

    // RD-Coordinates
    int xmin, xmax, ymin, ymax;
    // height [-50, 106.5]
    float zmin, zmax;

    // range to read in GeoTOP extract
    xmin = 85100; xmax = 85280;
    ymin = 446738; ymax = 446982;
    zmin = -37.5; zmax = -36.0;

    // Read command lines arguments.
    QApplication application(argc,argv);

    SuBIM_main my_SuBIM;
    my_SuBIM.Get_GeoTOP_voxels( xmin, xmax, ymin, ymax, zmin, zmax );


    x_in = 0.0;
    y_in = 0.0;
//    x_in = my_SuBIM.x0;
//    y_in = my_SuBIM.y0;
    z_in = my_SuBIM.z0;

    std::cout << "x0: " << my_SuBIM.x0 << std::endl;
    std::cout << "y0: " << my_SuBIM.y0 << std::endl;
    std::cout << "z0: " << my_SuBIM.z0 << std::endl;

    sz_x = my_SuBIM.sx;
    sz_y = my_SuBIM.sy;
    sz_z = my_SuBIM.sz;

    // Instantiate the viewer.
    Viewer viewer;
    viewer.setWindowTitle("VoxelViewer");

    // Make the viewer window visible on screen.
    viewer.show();

    // Generates IFC file
    IfcDealer::Create_IfcSpace_entities();

    // Run main loop.
    return application.exec();

//    QApplication a(argc, argv);
//    SuBIM_main w;
//    w.show();

//    return a.exec();
//    return 0;
}
