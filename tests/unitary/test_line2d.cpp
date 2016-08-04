#include "catch.hpp"

#include "tinyphysics/geometry/vector2d.h"
#include "tinyphysics/geometry/point2d.h"
#include "tinyphysics/geometry/line2d.h"
#include "tinyphysics/geometry/algorithms.h"

using namespace tinyphysics;

TEST_CASE("Line2D", "[geometry]")
{ 
    SECTION("Constructors")
    {
        //Constructor Point + Vector
        Vector2D vect(1., 2.);
        Point2D origin(0., 0.);
        Line2D line1(origin, vect);
        REQUIRE(almostEquals(line1.getDirectionVector().getX(), 1.));
        REQUIRE(almostEquals(line1.getDirectionVector().getY(), 2.));
        
        //Constructor 2 Points
        Line2D line2(Point2D(0., 0.), Point2D(2., 3.));
        REQUIRE(almostEquals(line2.getDirectionVector().getX(), 2.));
        REQUIRE(almostEquals(line2.getDirectionVector().getY(), 3.));
    }
    
    SECTION("getUnitDirectionVector")
    {
        Line2D line(Point2D(0., 0.), Point2D(2., 2.));
        REQUIRE(almostEquals(line.getUnitDirectionVector().getX(), 1. / std::sqrt(2.)));
        REQUIRE(almostEquals(line.getUnitDirectionVector().getY(), 1. / std::sqrt(2.)));
    }
    
    SECTION("areParallel")
    {
        Line2D line1(Point2D(0., 0.), Point2D(1., 1.));
        Line2D line2(Point2D(0., 0.), Point2D(1., 2.));
        Line2D line3(Point2D(0., 0.), Point2D(2., 2.));
        REQUIRE(areParallel(line1, line3));
        REQUIRE(!areParallel(line1, line2));
    }
    
    SECTION("areCoincident")
    {
        Line2D line1(Point2D(0., 0.), Point2D(1., 1.));
        Line2D line2(Point2D(1., 0.), Point2D(2., 1.));
        Line2D line3(Point2D(0., 0.), Point2D(2., 2.));
        REQUIRE(areCoincident(line1, line3));
        REQUIRE(!areCoincident(line1, line2));
    }
    
    SECTION("get points")
    {
        Line2D line(Point2D(1., 0.), Point2D(2., 1.));
        REQUIRE(areCoincident(line.getFirstPoint(), Point2D(1., 0.)));
        REQUIRE(areCoincident(line.getSecondPoint(), Point2D(2., 1.)));
    }
    
    SECTION("intersectsLine")
    {
        Point2D point;
        //Coincident lines
        Line2D line1(Point2D(0.5, 0.5), Point2D(1., 1.));
        Line2D line2(Point2D(0., 0.), Point2D(2., 2.));
        REQUIRE(line1.intersectsLine(line2, point));
        REQUIRE(almostEquals(point.getX(), 0.5));
        REQUIRE(almostEquals(point.getY(), 0.5));
        //Parallel lines
        Line2D line3(Point2D(1., 0.), Point2D(2., 1.));
        REQUIRE(!line1.intersectsLine(line3, point));
        //Crossing lines
        Line2D line4(Point2D(0., 2.), Point2D(2., 0.));
        REQUIRE(line2.intersectsLine(line4, point));
        REQUIRE(almostEquals(point.getX(), 1.));
        REQUIRE(almostEquals(point.getY(), 1.));        
    }
    
    SECTION("arePerpendicular")
    {
        Line2D line1(Point2D(2., 0.), Point2D(0., 2.));
        Line2D line2(Point2D(0., 0.), Point2D(2., 2.));
        Line2D line3(Point2D(0., 0.), Point2D(1., 2.));
        REQUIRE(arePerpendicular(line1, line2));
        REQUIRE(!arePerpendicular(line3, line2));
    }
    
    SECTION("angleBetween")
    {
        Line2D line1(Point2D(2., 0.), Point2D(0., 2.));
        Line2D line2(Point2D(0., 0.), Point2D(2., 2.));
        Line2D line3(Point2D(0., 0.), Point2D(0., 2.));
        REQUIRE(almostEquals(angleBetween(line1, line2), -PI / 2.));
        REQUIRE(almostEquals(angleBetween(line2, line3), PI / 4.));
    }  
}