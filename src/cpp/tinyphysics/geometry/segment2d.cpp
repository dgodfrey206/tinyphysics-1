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

#include "segment2d.h"
#include "algorithms.h"

namespace tinyphysics
{

Segment2D::Segment2D(const Point2D& point1, const Point2D& point2)
        :Line2D(point1, point2)
{ }

double Segment2D::getLength() const
{
    return distance(getFirstPoint(), getSecondPoint());
}

} // namespace tinyphysics

