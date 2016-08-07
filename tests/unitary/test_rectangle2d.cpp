#include "catch.hpp"

#include "tinyphysics/geometry/rectangle2d.h"
#include "tinyphysics/geometry/point2d.h"
#include "tinyphysics/geometry/segment2d.h"
#include "tinyphysics/geometry/algorithms.h"


using namespace tinyphysics;


TEST_CASE("rectangle2d", "[geometry]")
{
    SECTION("Constructor")
    {
        Point2D point1(0., 0.);
        Point2D point2(1., 1.);
        Rectangle2D rect1(point1, point2);
        REQUIRE(almostEquals(rect1.getArea(), 1.));
        Point2D point3(2., 0.);
        Point2D point4(1., 2.);
        Rectangle2D rect2(point1, point3, point4);
        REQUIRE(areCoincident(rect2.getPoint(2), Point2D(2., 2.)));
        REQUIRE(areCoincident(rect2.getPoint(3), Point2D(0., 2.)));
    }
    
    SECTION("getPoint")
    {
        Point2D point1(0., 0.);
        Point2D point2(1., 1.);
        Rectangle2D rect1(point1, point2);
        REQUIRE(areCoincident(rect1.getPoint(1), Point2D(1., 0.)));
        REQUIRE(rect1.countPoints() == 4);
    }
    
    SECTION("getSegment")
    {
        Point2D point1(0., 0.);
        Point2D point2(1., 1.);
        Rectangle2D rect1(point1, point2);
        REQUIRE(rect1.countSegments() == 4);
        Segment2D segment = rect1.getSegment(3);
        REQUIRE(areCoincident(segment.getFirstPoint(), Point2D(0., 1.)));
        REQUIRE(areCoincident(segment.getSecondPoint(), Point2D(0., 0.)));
    }
    
    SECTION("clone")
    {
        Point2D point1(0., 0.);
        Point2D point2(1., 1.);
        Rectangle2D rect(point1, point2);
        Rectangle2D* copy = dynamic_cast<Rectangle2D*>(rect.clone());
        for (size_t i = 0; i < rect.countPoints(); ++i)
        {
            REQUIRE(areCoincident(rect.getPoint(i), copy->getPoint(i)));
        }
    }
    
    SECTION("getArea")
    {
        Point2D point1(0., 0.);
        Point2D point2(2., 1.);
        Rectangle2D rect(point1, point2);
        REQUIRE(almostEquals(rect.getArea(), 2.));
    }
    
    SECTION("getWidth")
    {
        Point2D point1(0., 0.);
        Point2D point2(2., 1.);
        Rectangle2D rect(point1, point2);
        REQUIRE(almostEquals(rect.getWidth(), 2.));        
    }

    SECTION("getHeigh")
    {
        Point2D point1(0., 0.);
        Point2D point2(2., 1.);
        Rectangle2D rect(point1, point2);
        REQUIRE(almostEquals(rect.getHeight(), 1.));                
    }
    

    
}
