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

#ifndef TINYPHYSICS_GEOMETRY_COORD2D_H
#define TINYPHYSICS_GEOMETRY_COORD2D_H

//STL headers
#include <array>
#include <cmath>

namespace tinyphysics
{
    
/**
 * @brief Coordinates in 2D space
 */ 
class Coord2D
{
public:
    
    /**
     * @brief Destructor.
     */
    virtual ~Coord2D() = default;
    
    /**
     * @brief Copy constructor.
     * 
     * @param other object to be copied from
     */
    Coord2D(const Coord2D& other) = default;
    
    /**
     * @brief Move constructor.
     * 
     * @param other object to be moved from
     */
    Coord2D(Coord2D&& other) = default;
    
    /**
     * @brief Assignment operator.
     * 
     * @param other object to be assigned from
     */
    Coord2D& operator=(const Coord2D& other) = default;
    
    /**
     * @brief Move assignment operator.
     * 
     * @param other object to be assigned from
     */
    Coord2D& operator=(Coord2D&& other) = default;
    
    /**
     * @brief Return X coordinate.
     */
    inline double getX() const
    {
        return mArray[0];
    }

    /**
     * @brief Return Y coordinate.
     */    
    inline double getY() const
    {
        return mArray[1];
    }
    
    /**
     * @brief Return coordinate at given index.
     * 
     * @param index coordinate index.
     */
    inline double get(size_t index) const
    {
        return mArray[index];
    }

    /**
     * @brief Return coordinate at given index.
     * 
     * @param index coordinate index.
     */
    inline const double& operator[](size_t index) const
    {
        return mArray[index];
    }
    
    /**
     * @brief Return coordinate at given index.
     * 
     * @param index coordinate index.
     */
    inline double& operator[](size_t index)
    {
        return mArray[index];
    }

protected:
    
    /**
     * @brief Constructor.
     * 
     * @param x
     * @param y
     */
    Coord2D(double x, double y);
    
private:
    
    //Attributes
    std::array<double, 2> mArray; //hold coordinates
};
    
}



#endif /* TINYPHYSICS_GEOMETRY_COORD2D_H */

