#ifndef SUBIM_MAIN_H
#define SUBIM_MAIN_H

#include <QMainWindow>
#include <vector>
#include <cmath>
#include <netcdf>

namespace Ui {
class SuBIM_main;
}

class SuBIM_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit SuBIM_main(QWidget *parent = 0);
    ~SuBIM_main();

    // resulting array of voxel
    int sx, sy, sz, *voxels;

    // starting point for drawing
    float x0, y0, z0;

    // Get corresponding voxels from GeoTOP using RD-Coordinates
    int Get_GeoTOP_voxels(int xmin, int xmax,
                          int ymin, int ymax,
                          int zmin, int zmax);

private:
    Ui::SuBIM_main *ui;
};

#endif // SUBIM_MAIN_H
