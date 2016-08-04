#include "catch.hpp"

#include "tinyphysics/geometry/point2d.h"
#include "tinyphysics/geometry/vector2d.h"
#include "tinyphysics/geometry/algorithms.h"

using namespace tinyphysics;

TEST_CASE("Point2D", "[geometry]")
{ 
    SECTION("constructors")
    {
        //Constructor
        Point2D point1(1., 2.);
        REQUIRE(almostEquals(point1.getX(), 1.));
        REQUIRE(almostEquals(point1.getY(), 2.));
        
        //Default constructor
        Point2D point2;
        REQUIRE(almostEquals(point2.getX(), 0.));
        REQUIRE(almostEquals(point2.getY(), 0.));
                
        //Copy constructor
        Point2D point3(point1);
        REQUIRE(almostEquals(point3.getX(), 1.));
        REQUIRE(almostEquals(point3.getY(), 2.));

        //Assignment operator
        point2 = point3;
        REQUIRE(almostEquals(point2.getX(), 1.));
        REQUIRE(almostEquals(point3.getY(), 2.));
        
        //Move constructor
        Point2D point4(Point2D(3., 4.));
        REQUIRE(almostEquals(point4.getX(), 3.));
        REQUIRE(almostEquals(point4.getY(), 4.));
        Point2D point5(std::move(point4));
        REQUIRE(almostEquals(point5.getX(), 3.));
        REQUIRE(almostEquals(point5.getY(), 4.));

        //Move assignment operator
        point5 = Point2D(10., 11.);
        REQUIRE(almostEquals(point5.getX(), 10.));
        REQUIRE(almostEquals(point5.getY(), 11.));
    }
    
    SECTION("distance")
    {
        Point2D origin;
        Point2D point(3., 4.);
        REQUIRE (almostEquals(distance(point, origin), 5.));
        REQUIRE (almostEquals(distance(origin, point), 5.));
    }
    
    SECTION("getters")
    {
        Point2D point(3., 4.);
        REQUIRE(almostEquals(point.getX(), 3.));
        REQUIRE(almostEquals(point.getY(), 4.));
        REQUIRE(almostEquals(point.get(0), 3.));
        REQUIRE(almostEquals(point.get(1), 4.));
        REQUIRE(almostEquals(point[0], 3.));
        REQUIRE(almostEquals(point[1], 4.));
    }
    
    SECTION("setters")
    {
        Point2D point(0., 0.);
        point[0] = 1.;
        point[1] = 2.;
        REQUIRE(almostEquals(point.getX(), 1.));
        REQUIRE(almostEquals(point.getY(), 2.));
    }
    
    SECTION("move")
    {
        Point2D point(3., 4.);
        Vector2D move(1., 2.);
        point.move(move);
        REQUIRE(almostEquals(point.getX(), 4.));
        REQUIRE(almostEquals(point.getY(), 6.));
    }
}