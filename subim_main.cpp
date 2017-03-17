#include "subim_main.h"
#include "ui_subim_main.h"

using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

// Return this in event of a problem.
static const int NC_ERR = 2;


SuBIM_main::SuBIM_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SuBIM_main)
{
    ui->setupUi(this);
}

SuBIM_main::~SuBIM_main()
{
    delete ui;
}

int SuBIM_main::Get_GeoTOP_voxels(int xmin, int xmax,
                                  int ymin, int ymax,
                                  int zmin, int zmax)
{
    try
    {
        // Open the file for read access
        NcFile dataFile("http://www.dinodata.nl/opendap/GeoTOP/geotop.nc", NcFile::read);
        cout << "Well it seems I got something here... " << endl;
        cout << "#Dimensions: " << dataFile.getDimCount() << endl;
        cout << "#Attributes: " << dataFile.getAttCount() << endl;
        cout << "#Variables: " << dataFile.getVarCount() << endl;
        cout << "#Types: " << dataFile.getTypeCount() << endl;

        // Retrieve the variable named "something"
        NcVar data_var = dataFile.getVar("lithok");
        if(data_var.isNull())
            return NC_ERR;
        cout << "\n#Dimensions of selected variable: " << data_var.getDimCount() << endl;

        // Handle the proper array size and location to extract
        int X, Nx;
        // 13600 = xmin of the Netherlands in RD-Coordinates
        X = ceil( (xmin - 13600)/100 );
        Nx = ceil( (xmax - xmin)/100 ) + 1;

        int Y, Ny;
        // 358000 = ymin of the Netherlands in RD-Coordinates
        Y = ceil( (ymin - 358000)/100 );
        Ny = ceil( (ymax - ymin)/100 ) + 1;

        int Z, Nz;
        // -50 = zmin of the GeoTOP data
        Z = fabs(zmin + 50.0)*2;
        Nz = fabs(zmax - zmin)*2 + 1;


        int *res = new int[Nx*Ny*Nz];
        cout << "\nGuess I got my array ready: \n";
        cout << " X = " << X << " & Nx = " << Nx << "\n" ;
        cout << " Y = " << Y << " & Ny = " << Ny << "\n" ;
        cout << " Z = " << Z << " & Nz = " << Nz << endl;

        // 3D Vector specifying the index of the first data value to be read in the corresponding dimension.
        std::vector<size_t> start(3);

        start[0] = X;
        start[1] = Y;
        start[2] = Z;
//        start[3] = 0;

        // Declare count Vector specifying the edge lengths along each dimension of
        // the block of data values to be read.
        std::vector<size_t> count(3);

        count[0] = Nx;
        count[1] = Ny;
        count[2] = Nz;
//        count[3] = 5;

        data_var.getVar(start, count, res);

        for (int i=0; i<Nx; i++)
        {
            for (int j=0; j<Ny; j++)
            {
                for (int k=0; k<Nz; k++)
                    cout << res[(i*Ny*Nz) + (j*Nz) + k] << " (" << (i*Ny*Nz) + (j*Nz) + k <<  ") \t";
                cout << endl;
            }
            cout << endl;
        }

        cout << "\nSeems like I made it " << endl;

        voxels = res;
        sx = Nx; sy = Ny; sz = Nz;
        x0 = (X*100) + 13600;
        y0 = (Y*100) + 358000;
        z0 = (Z/2) - 50;

        return 0;
    }

    catch(NcException& e)
    {
        e.what();
        cout<<"FAILURE*************************************"<<endl;
        return NC_ERR;
    }
}

