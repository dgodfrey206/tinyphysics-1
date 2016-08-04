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

/** 
 * @file
 */

#ifndef TINYPHYSICS_GEOMETRY_DISTANCE_H
#define TINYPHYSICS_GEOMETRY_DISTANCE_H

//STL headers
#include <cmath>
#include <vector>

//Tinyphysics
#include "constants.h"
#include "point2d.h"
#include "vector2d.h"
#include "line2d.h"

namespace tinyphysics
{

//==============================================================================
// UTILITIES
//==============================================================================

/**
 * @brief Stat whether two doubles are almost equal.
 * 
 * @param x
 * @param y
 * @param tolerance
 */
bool inline almostEquals(double x, double y, double tolerance=1.e-8)
{
    return std::abs(x - y) <= tolerance;
}

/**
 * @brief calculate dot product between two 2D vectors.
 * 
 * @param vect1 first vector
 * @param vect2 second vector
 */
inline double dotProduct(const Vector2D& vect1, const Vector2D& vect2)
{
    double result = 0.;
    for (uint i = 0; i < 2; ++i)
    {
        result += vect1.get(i) * vect2.get(i);
    }
    return result;
}

/**
 * @brief calculate perp product between two 2D vectors.
 * 
 * @param vect1 first vector
 * @param vect2 second vector
 */
inline double perpProduct(const Vector2D& vect1, const Vector2D& vect2)
{
    return vect1.get(0) * vect2.get(1) - vect1.get(1) * vect2.get(0);
}

//==============================================================================
// DISTANCE
//==============================================================================

/**
 * @brief Calculate distance between two 2D points.
 * 
 * @param point1 first point
 * @param point2 second point
 */
inline double distance(const Point2D& point1, const Point2D& point2)
{   
    double result = 0.;
    for (size_t i = 0; i < 2; ++i)
    {
        result += std::pow((point1.get(i) - point2.get(i)), 2);
    }
    return std::sqrt(result);
}

//==============================================================================
// COLINEARITY and PARALLELISM
//==============================================================================

/**
 * @brief Stat whether two 2D entities are colinear.
 * 
 * @param vect1 first vector
 * @param vect2 second vector
 * @param tolerance tolerance for perp product equality
 */
inline bool areColinear(const Vector2D& vect1, 
                        const Vector2D& vect2,
                        double tolerance=1.e-8)
{
    return almostEquals(perpProduct(vect1, vect2), tolerance);
}

/**
 * @brief Stat whether two 2D vectors are parallel.
 * 
 * For vectors, parallelism and colinearity mean the same.
 * 
 * @param vect1 first vector
 * @param vect2 second vector
 * @param tolerance tolerance for perp product equality
 */
inline bool areParallel(const Vector2D& vect1, 
                        const Vector2D& vect2,
                        double tolerance=1.e-8)
{
    return almostEquals(perpProduct(vect1, vect2), tolerance);
}

/**
 * @brief Stat whether two 2D lines are parallel.
 * 
 * @param line1 first line
 * @param line2 second line
 * @param tolerance tolerance for perp product equality
 */
inline bool areParallel(const Line2D& line1,
                        const Line2D& line2,
                        double tolerance=1.e-8)
{
    return areColinear(line1.getDirectionVector(), line2.getDirectionVector(),
            tolerance);
}

//==============================================================================
// COINCIDENCE
//==============================================================================

/**
 * @brief Stat whether two 2D points are close enough to be considered 
 * coincidents.
 * 
 * @param point1 first point
 * @param point2 second point
 * @param tolerance distance tolerance between two points
 */
inline bool areCoincident(const Point2D& point1, 
                          const Point2D& point2, 
                          double tolerance=1.e-8)
{
    return almostEquals(distance(point1, point2), 0., tolerance);
}

/**
 * @brief Stat whether two 2D lines are close enough to be considered 
 * coincidents.
 * 
 * @param line1 first line
 * @param line2 second line
 * @param tolerance distance tolerance between two line
 */
inline bool areCoincident(const Line2D& line1, 
                          const Line2D& line2, 
                          double tolerance=1.e-8)
{
    if (!areParallel(line1, line2, tolerance))
        return false;
    else
    {
        //Check perp product
        return almostEquals(perpProduct(line1.getDirectionVector(), 
                Vector2D(line1.getFirstPoint(), line2.getFirstPoint())), 
                tolerance);
    }
}

/**
 * @brief Stat whether a 2D point belongs to a 2D line.
 * 
 * @param line line
 * @param point point
 * @param tolerance tolerance
 */
inline bool areCoincident(const Line2D& line, 
                          const Point2D&point,
                          double tolerance=1.e-8)
{
    return areColinear(line.getDirectionVector(), 
            Vector2D(line.getFirstPoint(), point), tolerance);
}

/**
 * @brief Stat whether a 2D point belongs to a 2D line.
 * 
 * @param line line
 * @param point point
 * @param tolerance tolerance
 */
inline bool areCoincident(const Point2D&point,
                          const Line2D& line, 
                          double tolerance=1.e-8)
{
    return areColinear(line.getDirectionVector(), 
            Vector2D(line.getFirstPoint(), point), tolerance);
}


//==============================================================================
// PERPENDICULARTY
//==============================================================================

/**
 * @brief Stat whether two 2D vectors are perpendicular.
 * 
 * @param vect1 first vector
 * @param vect2 second vector
 */
inline bool arePerpendicular(const Vector2D& vect1, 
                             const Vector2D& vect2,
                             double tolerance=1.e-8)
{
    return almostEquals(dotProduct(vect1, vect2), tolerance);
}

/**
 * @brief Stat whether two 2D lines are perpendicular.
 * 
 * @param line1 first line
 * @param line2 second line
 */
inline bool arePerpendicular(const Line2D& line1, 
                             const Line2D& line2,
                             double tolerance=1.e-8)
{
    return almostEquals(dotProduct(line1.getDirectionVector(), 
            line2.getDirectionVector()), tolerance);
}

//==============================================================================
// ANGLES
//==============================================================================

/**
 * @brief Returns the angle between two 2D entities.
 * 
 * If entities are given in trigonometric order, a positive angle (in radians)
 * is returned. Otherwise, a negative angle is returned.
 * 
 * @param vect1 first vector
 * @param vect2 second vector
 */
inline double angleBetween(const Vector2D& vect1, const Vector2D& vect2)
{
    return std::atan2(vect2.getY(), vect2.getX()) - 
           std::atan2(vect1.getY(), vect1.getX());
}

/**
 * @brief Returns the angle between two 2D entities.
 * 
 * If entities are given in trigonometric order, a positive angle (in radians)
 * is returned. Otherwise, a negative angle is returned.
 * 
 * @param line1 first line
 * @param line2 second line
 */
inline double angleBetween(const Line2D& line1, const Line2D& line2)
{
    return angleBetween(line1.getDirectionVector(), line2.getDirectionVector());
}

//==============================================================================
// INTERSECTION
//==============================================================================

class Intersection2D
{
public:
    
    enum Method { OnlyFirstIntersection, AllIntersections };
    
    /**
     * @brief Constructor.
     */
    Intersection2D();
    
    /**
     * @brief Constructor.
     * 
     * A method may be specified. By default only first intersection is looked 
     * for.
     */
    Intersection2D(Intersection2D::Method method);
    
    /**
     * @brief Destructor.
     */
    ~Intersection2D();
    
    /**
     * @brief Set tolerance.
     * 
     * @param tolerance tolerance value
     */
    void setTolerance(double tolerance);
    
    /**
     * @brief Get tolerance.
     */
    double getTolerance() const;
    
    /**
     * @brief Set method for intersection check.
     * 
     * @param method
     */
    void setMethod(Intersection2D::Method method);
    
    /**
     * @brief Return the current method for intersection check.
     */
    Intersection2D::Method getMethod() const;
    
    /**
     * @brief Return the number of intersections found.
     */
    size_t countIntersections() const;
    
    /**
     * @brief Get n'th intersection point.
     * 
     * @param index number of intersection point
     */
    Point2D getIntersectionPoint(size_t index) const;
    
    /**
     * @brief Check whether two 2D entities intersect.
     */
    bool intersect(const Line2D& line1, const Line2D& line2);
    
private:
    
    //Disabled operators
    Intersection2D(const Intersection2D& other);
    Intersection2D(Intersection2D&& other);
    Intersection2D& operator=(const Intersection2D& other);
    Intersection2D& operator=(Intersection2D&& other);
    
    /**
     * @brief Reset results
     */
    void reset();
    
    /**
     * @brief Calculate s and t parameters at intersection.
     * 
     * If no intersection is found (because entity are parallel), s and t are 
     * set to NAN.
     * 
     * @param vect1 direction vector of first entity
     * @param vect2 direction vector of second entity
     * @param point1 first point of first entity
     * @param point2 second point of second entity
     * @param s parameter value for first entity at intersection
     * @param t parameter value for second entity at intersection
     */
    void calculateParametersAtIntersection(
            const Vector2D& vect1,
            const Vector2D& vect2,
            const Point2D& point1,
            const Point2D& point2,
            double& s,
            double& t) const;
    
    //Attributes
    Intersection2D::Method mMethod;
    double mTolerance;
    std::vector<Point2D> mPoints;
};

}

#endif /* TINYPHYSICS_GEOMETRY_DISTANCE_H */

