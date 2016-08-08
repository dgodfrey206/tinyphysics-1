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

#ifndef TINYPHYSICS_SFML_APPLICATION_H
#define TINYPHYSICS_SFML_APPLICATION_H

//STL headers
#include <iostream>

//SFML headers
#include <SFML/Graphics.hpp>

namespace tinyphysics
{

class SfmlApplication
{
    
public:
    
    enum KeyModifier
    { 
        Alt = 1 << 0,
        Ctrl = 1 << 1,
        Shift = 1 << 2
    };
    
    /**
     * @brief Constructor.
     */
    
    SfmlApplication();
    
    /**
     * @brief Run the mainloop.
     */
    void run();
    
protected:
    
    /**
     * @brief Handle input from user.
     * 
     * By default this method only handle close event.
     * Clients may override this method to implement additional events.
     * 
     * @param event event been sent by user
     */
    virtual void handleInput(sf::Event& event);
    
    /**
     * @brief Draw items in window.
     * 
     * By default, this method draws nothing.
     * Clients may override it to draw anything.
     */
    virtual void draw();
    
    /**
     * @brief Update system being drawn in the SFML window.
     * 
     * By default, this method does nothing.
     * Clients may override it do to whatever necessary.
     * 
     * @param dtime elapsed time since previous call
     */
    virtual void update(double dtime);
    
    /**
     * @brief Slot for application closure.
     */
    virtual void onApplicationClose();
    
    /**
     * @brief Slot for mouse move event.
     * 
     * @param position mouse position
     */
    virtual void onMouseMove(sf::Vector2f position);
    
    /**
     * @brief Slot for keyboard pressed event.
     * 
     * @param key key pressed
     * @param modifiers activated (Alt, Ctrl, Shift or System)
     */
    virtual void onKeyPressed(sf::Keyboard::Key key, uint modifiers);
    
    /**
     * @brief Slot for mouse button pressed event.
     * 
     * @param button pressed button
     * @param position mouse position
     */
    virtual void onMouseClicked(sf::Mouse::Button button, 
                                sf::Vector2f position);
    
protected:
    
    //Attributes
    sf::RenderWindow mWindow; //SFML window
    
private:
    sf::Clock mClock;   //SFML clock
    
};

}

#endif /* TINYPHYSICS_SFML_APPLICATION_H */

