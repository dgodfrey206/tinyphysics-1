#include "application.h"

namespace tinyphysics
{

SfmlApplication::SfmlApplication():
        mWindow(),
        mClock()
{
    sf::ContextSettings settings;;
    settings.antialiasingLevel = 8;
    mWindow.create(sf::VideoMode(800, 600, 32), "Tiny Physics", sf::Style::Default, settings);
    mWindow.setFramerateLimit(60);
    mWindow.setVerticalSyncEnabled(true);
}

void SfmlApplication::run()
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

void SfmlApplication::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::Closed)
        onApplicationClose();
    else if (event.type == sf::Event::MouseMoved)
        onMouseMove(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)));
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        onMouseClicked(event.mouseButton.button, 
                sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
    }
    else if (event.type == event.KeyPressed)
    {
        int modifier = 0;
        if (event.key.alt)
            modifier |= KeyModifier::Alt;
        if (event.key.shift)
            modifier |= KeyModifier::Shift;
        if (event.key.control)
            modifier |= KeyModifier::Ctrl;        
        onKeyPressed(event.key.code, modifier);
    }
}

void SfmlApplication::draw()
{ }

void SfmlApplication::update(double dtime)
{ }

void SfmlApplication::onApplicationClose()
{
    mWindow.close();
}

void SfmlApplication::onMouseMove(sf::Vector2f position)
{ }

void SfmlApplication::onKeyPressed(sf::Keyboard::Key key, uint modifiers)
{
//    std::cout << "key = " << key << std::endl;
//    std::cout << "modifiers = " << modifiers << std::endl;
//    std::cout << (modifiers & KeyModifier::Alt) << std::endl;
//    std::cout << (modifiers & KeyModifier::Ctrl) << std::endl;
//    std::cout << (modifiers & KeyModifier::Shift) << std::endl;
}

void SfmlApplication::onMouseClicked(sf::Mouse::Button button, 
        sf::Vector2f position)
{
//    std::cout << button << std::endl;
//    std::cout << position.x << std::endl;
//    std::cout << position.y << std::endl;
}
    
}
