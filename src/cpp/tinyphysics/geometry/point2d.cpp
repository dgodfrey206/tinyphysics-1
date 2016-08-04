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

#include "point2d.h"
#include "vector2d.h"


namespace tinyphysics
{

Point2D::Point2D(): Coord2D(0., 0.)
{ }

Point2D::Point2D(double x, double y): Coord2D(x, y)
{ }

Point2D& Point2D::move(const Vector2D& vect)
{
    operator[](0) += vect.getX();
    operator[](1) += vect.getY();
    return *this;
}

}
