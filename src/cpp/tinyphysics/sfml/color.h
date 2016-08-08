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

#ifndef TINYPHYSICS_SMFL_COLOR_H
#define TINYPHYSICS_SMFL_COLOR_H

//STL headers
#include <algorithm>
#include <cmath>

//SFML headers
#include <SFML/Graphics.hpp>

namespace tinyphysics
{

/**
 * @brief Convert a RGB color into a HSL (Hue/Saturation/Luminance) color.
 * 
 * @param color RGB color
 */
sf::Vector3f convertRgbToHslColor(sf::Color color);
    
/**
 * @brief Convert a HSL (Hue/Saturation/Luminance) color into a RGB color.
 * 
 * @param color HSL color
 */
sf::Color convertHslToRgbColor(sf::Vector3f color);

} // namespace tinyphysics

#endif /* TINYPHYSICS_SFML_COLOR_H */

