/*
 * Tinyphysics
 * Copyright (C) 2016 Cédric Campguilhem
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "algorithms.h"


namespace tinyphysics
{

//==============================================================================
// INTERSECTION2D
//==============================================================================

Intersection2D::Intersection2D()
        :mMethod(Intersection2D::OnlyFirstIntersection),
        mTolerance(1.e-8),
        mPoints()
{ }

Intersection2D::Intersection2D(Intersection2D::Method method)
        :mMethod(method),
        mTolerance(1.e-8),
        mPoints()
{ }

Intersection2D::~Intersection2D()
{ }

void Intersection2D::setTolerance(double tolerance) 
{
    mTolerance = tolerance;
}

double Intersection2D::getTolerance() const
{
    return mTolerance;
}

void Intersection2D::setMethod(Intersection2D::Method method)
{
    mMethod = method;
}

Intersection2D::Method Intersection2D::getMethod() const
{
    return mMethod;
}

size_t Intersection2D::countIntersections() const
{
    return mPoints.size();
}

Point2D Intersection2D::getIntersectionPoint(size_t index) const
{
    return mPoints[index];
}

void Intersection2D::reset()
{
    mPoints.clear();    
}

void Intersection2D::calculateParametersAtIntersection(const Vector2D& u, 
        const Vector2D& v, const Point2D& point1, const Point2D& point2,  
        double& s, double& t) const
{
        Vector2D w = Vector2D(point2, point1);
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


bool Intersection2D::intersect(const Line2D& line1, const Line2D& line2)
{
    //Reset results
    reset();
    
    //Check parallelism
    if (areParallel(line1, line2))
    {
        if (areCoincident(line1, line2))
        {
            mPoints.push_back(line1.getFirstPoint());
            mPoints.push_back(line1.getSecondPoint());
            mPoints.push_back(line2.getFirstPoint());
            mPoints.push_back(line2.getSecondPoint());
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        Point2D a = line1.getFirstPoint();
        Point2D b = line1.getSecondPoint();
        double s = 0.;
        double t = 0.;
        calculateParametersAtIntersection(
                line1.getDirectionVector(),
                line2.getDirectionVector(),
                a, line2.getFirstPoint(),
                s, t);
        double x = a.getX() + s * (b.getX() - a.getX());
        double y = a.getY() + s * (b.getY() - a.getY());
        mPoints.push_back(Point2D(x, y));
        return true;
    }
    
    
    
    
}

}

