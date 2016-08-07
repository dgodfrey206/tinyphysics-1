#include "line2d.h"
#include "algorithms.h"

namespace tinyphysics
{

Line2D::Line2D(const Point2D& point1, const Point2D& point2):
        mA(point1),
        mB(point2)
{ }

Line2D::Line2D(const Point2D& point, const Vector2D& vect):
        mA(point),
        mB(Point2D(point).move(vect))
{ }

Vector2D Line2D::getDirectionVector() const
{
    return Vector2D(mA, mB);
}

Vector2D Line2D::getUnitDirectionVector() const
{
    return Vector2D(mA, mB).normalize();
}

Line2D Line2D::createPerpendicularLine(const Point2D& point) const
{
    Vector2D direction = getDirectionVector();
    return Line2D(point, Vector2D(-direction.getY(), direction.getX()));
}

Line2D Line2D::createParallelLine(const Point2D& point) const
{
    return Line2D(point, getDirectionVector());
}

} // namespace tinyphysics