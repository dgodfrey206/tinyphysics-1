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
 * @brief This demo is a first using particles and gravitational forces.
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
#include "tinyphysics/sfml/color.h"
#include "tinyphysics/geometry/rectangle2d.h"
#include "tinyphysics/geometry/point2d.h"
#include "tinyphysics/geometry/algorithms.h"

namespace tinyphysics
{

struct Particle
{    
    Point2D position;      //Current position
    Vector2D speed;        //Speed
    double weight;         //Weight used for gravitational attraction
    double color;          //Hue value
    double luminance;      //Minimum distance to attractor
};

class Demo3State: public State
{
public:
    
    Demo3State(Application* application);
    void onKeyPressed(sf::Keyboard::Key key, uint modifiers) override;
    void onMouseClicked(sf::Mouse::Button button, sf::Vector2f position) override;
    void onMouseMoved(sf::Vector2f position) override;
    void update(double dtime) override;
    void draw(double dtime) override;
    
private:
    //Attributes
    sf::Texture mTexture;
    std::vector<Particle> mParticles;
    std::vector<Particle> mAttractors;
    double mMaxSpeed;
    double mMinSpeed;
    double mRepulsionMagnitude;
    Point2D mRepulsionSource;
    sf::Shader mShader;
    bool mDrawField;
};


class FpsCounter: public State
{
public:
    FpsCounter(Application* application, State* parent);
    void update(double dtime) override;
    void draw(double dtime) override;
    
private:
    double mCumulatedTime;
    size_t mNumberOfFrames;
    double mFramesPerSecond;
    sf::Font mFont;
};


class Demo3: public Application
{
public:
    
    Demo3();
    ~Demo3();
    
private:
    State* mDefaultState;
    State* mFpsCounterState;
    
};


}

#endif /* TINYPHYSICS_SFML_DEMO3_DEMO_H */

