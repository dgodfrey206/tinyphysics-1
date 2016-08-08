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

#ifndef TINYPHYSICS_SFML_DEMOS_H
#define TINYPHYSICS_SFML_DEMOS_H

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

//class Demo1: public Application
//{
//   
//public:
//    
//    enum State { Idle, Clicking, Drawing, DrawingOnGoing };
//    enum DrawingMode { Rectangle2Points, Rectangle3Points };
//    
//    /**
//     * @brief Constructor.
//     */
//    Demo1();
//
//private:
//    
//    /**
//     * @brief Handle input from user
//     * 
//     * @param event event being sent by user
//     */
//    void handleInput(sf::Event& event) override;
//    
//    /**
//     * @brief Draw rectangles.
//     * 
//     * @param dtime elapsed time since previous call
//     */
//    void draw(double dtime) override;
//    
//private:
//    
//    //Attributes
//    State mState;
//    std::vector<Rectangle2D> mRectangles;
//    std::vector<Point2D> mClickedPoints;
//    Rectangle2D mCurrentRectangle;
//    sf::View mView;
//    DrawingMode mDrawingMode;
//};

}

#endif /* TINYPHYSICS_SFML_DEMOS_H */

