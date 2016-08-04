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
#include "polygon2d.h"


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


bool Intersection2D::intersect(const Line2D& line1, const Line2D& line2, 
        bool forceReset)
{
    //Reset results
    if (forceReset) reset();
    
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


bool Intersection2D::intersect(const Ray2D& ray, const Segment2D& segment, 
        bool forceReset)
{
    //Reset results
    if (forceReset) reset();
    
    //Check parallelism
    if (areParallel(ray, segment))
    {
        if (areCoincident(ray, segment))
        {
            mPoints.push_back(segment.getFirstPoint());
            mPoints.push_back(segment.getSecondPoint());
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        Point2D a = ray.getFirstPoint();
        Point2D b = ray.getSecondPoint();
        double s = 0.;
        double t = 0.;
        calculateParametersAtIntersection(
                ray.getDirectionVector(),
                segment.getDirectionVector(),
                a, segment.getFirstPoint(),
                s, t);
        if ((s >= 0.) && (t >= 0.) && (t <= 1.))
        {
            double x = a.getX() + s * (b.getX() - a.getX());
            double y = a.getY() + s * (b.getY() - a.getY());
            mPoints.push_back(Point2D(x, y));
            return true;
        }
    }
    return false;
}

bool Intersection2D::intersect(const Segment2D& segment, const Ray2D& ray, 
        bool forceReset)
{
    return intersect(ray, segment, forceReset);
}

bool Intersection2D::intersect(const Segment2D& segment1, 
        const Segment2D& segment2, bool forceReset)
{
    //Reset results
    if (forceReset) reset();
    
    //Check parallelism
    if (areParallel(segment1, segment2))
    {
        bool found = false;
        if (areCoincident(segment2, segment1.getFirstPoint()))
        {
            mPoints.push_back(segment1.getFirstPoint());
            found = true;
        }
        if (areCoincident(segment2, segment1.getSecondPoint()))
        {
            mPoints.push_back(segment1.getSecondPoint());
            found = true;
        }
        if (areCoincident(segment1, segment2.getFirstPoint()))
        {
            mPoints.push_back(segment2.getFirstPoint());
            found = true;
        }
        if (areCoincident(segment1, segment2.getSecondPoint()))
        {
            mPoints.push_back(segment2.getSecondPoint());
            found = true;
        }
        if (found)
            return true;
        else
            return false;
    }
    else
    {
        Point2D a = segment1.getFirstPoint();
        Point2D b = segment1.getSecondPoint();
        double s = 0.;
        double t = 0.;
        calculateParametersAtIntersection(
                segment1.getDirectionVector(),
                segment2.getDirectionVector(),
                a, segment2.getFirstPoint(),
                s, t);
        if ((s >= 0.) && (s <= 1.) && (t >= 0.) && (t <= 1.))
        {
            double x = a.getX() + s * (b.getX() - a.getX());
            double y = a.getY() + s * (b.getY() - a.getY());
            mPoints.push_back(Point2D(x, y));
            return true;
        }
    }
    return false;
}

bool Intersection2D::intersect(const Polygon2D& poly1, const Polygon2D& poly2, 
        bool forceReset)
{
    //Reset
    if (forceReset) reset();
    
    //Loop on all segments of polygon 1 and polygon 2
    bool status = false;
    for (size_t i = 0; i < poly1.countSegments(); ++i)
    {
        for (size_t j = 0; j < poly2.countSegments(); ++j)
        {
            status = intersect(poly1.getSegment(i), poly2.getSegment(j),
                    false) || status;
        }
    }
    return status;
}

}

