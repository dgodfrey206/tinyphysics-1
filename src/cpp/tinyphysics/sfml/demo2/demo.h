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
 * @brief This demos shows how to use HSL colors, textures and shaders.
 */

#ifndef TINYPHYSICS_SFML_DEMO2_DEMO_H
#define TINYPHYSICS_SFML_DEMO2_DEMO_H

//STL headers
#include <iostream>
#include <vector>
#include <sstream>

//Tinyphysics headers
#include "tinyphysics/sfml/application.h"
#include "tinyphysics/sfml/color.h"
#include "tinyphysics/geometry/rectangle2d.h"
#include "tinyphysics/geometry/point2d.h"
#include "tinyphysics/geometry/algorithms.h"

namespace tinyphysics
{

class Demo2State: public State
{
public:
    
    Demo2State(Application* application);
    void onKeyPressed(sf::Keyboard::Key key, uint modifiers) override;
    void draw(double dtime) override;
    
private:
    //Attributes
    sf::Vector3f mHslColor;
    sf::Texture mTexture;
    bool mUseTexture;
    bool mUseShader;
};


class Demo2: public Application
{
public:
    
    Demo2();
    ~Demo2();
    
private:
    State* mDefaultState;
};


}

#endif /* TINYPHYSICS_SFML_DEMO2_DEMO_H */

