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
 * @brief Shoot'em up !
 * 
 * Wonderfull sprites there:
 * http://millionthvector.blogspot.fr/p/free-sprites.html
 */

#ifndef TINYPHYSICS_SFML_DEMO3_DEMO_H
#define TINYPHYSICS_SFML_DEMO3_DEMO_H

//STL headers
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdlib>

//Tinyphysics headers
#include "tinyphysics/sfml/application.h"
#include "tinyphysics/sfml/fpscounter.h"
#include "tinyphysics/sfml/color.h"
#include "tinyphysics/geometry/rectangle2d.h"
#include "tinyphysics/geometry/point2d.h"
#include "tinyphysics/geometry/algorithms.h"

namespace tinyphysics
{

class Demo4State: public State
{
public:
    
    Demo4State(Application* application);
    void onKeyPressed(sf::Keyboard::Key key, uint modifiers) override;
    void onMouseClicked(sf::Mouse::Button button, sf::Vector2f position) override;
    void onMouseMoved(sf::Vector2f position) override;
    void update(double dtime) override;
    void draw(double dtime) override;
    
private:
    //Attributes
    sf::Texture mSpaceBackground;
    sf::View mView;
    sf::Vector2f mBackgroundTextRect;
    sf::Sprite mBackgroundSprite;
    std::vector<sf::Texture> mFighterTextures;
    sf::Sprite mFighterSprite;
};

class Demo4: public Application
{
public:
    
    Demo4();
    ~Demo4();
    
private:
    State* mDefaultState;
    State* mFpsCounterState;
};


}

#endif /* TINYPHYSICS_SFML_DEMO3_DEMO_H */

