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

void Line2D::calculateParametersAtIntersection(const Line2D& other, double& s, 
        double& t) const
{
        Vector2D u = getDirectionVector();
        Vector2D v = other.getDirectionVector();
        Vector2D w = Vector2D(other.mA, mA);
        double uv = perpProduct(u, v);
        double uw = perpProduct(u, w);
        double vw = perpProduct(v, w);
        if ((uv > 0.) || (uv < 0.))
            s = vw / uv;
        else
            s = NAN;
        if ((uv > 0.) || (uv < 0.))
            t = uw / uv;
        else
            t = NAN;
}

bool Line2D::intersectsLine(const Line2D& other, Point2D& point) const
{
    if (areParallel(*this, other))
    {
        if (areCoincident(*this, other))
        {
            point = mA; //A point is returned arbitrarily
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        double s = 0.;
        double t = 0.;
        calculateParametersAtIntersection(other, s, t);
        double x = mA.getX() + s * (mB.getX() - mA.getX());
        double y = mA.getY() + s * (mB.getY() - mA.getY());
        point = Point2D(x, y);
        return true;
    }
}

}