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

#ifndef TINYPHYSICS_GEOMETRY_RAY2D_H
#define TINYPHYSICS_GEOMETRY_RAY2D_H

#include "line2d.h"

namespace tinyphysics
{

/**
 * @brief 2D ray class (semi-infinite line)
 */
class Ray2D: public Line2D
{
    
public:
    
    /**
     * @brief Constructor.
     * 
     * @param point point
     * @param vect direction vector
     */
    Ray2D(const Point2D& point, const Vector2D vect)
            :Line2D(point, vect)
    { }
};

}

#endif /* TINYPHYSICS_GEOMETRY_RAY2D_H */

