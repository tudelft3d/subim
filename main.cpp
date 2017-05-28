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
    zmin = -15.5; zmax = 0.0;

    // Read command lines arguments.
    QApplication application(argc,argv);

    SuBIM_main my_SuBIM, my_SuBIM2;
    my_SuBIM.Get_GeoTOP_voxels("strat", xmin, xmax, ymin, ymax, zmin, zmax );
    my_SuBIM2.Get_GeoTOP_voxels("lithok", xmin, xmax, ymin, ymax, zmin, zmax );


    // Initial position of the first voxel
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

    // Collect the values of the voxel as strings to add them to the IfcSpace attributes
    std::string *vox_values = new std::string [sz_x*sz_y*sz_z];
    for (int i=0; i<sz_x; i++)
    {
        for (int j=0; j<sz_y; j++)
        {
            for (int k=0; k<sz_z; k++)
               vox_values[(i*sz_y*sz_z) + (j*sz_z) + k] = "strat = " + std::to_string(my_SuBIM.voxels[(i*sz_y*sz_z) + (j*sz_z) + k]) +
                                                    "; lithok = " +  std::to_string(my_SuBIM2.voxels[(i*sz_y*sz_z) + (j*sz_z) + k]);
        }
    }


    // -------------------------------------- Generates IFC files //
    IfcDealer::Vec3D<double> init_pos(x_in, y_in, z_in);
    IfcDealer::Vec3D<int> range(sz_x, sz_y, sz_z);
    IfcDealer::Vec3D<double> sz(100000, 100000, 500);
    IfcDealer::Create_IfcSpace_entities(init_pos, range, sz, vox_values);

    // ------------------------------------- OpenGL voxel viewer //

    // Instantiate the viewer.
    Viewer viewer;
    viewer.setWindowTitle("VoxelViewer");
    // Make the viewer window visible on screen.
    viewer.show();
    // Run main loop.
    return application.exec();

    // ------------------------------------- SuBIM UI //

//    QApplication a(argc, argv);
//    SuBIM_main w;
//    w.show();

//    return a.exec();


//    return 0;
}
