#include "catch.hpp"

#include "tinyphysics/geometry/rectangle2d.h"
#include "tinyphysics/geometry/point2d.h"
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
    }
}
