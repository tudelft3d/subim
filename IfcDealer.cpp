#include "IfcDealer.h"

void IfcDealer::Create_IfcSpace_entities(Vec3D<double>& init_pos, Vec3D<int>& range, Vec3D<double>& sz)
{
    // The IfcHierarchyHelper is a subclass of the regular IfcFile that provides several
    // convenience functions for working with geometry in IFC files.
    IfcHierarchyHelper file;
    file.header().file_name().name("MyIFC.ifc");

//    // Start by adding a wall to the file, initially leaving most attributes blank.
////    IfcSchema::IfcWallStandardCase* south_wall = new IfcSchema::IfcWallStandardCase(
////        IfcDealer::guid(),          // GlobalId
////        0,                          // OwnerHistory
////        std::string("One_space"), 	// Name
////        IfcDealer::null,            // Description
////        IfcDealer::null,            // ObjectType
////        0,                          // ObjectPlacement
////        0,                          // Representation
////        IfcDealer::null             // Tag
////    #ifdef USE_IFC4
////            , IfcSchema::IfcWallTypeEnum::IfcWallType_STANDARD
////    #endif
////    );

//    IfcSchema::IfcSpace* south_wall = new IfcSchema::IfcSpace(
//        IfcDealer::guid(),                      // GlobalId
//        0,                                      // OwnerHistory
//        std::string("One_space"),               // Name
//        IfcDealer::null,                        // Description
//        IfcDealer::null,                        // ObjectType
//        0,                                      // ObjectPlacement
//        0,                                      // Representation
//        std::string("A long name!"),            // LongName
//        IfcSchema::IfcElementCompositionEnum::IfcElementComposition_ELEMENT,            // CompositionType [Complex (aggregation of), ELEMENT (undivided element) or PARTIAL (subelement)]
//        IfcSchema::IfcInternalOrExternalEnum::IfcInternalOrExternal_EXTERNAL,           // InteriorOrExteriorSpace [Internal (fully bounded physically), External (Not or partly bounded), NotDefined]
//        double(0.0)                             // ElevationWithFlooring (Level of flooring of this space)
//    #ifdef USE_IFC4
//            , IfcSchema::IfcWallTypeEnum::IfcWallType_STANDARD
//    #endif
//    );
//    file.addBuildingProduct(south_wall);

//    // By adding a wall, a hierarchy has been automatically created that consists of the following
//    // structure: IfcProject > IfcSite > IfcBuilding > IfcBuildingStorey > IfcWall

//    // Lateron changing the name of the IfcProject can be done by obtaining a reference to the
//    // project, which has been created automatically.
//    file.getSingle<IfcSchema::IfcProject>()->setName("MyIFC");

//    // An IfcOwnerHistory has been initialized as well, which should be assigned to the wall.
//    south_wall->setOwnerHistory(file.getSingle<IfcSchema::IfcOwnerHistory>());

//    // The wall will be shaped as a box, with the dimensions specified in millimeters. The resulting
//    // product definition will consist of both a body representation as well as an axis representation
//    // that runs over the centerline of the box in the X-axis.
////    IfcSchema::IfcProductDefinitionShape* south_wall_shape = file.addAxisBox(10000, 360, 3000);
//    IfcSchema::IfcProductDefinitionShape* south_wall_shape = file.addBox(100000, 100000, 500);

//    // Obtain a reference to the placement of the IfcBuildingStorey in order to create a hierarchy
//    // of placements for the products
//    IfcSchema::IfcObjectPlacement* storey_placement = file.getSingle<IfcSchema::IfcBuildingStorey>()->ObjectPlacement();

//    // The shape has to be assigned to the representation of the wall and is placed at the origin
//    // of the coordinate system.
//    south_wall->setRepresentation(south_wall_shape);
//    south_wall->setObjectPlacement(file.addLocalPlacement(storey_placement));


    file.addSite();
    file.getSingle<IfcSchema::IfcProject>()->setName("MyIfcVoxels");
    IfcSchema::IfcObjectPlacement* site_placement = file.getSingle<IfcSchema::IfcSite>()->ObjectPlacement();

    // Get the initial position of the ref IfcSpace
    float x = init_pos.x,
          y = init_pos.y,
          z = init_pos.z;

    for (int i=0; i<range.x; ++i)
    {
        for (int j=0; j<range.y; ++j)
        {
            for (int k=0; k<range.z; ++k)
            {
                Vec3D<double> pos(x,y,z);
                addIfcSpace_box(file, site_placement, pos, sz);
                z += sz.z;
//                std::cout << "(" << x << ", " << y << ", " << z  << ")";
            }
//            std::cout << std::endl;
            y += sz.y;
            z = init_pos.z;
        }
//        std::cout << std::endl;
        x += sz.x;
        y = init_pos.y;
    }


    // Finally create a file stream for our output and write the IFC file to it.
    std::ofstream f("../Outputs/voxels.ifc");
    f << file;
}

void IfcDealer::addIfcSpace_box(IfcHierarchyHelper& file, IfcSchema::IfcObjectPlacement* ref_placement, IfcDealer::Vec3D<double>& pos,
                                IfcDealer::Vec3D<double>& sz, std::string name, std::string description, int number)
{
    std::vector<XY> points;
    points.push_back(XY(   0,    0));
    points.push_back(XY(sz.x,    0));
    points.push_back(XY(sz.x, sz.y));
    points.push_back(XY(   0, sz.y));


    IfcSchema::IfcSpace* myspace = new IfcSchema::IfcSpace(
        IfcDealer::guid(),                      // GlobalId
        file.getSingle<IfcSchema::IfcOwnerHistory>(),                                   // OwnerHistory
        std::string("space ") + std::to_string(number),                                 // Name
        description,                            // Description
        IfcDealer::null,                        // ObjectType
        file.addLocalPlacement(ref_placement, pos.x, pos.y, pos.z),                     // ObjectPlacement
        file.addExtrudedPolyline(points, sz.z),                                         // Representation
        name,                                   // LongName
        IfcSchema::IfcElementCompositionEnum::IfcElementComposition_ELEMENT,            // CompositionType [Complex (aggregation of), ELEMENT (undivided element) or PARTIAL (subelement)]
        IfcSchema::IfcInternalOrExternalEnum::IfcInternalOrExternal_EXTERNAL,           // InteriorOrExteriorSpace [Internal (fully bounded physically), External (Not or partly bounded), NotDefined]
        double(0.0)                             // ElevationWithFlooring (Level of flooring of this space)
    #ifdef USE_IFC4
            , IfcSchema::IfcWallTypeEnum::IfcWallType_STANDARD
    #endif
    );

    file.addBuildingProduct(myspace);
}

