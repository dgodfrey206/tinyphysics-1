#include "rectangle2d.h"
#include "algorithms.h"

namespace tinyphysics
{
    
Rectangle2D::Rectangle2D(const Point2D& bottomLeft, const Point2D& topRight)
        :Polygon2D(4)
{ 
    setPoint(0, bottomLeft);
    setPoint(1, Point2D(topRight.getX(), bottomLeft.getY()));
    setPoint(2, topRight);
    setPoint(3, Point2D(bottomLeft.getX(), topRight.getY()));
}

Shape2D* Rectangle2D::clone() const
{
    return new Rectangle2D(*this);
}

double Rectangle2D::getArea() const
{
    return distance(getPoint(0), getPoint(1)) * 
            distance(getPoint(1), getPoint(2));
}

double Rectangle2D::getWidth() const
{
    return distance(getPoint(0), getPoint(1));
}

double Rectangle2D::getHeight() const
{
    return distance(getPoint(1), getPoint(2));
}

Point2D Rectangle2D::getPosition() const
{
//    double minY = 100000.;
//    Point2D point;
//    double y1 = mBottomLeftPoint.getY();
//    double y2 = mBottomRightPoint.getY();
//    double y3 = mTopRightPoint.getY();
//    if (y1 <= minY)
//    {
//        minY = y1;
//        point = mBottomLeftPoint;
//    }
//    if (y2 <= minY)
//    {
//        minY = y2;
//        point = mBottomRightPoint;
//    }
//    if (y3 <= minY)
//    {
//        minY = y3;
//        point = mTopRightPoint;
//    }
//    //return point;
//    return mBottomLeftPoint;
    return getPoint(0);
}
    
}