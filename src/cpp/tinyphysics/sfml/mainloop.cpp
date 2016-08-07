#include "mainloop.h"

namespace tinyphysics
{

SfmlMainLoop::SfmlMainLoop():
        mWindow(),
        mClock()
{
    sf::ContextSettings settings;;
    settings.antialiasingLevel = 8;
    std::cout << "Anti-aliasing: " << settings.antialiasingLevel << std::endl;
    mWindow.create(sf::VideoMode(800, 600, 32), "Tiny Physics", sf::Style::Default, settings);
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

}

void SfmlMainLoop::update(double dtime)
{
    //
}
    
}
