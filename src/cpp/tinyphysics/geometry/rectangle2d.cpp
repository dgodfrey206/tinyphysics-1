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

Rectangle2D::Rectangle2D(const Point2D& bottomLeft, const Point2D& bottomRight, 
        const Point2D& point)
        :Polygon2D(4)
{ 
    setPoint(0, bottomLeft);
    setPoint(1, bottomRight);
    Line2D perpendicular = Line2D(bottomLeft, bottomRight)
            .createPerpendicularLine(bottomRight);
    Point2D tmp(point);
    projection(perpendicular, tmp);
    setPoint(2, tmp);
    perpendicular = Line2D(bottomLeft, bottomRight)
            .createPerpendicularLine(bottomLeft);
    tmp = point;
    projection(perpendicular, tmp);
    setPoint(3, tmp);
}

Shape2D* Rectangle2D::clone() const
{
    return new Rectangle2D(*this);
}

double Rectangle2D::getArea() const
{
    return getSegment(0).getLength() * getSegment(1).getLength();
}

double Rectangle2D::getWidth() const
{
    return distance(getPoint(0), getPoint(1));
}

double Rectangle2D::getHeight() const
{
    return distance(getPoint(1), getPoint(2));
}
    
}