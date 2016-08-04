#include "catch.hpp"

#include "tinyphysics/geometry/vector2d.h"
#include "tinyphysics/geometry/algorithms.h"

using namespace tinyphysics;

TEST_CASE("Vector2D", "[geometry]")
{ 
    SECTION("constructors")
    {
        //Constructor
        Vector2D vect1(1., 2.);
        REQUIRE(almostEquals(vect1.getX(), 1.));
        REQUIRE(almostEquals(vect1.getY(), 2.));
        
        //Default constructor
        Vector2D vect2;
        REQUIRE(almostEquals(vect2.getX(), 0.));
        REQUIRE(almostEquals(vect2.getY(), 0.));
                
        //Copy constructor
        Vector2D vect3(vect1);
        REQUIRE(almostEquals(vect3.getX(), 1.));
        REQUIRE(almostEquals(vect3.getY(), 2.));

        //Assignment operator
        vect2 = vect3;
        REQUIRE(almostEquals(vect2.getX(), 1.));
        REQUIRE(almostEquals(vect3.getY(), 2.));
        
        //Move constructor
        Vector2D vect4(Vector2D(3., 4.));
        REQUIRE(almostEquals(vect4.getX(), 3.));
        REQUIRE(almostEquals(vect4.getY(), 4.));
        Vector2D vect5(std::move(vect4));
        REQUIRE(almostEquals(vect5.getX(), 3.));
        REQUIRE(almostEquals(vect5.getY(), 4.));

        //Move assignment operator
        vect5 = Vector2D(10., 11.);
        REQUIRE(almostEquals(vect5.getX(), 10.));
        REQUIRE(almostEquals(vect5.getY(), 11.));
        
        //From two 2D points
        Vector2D vect6(Point2D(1., 2.), Point2D(3., 5.));
        REQUIRE(almostEquals(vect6.getX(), 2.));
        REQUIRE(almostEquals(vect6.getY(), 3.));
    }
    
    SECTION("getNorm")
    {
        Vector2D vect(3., 4.);
        REQUIRE(almostEquals(vect.getNorm(), 5.));
    }
    
    SECTION("normalize")
    {
        Vector2D vect1(2., 2.);
        vect1.normalize();
        REQUIRE(almostEquals(vect1.getNorm(), 1.));
        Vector2D vect2(0., 0.);
        vect2.normalize();
        REQUIRE(almostEquals(vect2.getNorm(), 0.));
    }
    
    SECTION("dotProduct")
    {
        Vector2D vect1(1., 2.);
        Vector2D vect2(3., 4.);
        REQUIRE(almostEquals(dotProduct(vect1, vect2), 11.));
        REQUIRE(almostEquals(dotProduct(vect2, vect1), 11.));
        Vector2D vect3(1., 0.);
        Vector2D vect4(0., 1.);
        REQUIRE(almostEquals(dotProduct(vect3, vect4), 0.));
        REQUIRE(almostEquals(dotProduct(vect4, vect3), 0.));
    }
    
    SECTION("perpProduct")
    {
        Vector2D vect1(1., 0.);
        Vector2D vect2(0., 1.);
        REQUIRE(almostEquals(perpProduct(vect1, vect2), 1.));
        REQUIRE(almostEquals(perpProduct(vect2, vect1), -1.));
        Vector2D vect3(1., 0.);
        Vector2D vect4(2., 0.);
        REQUIRE(almostEquals(perpProduct(vect3, vect4), 0.));
    }
}