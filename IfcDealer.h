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

    void Create_IfcSpace_entities();
}

#endif // IFCDEALER_H
