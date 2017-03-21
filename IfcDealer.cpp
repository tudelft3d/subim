#include "IfcDealer.h"

void IfcDealer::Create_IfcSpace_entities()
{
    // The IfcHierarchyHelper is a subclass of the regular IfcFile that provides several
    // convenience functions for working with geometry in IFC files.
    IfcHierarchyHelper file;
    file.header().file_name().name("MyIFC.ifc");

    // Start by adding a wall to the file, initially leaving most attributes blank.
    IfcSchema::IfcWallStandardCase* south_wall = new IfcSchema::IfcWallStandardCase(
        IfcDealer::guid(),          // GlobalId
        0,                          // OwnerHistory
        std::string("South wall"), 	// Name
        IfcDealer::null,            // Description
        IfcDealer::null,            // ObjectType
        0,                          // ObjectPlacement
        0,                          // Representation
        IfcDealer::null             // Tag
    #ifdef USE_IFC4
            , IfcSchema::IfcWallTypeEnum::IfcWallType_STANDARD
    #endif
    );
    file.addBuildingProduct(south_wall);

    // Finally create a file stream for our output and write the IFC file to it.
    std::ofstream f("MyIFC.ifc");
    f << file;
}
