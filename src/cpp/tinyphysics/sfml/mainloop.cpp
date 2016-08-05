#include "mainloop.h"

namespace tinyphysics
{

SfmlMainLoop::SfmlMainLoop():
        mWindow(sf::VideoMode(800, 600, 32), "Tiny Physics"),        
        mClock()
{
    mWindow.setFramerateLimit(60);
    mWindow.setVerticalSyncEnabled(true);
}

void SfmlMainLoop::run()
{
    while (mWindow.isOpen())
    {
        //Manage events
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            handleInput(event);
        }

        //Update
        update(mClock.restart().asSeconds());

        //Draw
        mWindow.clear();
        draw();
        mWindow.display();
    }
}

void SfmlMainLoop::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::Closed)
        mWindow.close();    
}

void SfmlMainLoop::draw()
{
//        mWindow.draw(system);
//        mWindow.draw(text);
}

void SfmlMainLoop::update(double dtime)
{
    //
}
    
}
