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

class Application;

//==============================================================================
// STATE
//==============================================================================

/**
 * @brief Implements states that will manage interactions with user.
 * Each application has only a single state activated but State uses decorator 
 * design pattern so that it's possible to virtually have multiple states 
 * activated.
 */
class State
{
public:
    
    /**
     * @brief Constructor.
     * 
     * State object is attached to given application.
     * 
     * @param application attached application.
     */
    State(Application* application);
    
    /**
     * @brief Constructor.
     * 
     * @param parent state to be decorated.
     */
    State(Application* application, State* parent);
    
    /**
     * @brief Destructor.
     */
    virtual ~State() = default;
    
    /**
     * @brief Copy constructor.
     * 
     * @param other object to be copied from
     */
    State(const State& other) = default;
    
    /**
     * @brief Move constructor.
     * 
     * @param other object to be moved from
     */
    State(State&& other) = default;
    
    /**
     * @brief Assignment operator
     * 
     * @param other object to be assigned from
     */
    State& operator=(const State& other) = default;
    
    /**
     * @brief Move assignment operator
     * 
     * @param other object to be moved assigned from
     */
    State& operator=(State&& other) = default;

    /**
     * @brief Slot for application closure.
     */
    virtual void onApplicationClosed();
    
    /**
     * @brief Slot for mouse move event.
     * 
     * @param position mouse position
     */
    virtual void onMouseMoved(sf::Vector2f position);
    
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
    
    /**
     * @brief Draw items in window.
     * 
     * By default, this method draws nothing.
     * Clients may override it to draw anything.
     * 
     * @param dtime elapsed time since previous call
     */
    virtual void draw(double dtime);
    
    /**
     * @brief Update system being drawn in the SFML window.
     * 
     * By default, this method does nothing.
     * Clients may override it do to whatever necessary.
     * 
     * @param dtime elapsed time since previous call
     */
    virtual void update(double dtime);
    
protected:
    
    /**
     * @brief Return attached application.
     */
    Application* getApplication();
    
private:
    
    //Attributes
    Application* mApplication;
    State* mParent;
};

//==============================================================================
// APPLICATION
//==============================================================================

class Application
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
    
    Application();
    
    /**
     * @brief Destructor.
     */
    virtual ~Application();
    
    /**
     * @brief Run the mainloop.
     */
    void run();
    
    /**
     * @brief Get render window object.
     */
    sf::RenderWindow* getRenderWindow();

    /**
     * @brief Set state
     * @param state state
     */
    void setState(State* state);
        
private:
    
    /**
     * @brief Deactivate few methods
     */
    Application(const Application& other) = delete;
    Application(Application&& other) = delete;
    Application& operator=(const Application& other) = delete;
    Application& operator=(Application&& other) = delete;
    
    /**
     * @brief Handle input from user.
     * 
     * By default this method only handle close event.
     * Clients may override this method to implement additional events.
     * 
     * @param event event been sent by user
     */
    void handleInput(sf::Event& event);

    //Attributes
    sf::RenderWindow mWindow; //SFML window
    State* mState;            //Active state
    State* mDefaultState;     //Default state
    sf::Clock mClock;         //SFML clock
};

}

#endif /* TINYPHYSICS_SFML_APPLICATION_H */

