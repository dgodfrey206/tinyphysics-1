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

#ifndef TINYPHYSICS_GEOMETRY_POLYGON2D_H
#define TINYPHYSICS_GEOMETRY_POLYGON2D_H

//STL headers
#include <vector>

//Tinyphysics
#include "shape2d.h"
#include "point2d.h"
#include "segment2d.h"


namespace tinyphysics
{

/**
 * @brief Base class for any 2D polygon
 */
class Polygon2D: public Shape2D
{
public:
    
    /**
     * @brief Constructor.
     * 
     * @param size number of points.
     */
    Polygon2D(size_t size);
    
    /**
     * @brief Destructor.
     */
    ~Polygon2D() override = default;
    
    /**
     * @brief Virtual copy constructor.
     */
    Shape2D* clone() const override;
    
    /**
     * @brief Calculate area delimited by polygon.
     */
    double getArea() const override;
    
    /**
     * @brief Return the number of points in polygon.
     */
    size_t countPoints() const;
    
    /**
     * @brief Return the number of segments in polygon.
     */
    size_t countSegments() const;
    
    /**
     * @brief Set point at given index.
     * 
     * @param index index of point
     * @param point point to be set
     */
    void setPoint(size_t index, const Point2D& point);
    
    /**
     * @brief Get point at given index.
     * 
     * @param index index of point
     */
    Point2D getPoint(size_t index) const;
    
    /**
     * @brief Get segment at given index.
     * 
     * @param index index of segment
     */
    Segment2D getSegment(size_t index) const;
        
protected:    

    /**
     * @brief Copy constructor.
     * 
     * @param other object to be copied from
     */
    Polygon2D(const Polygon2D& other) = default;
    
    /**
     * @brief Move constructor.
     * 
     * @param other object to be copied from
     */    
    Polygon2D(Polygon2D&& other) = default;
    
    /**
     * @brief Assignment operator.
     * 
     * @param other object to be assigned from
     */
    Polygon2D& operator=(const Polygon2D& other) = default;
    
    /**
     * @brief Move assignment operator.
     * 
     * @param other object to be move assigned from
     */    
    Polygon2D& operator=(Polygon2D&& other) = default;

private:
    //Attributes
    std::vector<Point2D> mPoints;
};

}


#endif /* TINYPHYSICS_GEOMETRY_POLYGON2D_H */

