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

    // By adding a wall, a hierarchy has been automatically created that consists of the following
    // structure: IfcProject > IfcSite > IfcBuilding > IfcBuildingStorey > IfcWall

    // Lateron changing the name of the IfcProject can be done by obtaining a reference to the
    // project, which has been created automatically.
    file.getSingle<IfcSchema::IfcProject>()->setName("MyIFC");

    // An IfcOwnerHistory has been initialized as well, which should be assigned to the wall.
    south_wall->setOwnerHistory(file.getSingle<IfcSchema::IfcOwnerHistory>());

    // The wall will be shaped as a box, with the dimensions specified in millimeters. The resulting
    // product definition will consist of both a body representation as well as an axis representation
    // that runs over the centerline of the box in the X-axis.
    IfcSchema::IfcProductDefinitionShape* south_wall_shape = file.addAxisBox(10000, 360, 3000);

    // Obtain a reference to the placement of the IfcBuildingStorey in order to create a hierarchy
    // of placements for the products
    IfcSchema::IfcObjectPlacement* storey_placement = file.getSingle<IfcSchema::IfcBuildingStorey>()->ObjectPlacement();

    // The shape has to be assigned to the representation of the wall and is placed at the origin
    // of the coordinate system.
    south_wall->setRepresentation(south_wall_shape);
    south_wall->setObjectPlacement(file.addLocalPlacement(storey_placement));

    // Finally create a file stream for our output and write the IFC file to it.
    std::ofstream f("MyIFC2.ifc");
    f << file;
}


static int x = 0;

void create_testcase(IfcHierarchyHelper& file, IfcSchema::IfcFace* face, const std::string& name)
{
    IfcSchema::IfcFace::list::ptr faces(new IfcSchema::IfcFace::list);
    faces->push(face);
    IfcSchema::IfcOpenShell* shell = new IfcSchema::IfcOpenShell(faces);

    IfcSchema::IfcConnectedFaceSet::list::ptr shells(new IfcSchema::IfcConnectedFaceSet::list);
    shells->push(shell);
    IfcSchema::IfcFaceBasedSurfaceModel* model = new IfcSchema::IfcFaceBasedSurfaceModel(shells);

    IfcSchema::IfcBuildingElementProxy* product = new IfcSchema::IfcBuildingElementProxy(
        IfcDealer::guid(), 0, name, IfcDealer::null, IfcDealer::null, 0, 0, IfcDealer::null, IfcDealer::null);

    file.addBuildingProduct(product);
    product->setOwnerHistory(file.getSingle<IfcSchema::IfcOwnerHistory>());

    product->setObjectPlacement(file.addLocalPlacement(0, 1000 * x++, 0));

    IfcSchema::IfcRepresentation::list::ptr reps (new IfcSchema::IfcRepresentation::list);
    IfcSchema::IfcRepresentationItem::list::ptr items (new IfcSchema::IfcRepresentationItem::list);

    items->push(model);
    IfcSchema::IfcShapeRepresentation* rep = new IfcSchema::IfcShapeRepresentation(
        file.getRepresentationContext("Model"), std::string("Body"), std::string("SurfaceModel"), items);
    reps->push(rep);

    IfcSchema::IfcProductDefinitionShape* shape = new IfcSchema::IfcProductDefinitionShape(0, 0, reps);
    file.addEntity(shape);

    // Obtain a reference to the placement of the IfcBuildingStorey in order to create a hierarchy
    // of placements for the products
    IfcSchema::IfcObjectPlacement* storey_placement = file.getSingle<IfcSchema::IfcBuildingStorey>()->ObjectPlacement();

    product->setRepresentation(shape);
    product->setObjectPlacement(file.addLocalPlacement(storey_placement));
}

void test_faces()
{
    IfcHierarchyHelper file;

    {
        IfcSchema::IfcCartesianPoint::list::ptr points (new IfcSchema::IfcCartesianPoint::list);
        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-400, -400, 0));
        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+400, -400, 0));
        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+400, +400, 0));
        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-400, +400, 0));
        IfcSchema::IfcPolyLoop* loop = new IfcSchema::IfcPolyLoop(points);
        IfcSchema::IfcFaceOuterBound* bound = new IfcSchema::IfcFaceOuterBound(loop, true);

        IfcSchema::IfcFaceBound::list::ptr bounds (new IfcSchema::IfcFaceBound::list);
        bounds->push(bound);
        IfcSchema::IfcFace* face = new IfcSchema::IfcFace(bounds);
        create_testcase(file, face, "polyloop");
    }
//    {
//        IfcSchema::IfcCartesianPoint* point1 = file.addTriplet<IfcSchema::IfcCartesianPoint>(+400, 0., 0.);
//        IfcSchema::IfcCartesianPoint* point2 = file.addTriplet<IfcSchema::IfcCartesianPoint>(-400, 0., 0.);
//        IfcSchema::IfcVertexPoint* vertex1 = new IfcSchema::IfcVertexPoint(point1);
//        IfcSchema::IfcVertexPoint* vertex2 = new IfcSchema::IfcVertexPoint(point2);
//        IfcSchema::IfcCircle* circle = new IfcSchema::IfcCircle(file.addPlacement2d(), 400.);
//        IfcSchema::IfcEdgeCurve* edge1 = new IfcSchema::IfcEdgeCurve(vertex1, vertex2, circle, true);
//        IfcSchema::IfcEdgeCurve* edge2 = new IfcSchema::IfcEdgeCurve(vertex2, vertex1, circle, true);
//        IfcSchema::IfcOrientedEdge* oriented_edge1 = new IfcSchema::IfcOrientedEdge(edge1, true);
//        IfcSchema::IfcOrientedEdge* oriented_edge2 = new IfcSchema::IfcOrientedEdge(edge2, true);
//        IfcSchema::IfcOrientedEdge::list::ptr edges(new IfcSchema::IfcOrientedEdge::list);
//        edges->push(oriented_edge1);
//        edges->push(oriented_edge2);
//        IfcSchema::IfcEdgeLoop* loop = new IfcSchema::IfcEdgeLoop(edges);
//        IfcSchema::IfcFaceOuterBound* bound = new IfcSchema::IfcFaceOuterBound(loop, true);

//        IfcSchema::IfcFaceBound::list::ptr bounds (new IfcSchema::IfcFaceBound::list);
//        bounds->push(bound);
//        IfcSchema::IfcFace* face = new IfcSchema::IfcFace(bounds);
//        create_testcase(file, face, "circle");
//    }
//    {
//        IfcSchema::IfcCartesianPoint::list::ptr points (new IfcSchema::IfcCartesianPoint::list);
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-400, -400, 0));
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+400, -400, 0));
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+400, +400, 0));
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-400, +400, 0));
//        IfcSchema::IfcPolyLoop* loop = new IfcSchema::IfcPolyLoop(points);
//        IfcSchema::IfcFaceOuterBound* outer_bound = new IfcSchema::IfcFaceOuterBound(loop, true);

//        IfcSchema::IfcCartesianPoint::list::ptr points2 (new IfcSchema::IfcCartesianPoint::list);
//        points2->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-300, -300, 0));
//        points2->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-100, -300, 0));
//        points2->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-100, +300, 0));
//        points2->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-300, +300, 0));
//        IfcSchema::IfcPolyLoop* loop2 = new IfcSchema::IfcPolyLoop(points2);
//        IfcSchema::IfcFaceBound* inner_bound1 = new IfcSchema::IfcFaceBound(loop2, false);

//        IfcSchema::IfcCartesianPoint::list::ptr points3 (new IfcSchema::IfcCartesianPoint::list);
//        points3->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+100, +300, 0));
//        points3->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+300, +300, 0));
//        points3->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+300, -300, 0));
//        points3->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+100, -300, 0));
//        IfcSchema::IfcPolyLoop* loop3 = new IfcSchema::IfcPolyLoop(points3);
//        IfcSchema::IfcFaceBound* inner_bound2 = new IfcSchema::IfcFaceBound(loop3, true);

//        IfcSchema::IfcFaceBound::list::ptr bounds (new IfcSchema::IfcFaceBound::list);
//        bounds->push(inner_bound1);
//        bounds->push(outer_bound);
//        bounds->push(inner_bound2);
//        IfcSchema::IfcFace* face = new IfcSchema::IfcFace(bounds);
//        create_testcase(file, face, "polyloop with holes");
//    }
//    {
//        IfcSchema::IfcCartesianPoint::list::ptr points (new IfcSchema::IfcCartesianPoint::list);
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-400, -400, 0));
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-100, -400, 0));
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-100, +400, 0));
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-400, +400, 0));
//        IfcSchema::IfcPolyLoop* loop = new IfcSchema::IfcPolyLoop(points);
//        IfcSchema::IfcFaceOuterBound* bound1 = new IfcSchema::IfcFaceOuterBound(loop, true);

//        IfcSchema::IfcCartesianPoint::list::ptr points2 (new IfcSchema::IfcCartesianPoint::list);
//        points2->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+100, +400, 0));
//        points2->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+400, +400, 0));
//        points2->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+400, -400, 0));
//        points2->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+100, -400, 0));
//        IfcSchema::IfcPolyLoop* loop2 = new IfcSchema::IfcPolyLoop(points2);
//        IfcSchema::IfcFaceOuterBound* bound2 = new IfcSchema::IfcFaceOuterBound(loop2, false);

//        IfcSchema::IfcFaceBound::list::ptr bounds (new IfcSchema::IfcFaceBound::list);
//        bounds->push(bound1);
//        bounds->push(bound2);
//        IfcSchema::IfcFace* face = new IfcSchema::IfcFace(bounds);
//        create_testcase(file, face, "multiple outer boundaries (invalid)");
//    }
//    {
//        IfcSchema::IfcCartesianPoint::list::ptr points (new IfcSchema::IfcCartesianPoint::list);
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-400, -400, 1e-6));
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+400, -400, 0));
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(+400, +400, 0));
//        points->push(file.addTriplet<IfcSchema::IfcCartesianPoint>(-400, +400, 0));
//        IfcSchema::IfcPolyLoop* loop = new IfcSchema::IfcPolyLoop(points);
//        IfcSchema::IfcFaceOuterBound* bound = new IfcSchema::IfcFaceOuterBound(loop, true);

//        IfcSchema::IfcFaceBound::list::ptr bounds (new IfcSchema::IfcFaceBound::list);
//        bounds->push(bound);
//        IfcSchema::IfcFace* face = new IfcSchema::IfcFace(bounds);
//        create_testcase(file, face, "imprecise polyloop");
//    }
//    {
//        IfcSchema::IfcCartesianPoint* point1 = file.addTriplet<IfcSchema::IfcCartesianPoint>(+400, 0., 0.);
//        IfcSchema::IfcCartesianPoint* point2 = file.addTriplet<IfcSchema::IfcCartesianPoint>(-400, 0., 0.);
//        IfcSchema::IfcVertexPoint* vertex1 = new IfcSchema::IfcVertexPoint(point1);
//        IfcSchema::IfcVertexPoint* vertex2 = new IfcSchema::IfcVertexPoint(point2);
//        IfcSchema::IfcCircle* circle = new IfcSchema::IfcCircle(file.addPlacement2d(), 400.);
//        IfcSchema::IfcEdgeCurve* edge1 = new IfcSchema::IfcEdgeCurve(vertex1, vertex2, circle, true);
//        IfcSchema::IfcEdgeCurve* edge2 = new IfcSchema::IfcEdgeCurve(vertex2, vertex1, circle, true);
//        IfcSchema::IfcOrientedEdge* oriented_edge1 = new IfcSchema::IfcOrientedEdge(edge1, true);
//        IfcSchema::IfcOrientedEdge* oriented_edge2 = new IfcSchema::IfcOrientedEdge(edge2, true);
//        IfcSchema::IfcOrientedEdge::list::ptr edges(new IfcSchema::IfcOrientedEdge::list);
//        edges->push(oriented_edge1);
//        edges->push(oriented_edge2);
//        IfcSchema::IfcEdgeLoop* loop = new IfcSchema::IfcEdgeLoop(edges);
//        IfcSchema::IfcFaceOuterBound* bound = new IfcSchema::IfcFaceOuterBound(loop, true);

//        IfcSchema::IfcFaceBound::list::ptr bounds (new IfcSchema::IfcFaceBound::list);
//        bounds->push(bound);

//        IfcSchema::IfcCartesianPoint::list::ptr trim1(new IfcSchema::IfcCartesianPoint::list);
//        IfcSchema::IfcCartesianPoint::list::ptr trim2(new IfcSchema::IfcCartesianPoint::list);
//        trim1->push(point1);
//        trim2->push(point2);
//        IfcSchema::IfcTrimmedCurve* trimmed_curve = new IfcSchema::IfcTrimmedCurve(circle, trim1->generalize(), trim2->generalize(), true, IfcSchema::IfcTrimmingPreference::IfcTrimmingPreference_CARTESIAN);
//        IfcSchema::IfcArbitraryOpenProfileDef* profile = new IfcSchema::IfcArbitraryOpenProfileDef(IfcSchema::IfcProfileTypeEnum::IfcProfileType_CURVE, boost::none, trimmed_curve);
//        IfcSchema::IfcAxis1Placement* place = new IfcSchema::IfcAxis1Placement(file.addTriplet<IfcSchema::IfcCartesianPoint>(0., 0., 0.), file.addTriplet<IfcSchema::IfcDirection>(1., 0., 0.));
//        IfcSchema::IfcSurfaceOfRevolution* surface = new IfcSchema::IfcSurfaceOfRevolution(profile, file.addPlacement3d(), place);

//        IfcSchema::IfcFace* face = new IfcSchema::IfcFaceSurface(bounds, surface, true);
//        create_testcase(file, face, "face surface");
//    }
    const std::string filename = "faces.ifc";
    file.header().file_name().name(filename);
    std::ofstream f(filename.c_str());
    f << file;
}

