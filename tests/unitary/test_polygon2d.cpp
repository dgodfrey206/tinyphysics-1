#include "catch.hpp"

#include "tinyphysics/geometry/polygon2d.h"
#include "tinyphysics/geometry/point2d.h"
#include "tinyphysics/geometry/algorithms.h"


using namespace tinyphysics;


TEST_CASE("Polygon2d", "[geometry]")
{
    SECTION("Constructor")
    {
        Polygon2D polygon(4);
        polygon.setPoint(0, Point2D(0., 0.));
        polygon.setPoint(1, Point2D(1., 0.));
        polygon.setPoint(2, Point2D(1., 1.));
        polygon.setPoint(3, Point2D(0., 1.));
        REQUIRE(almostEquals(polygon.getPoint(0).getX(), 0.));
        REQUIRE(almostEquals(polygon.getPoint(0).getY(), 0.));
        REQUIRE(almostEquals(polygon.getPoint(1).getX(), 1.));
        REQUIRE(almostEquals(polygon.getPoint(1).getY(), 0.));
        REQUIRE(almostEquals(polygon.getPoint(2).getX(), 1.));
        REQUIRE(almostEquals(polygon.getPoint(2).getY(), 1.));
        REQUIRE(almostEquals(polygon.getPoint(3).getX(), 0.));
        REQUIRE(almostEquals(polygon.getPoint(3).getY(), 1.));        
    }
    
    SECTION("intersection")
    {
        Polygon2D polygon1(4);
        polygon1.setPoint(0, Point2D(0., 0.));
        polygon1.setPoint(1, Point2D(1., 0.));
        polygon1.setPoint(2, Point2D(1., 1.));
        polygon1.setPoint(3, Point2D(0., 1.));
        Polygon2D polygon2(4);
        polygon2.setPoint(0, Point2D(0.5, 0.5));
        polygon2.setPoint(1, Point2D(1.5, 0.5));
        polygon2.setPoint(2, Point2D(1.5, 1.5));
        polygon2.setPoint(3, Point2D(0.5, 1.5));        
        Intersection2D algo;
        REQUIRE(algo.intersect(polygon1, polygon2));
        REQUIRE(algo.countIntersections() == 2);
        REQUIRE(areCoincident(algo.getIntersectionPoint(0), Point2D(1., 0.5)));
        REQUIRE(areCoincident(algo.getIntersectionPoint(1), Point2D(0.5, 1.)));        
    }
}
