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

#ifndef TINYPHYSICS_GEOMETRY_RECTANGLE2D_H
#define TINYPHYSICS_GEOMETRY_RECTANGLE2D_H

#include "polygon2d.h"
#include "point2d.h"

namespace tinyphysics
{

class Rectangle2D: public Polygon2D
{
public:
    
    /**
     * @brief Constructor.
     * 
     * Build a rectangle between given bottom-left point and top-right point.
     * The rectangle is supposed to be parallel to X and Y axes.
     * 
     * @param bottomLeft bottom-left point
     * @param topRight top-right point
     */
    Rectangle2D(const Point2D& bottomLeft, const Point2D& topRight);
    
    //TODO more general constructor
    
    /**
     * @brief Virtual copy constructor.
     */
    Shape2D* clone() const override;
    
    /**
     * @brief Return rectangle area.
     */
    double getArea() const override;
    
    /**
     * @brief Return rectangle width (along X axis).
     * TODO test
     */
    double getWidth() const;
    
    /**
     * @brief Return rectangle height (along Y axis).
     * TODO test
     */
    double getHeight() const;
    
    /**
     * @brief Return bottom left point.
     * TODO test
     */
    Point2D getPosition() const;
};

}


#endif /* TINYPHYSICS_GEOMETRY_RECTANGLE2D_H */

