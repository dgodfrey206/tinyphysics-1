#include "polygon2d.h"

namespace tinyphysics
{

Polygon2D::Polygon2D(size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        mPoints.emplace_back(0., 0.);
    }
}

Shape2D* Polygon2D::clone() const
{
    return new Polygon2D(*this);
}

double Polygon2D::getArea() const 
{
    return 0.;
}

void Polygon2D::setPoint(size_t index, const Point2D& point) 
{
    mPoints[index] = point;
}

Point2D Polygon2D::getPoint(size_t index) const
{
    return mPoints[index];
}

size_t Polygon2D::countPoints() const
{
    return mPoints.size();
}

bool Polygon2D::contains(const Point2D& point) const
{
    return false;
}

}