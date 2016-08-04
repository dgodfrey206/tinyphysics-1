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

#include "vector2d.h"


namespace tinyphysics
{
    Vector2D::Vector2D(): Coord2D(0., 0.)
    { }
    
    Vector2D::Vector2D(double x, double y): Coord2D(x, y)
    { }
    
    Vector2D::Vector2D(const Point2D& point1, const Point2D& point2):
        Coord2D(point2.getX() - point1.getX(), point2.getY() - point1.getY())
    { }
}
