#ifndef IFCDEALER_H
#define IFCDEALER_H

#include <string>
#include <iostream>
#include <fstream>

//#include <TColgp_Array2OfPnt.hxx>
//#include <TColgp_Array1OfPnt.hxx>
//#include <TColStd_Array1OfReal.hxx>
//#include <TColStd_Array1OfInteger.hxx>

//#include <Geom_BSplineSurface.hxx>
//#include <BRepBuilderAPI_MakeFace.hxx>

//#include <Standard_Version.hxx>

#ifdef USE_IFC4
#include "../ifcparse/Ifc4.h"
#else
#include "ifcparse/Ifc2x3.h"
#endif

#include "ifcparse/IfcUtil.h"
#include "ifcparse/IfcHierarchyHelper.h"
#include "ifcgeom/IfcGeom.h"

namespace IfcDealer
{
    // Some convenience typedefs and definitions.
    typedef IfcParse::IfcGlobalId guid;
    typedef std::pair<double, double> XY;
    boost::none_t const null = boost::none;
    template<class whatever> struct Vec3D
    {
        double x, y, z;
        // Constructors
        Vec3D(): x(0), y(0), z(0) {}
        Vec3D(whatever vx, whatever vy, whatever vz):
            x(vx), y(vy), z(vz) {}
    };

    void Create_IfcSpace_entities(Vec3D<double>&, Vec3D<int>&, Vec3D<double>&);
    static Vec3D<double> pos_init = Vec3D<double>(0,0,0);
    static Vec3D<double> sz_init = Vec3D<double>(100000, 100000, 500);
    void addIfcSpace_box(IfcHierarchyHelper&, IfcSchema::IfcObjectPlacement* ref_placement = 0,
                         Vec3D<double>& pos = pos_init, Vec3D<double>& sz = sz_init, std::string name = std::string("voxel"),
                         std::string description = std::string(""), int number = 0);
}

#endif // IFCDEALER_H
