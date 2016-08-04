#include "catch.hpp"

#include "tinyphysics/geometry/algorithms.h"
#include "tinyphysics/geometry/point2d.h"
#include "tinyphysics/geometry/vector2d.h"

using namespace tinyphysics;

TEST_CASE("algorithms", "[geometry]")
{ 
    SECTION("distance between two points")
    {
        Point2D origin;
        Point2D point(3., 4.);
        REQUIRE(distance(origin, point) == 5.);
    }
    
    SECTION("coincidence between two points")
    {
        Point2D origin;
        Point2D point1(1., 1.);
        Point2D point2(1.e-9, 1.e-9);
        REQUIRE(!areCoincident(point1, point2));
        REQUIRE(areCoincident(point2, origin));
    }
    
    SECTION("dot product")
    {
        Vector2D vect1(1., 2.);
        Vector2D vect2(3., 4.);
        REQUIRE(almostEquals(dotProduct(vect1, vect2), 11.));
    }
    
    SECTION("perp product")
    {
        Vector2D vect1(1., 0.);
        Vector2D vect2(0., 1.);
        REQUIRE(almostEquals(perpProduct(vect1, vect2), 1.));
        REQUIRE(almostEquals(perpProduct(vect2, vect1), -1.));
        Vector2D vect3(1., 0.);
        Vector2D vect4(2., 0.);
        REQUIRE(almostEquals(perpProduct(vect3, vect4), 0.));
    }
    
    SECTION("are colinear")
    {
        Vector2D vect1(1., 0.);
        Vector2D vect2(0., 1.);
        Vector2D vect3(2., 0.);
        REQUIRE(areColinear(vect1, vect3));
        REQUIRE(!areColinear(vect1, vect2));
    }
    
    SECTION("are perpendicular")
    {
        Vector2D vect1(1., 0.);
        Vector2D vect2(0., 1.);
        Vector2D vect3(2., 0.);
        REQUIRE(!arePerpendicular(vect1, vect3));
        REQUIRE(arePerpendicular(vect1, vect2));        
    }
    
    SECTION("angle between")
    {
        Vector2D vect1(1., 0.);
        Vector2D vect2(0., 1.);
        Vector2D vect3(2., 0.);
        REQUIRE(almostEquals(angleBetween(vect1, vect3), 0.));
        REQUIRE(almostEquals(angleBetween(vect1, vect2), PI / 2.));
        REQUIRE(almostEquals(angleBetween(vect2, vect1), -PI / 2.));
        Vector2D vect4(1., 1.);
        REQUIRE(almostEquals(angleBetween(vect1, vect4), PI / 4.));
    }
    
    SECTION("point on line")
    {
        Point2D point1(10., 10.);
        Point2D point2(1., 0.);
        Line2D line(Point2D(0., 0.), Vector2D(1., 1.));
        REQUIRE(areCoincident(line, point1));
        REQUIRE(!areCoincident(line, point2));
    }
}