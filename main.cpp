#include "subim_main.h"
#include <QApplication>
#include <iostream>
#include <vector>
#include <netcdf>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

// Return this in event of a problem.
static const int NC_ERR = 2;

static const int X = 10,
                 Y = 10,
                 Z = 5;

int main(/*int argc, char *argv[]*/)
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

        // Essential for determining the dimension. Calling of getSize becomes possible
        NcDim dim;

        // Retrieve the variable named "u", "v", and "w"
        NcVar data_u=dataFile.getVar("strat");
        if(data_u.isNull()) return NC_ERR;

        //  Array Iterators
        int i, j, k;
        int dataIn[3][4][4];

//        int NX = 3,
//            NY = 4,
//            NZ = 4;

//        int*** dataIn = new int**[NX]();
//        for(i = 0; i != NX; ++i)
//        {
//            dataIn[i] = new int*[NY]();

//            for(j = 0; j != NY; ++j)
//            {
//                dataIn[i][j] = new int[NZ]();
//            }
//        }

        dataIn[0][0][0] = 0;
        cout << "Guess I got my array ready " << dataIn[0][0][0] << endl;

        // Declare start Vector specifying the index in the variable where the first
        // of the data values will be read.
        std::vector<size_t> start(3);

        start[0] = 715;
        start[1] = 887;
        start[2] = 47;
//        start[3] = 0;

        // Declare count Vector specifying the edge lengths along each dimension of
        // the block of data values to be read.
        std::vector<size_t> count(3);

        count[0] = 2;
        count[1] = 3;
        count[2] = 3;
//        count[3] = 5;

        data_u.getVar(start, count, dataIn);

        for (i=0; i<2; i++)
        {
            for (j=0; j<3; j++)
            {
//                for (k=0; k<6; k++)
                    cout << dataIn[i][j][0] << "\t";
            }
            cout << endl;
        }

        cout << "Seems like I made it" << endl;







////        int X = 2645,
////            Y = 2615,
////            Z = 312;

//        int ***dataIn;

//        // Allocate memory
//        dataIn = new int**[X];
//        for (int i = 0; i < X; ++i)
//        {
//            dataIn[i] = new int*[Y];

//            for (int j = 0; j < Y; ++j)
//              dataIn[i][j] = new int[Z];
//        }

//        // This is the array we will read.
////        int dataIn[X][Y][Z];

////        vector< vector < vector < int > > > data_in_file;

////        data_in_file.resize( X );
////        for(uint i=0; i<X; i++)
////        {
////            data_in_file[i].resize(Y);
////            for(uint j=0; j<Y; j++)
////            {
////                data_in_file[i][j].resize(Z);
////            }
////        }


//        cout << "*** I got my array" << endl;

//        // Open the file for read access
//        NcFile dataFile("http://www.dinodata.nl/opendap/GeoTOP/geotop.nc", NcFile::read);
//        cout << "Well it seems I got something here... " << endl;
//        cout << "#Dimensions: " << dataFile.getDimCount() << endl;
//        cout << "#Attributes: " << dataFile.getAttCount() << endl;
//        cout << "#Variables: " << dataFile.getVarCount() << endl;
//        cout << "#Types: " << dataFile.getTypeCount() << endl;

//        vector<size_t> start;
//        vector<size_t> count;
//        int res[5][5][5];

//        start.push_back(0);
//        start.push_back(0);
//        start.push_back(0);
//        count.push_back(4);
//        count.push_back(4);
//        count.push_back(4);

//        // Retrieve the variable named "data"
//        NcVar data = dataFile.getVar("strat");
//        if(data.isNull())
//            return NC_ERR;

//        cout << "STILL IN! " << data.getDimCount() << endl;

//        for( int i = 0; i < count[0]; i++ )
//        {
//            start[0] = i;
//            data.getVar(start, count, res);
//        }
////        data.getVar(dataIn);

//        cout << "We cool" << endl;
//        for( int i = 0; i < count[0]; i++ )
//            cout << res[i] << " ";

////        // Check the values.
////        for (int i = 0; i < NX; i++)
////          for (int j = 0; j < NY; j++)
////         if (dataIn[i][j] != i * NY + j)
////           return NC_ERR;

////        for (int i = 85100; i < 85100+X; i++)
////        {
////            for (int j = 44638; j < 44638+Y; j++)
////            {
////                cout << dataIn[i][j][0] << " ";
////                for (int k = 0; k < Z; k++)
////                {

////                }
////            }

////            cout << endl;
////        }


//        // The netCDF file is automatically closed by the NcFile destructor
//        //cout << "*** SUCCESS reading example file simple_xy.nc!" << endl;

        return 0;
    }

    catch(NcException& e)
    {
        e.what();
        cout<<"FAILURE*************************************"<<endl;
        return NC_ERR;
    }

//    QApplication a(argc, argv);
//    SuBIM_main w;
//    w.show();

//    return a.exec();
//    return 0;
}
