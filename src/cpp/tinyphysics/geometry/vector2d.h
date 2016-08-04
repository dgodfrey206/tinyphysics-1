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

#ifndef TINYPHYSICS_GEOMETRY_VECTOR2D_H
#define TINYPHYSICS_GEOMETRY_VECTOR2D_H

//Tinyphysics
#include "coord2d.h"
#include "point2d.h"

namespace tinyphysics
{
    
class Vector2D: public Coord2D
{
public:
    
    /**
     * @brief Constructor.
     * 
     * A point with X = 0 and Y = 0 is created.
     */
    Vector2D();
    
    /**
     * @brief Constructor.
     * 
     * @param x X coordinate
     * @param y Y coordinate
     */
    Vector2D(double x, double y);
    
    /**
     * @brief Constructor.
     * 
     * Build a vector from two 2D points.
     * 
     * @param point1 begin of vector
     * @param point2 end of vector
     */
    Vector2D(const Point2D& point1, const Point2D& point2);
    
    /**
     * @brief Destructor.
     */
    virtual ~Vector2D() = default;
    
    /**
     * @brief Copy constructor.
     * 
     * @param other object to be copied from
     */
    Vector2D(const Vector2D& other) = default;

    /**
     * @brief Move constructor.
     * 
     * @param other object to be moved from
     */    
    Vector2D(Vector2D&& other) = default;
    
    /**
     * @brief Assignment operator.
     * 
     * @param other object to be assigned from
     */
    Vector2D& operator=(const Vector2D& other) = default;
    
    /**
     * @brief Move assignment operator.
     * 
     * @param other object to be moved-assigned from
     */
    Vector2D& operator=(Vector2D&& other) = default;
    
    /**
     * @brief Calculate norm of vector.
     */
    inline double getNorm() const
    {
        double result = 0.;
        for (uint i = 0; i < 2; ++i)
        {
            result += get(i) * get(i);
        }
        return std::sqrt(result);
    }
    
    /**
     * @brief Normalize (turn into a vector which norm is equal to 1.)
     * 
     * If norm is null, the vector is left unchanged.
     */
    inline Vector2D& normalize()
    {
        double norm = getNorm();
        if (norm > 0)
        {
            operator[](0) /= norm;
            operator[](1) /= norm;
        }
        return *this;
    }    
};

}




#endif /* TINYPHYSICS_GEOMETRY_VECTOR2D_H */

