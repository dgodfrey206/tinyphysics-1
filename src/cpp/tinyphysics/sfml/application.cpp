#include "application.h"

namespace tinyphysics
{

//==============================================================================
// APPLICATION
//==============================================================================

Application::Application():
        mWindow(),
        mState(nullptr),
        mDefaultState(nullptr),
        mClock()
{
    sf::ContextSettings settings;;
    settings.antialiasingLevel = 8;
    mWindow.create(sf::VideoMode(800, 600, 32), "Tiny Physics", sf::Style::Default, settings);
    mWindow.setFramerateLimit(60);
    mWindow.setVerticalSyncEnabled(true);
    mDefaultState = new State(this);
    setState(mDefaultState);
}

Application::~Application()
{
    delete mDefaultState;
}

void Application::run()
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
        double dtime = mClock.restart().asSeconds();
        mState->update(dtime);

        //Draw
        mWindow.clear();
        mState->draw(dtime);
        mWindow.display();
    }
}

void Application::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::Closed)
    {
        mState->onApplicationClosed();
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        mState->onMouseMoved(
            mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)));
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        mState->onMouseClicked(event.mouseButton.button, 
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
        mState->onKeyPressed(event.key.code, modifier);
    }
}

sf::RenderWindow* Application::getRenderWindow()
{
    return &mWindow;
}

void Application::setState(State* state)
{
    mState = state;
}

const sf::Vector2f Application::getMousePosition() const
{
    return mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
}

//==============================================================================
// STATE
//==============================================================================

State::State(Application* application): mApplication(application), 
        mParent(nullptr)
{ }

State::State(Application* application, State* parent)
: mApplication(application), mParent(parent)
{ }

void State::draw(double dtime)
{ 
    if (mParent)
    {
        mParent->draw(dtime);
    }
}

void State::update(double dtime)
{ 
    if (mParent)
    {
        mParent->update(dtime);
    }
}

void State::onApplicationClosed()
{ 
    if (mParent)
    {
        mParent->onApplicationClosed();
    }
    mApplication->getRenderWindow()->close();
}

void State::onMouseMoved(sf::Vector2f position)
{ 
    if (mParent)
    {
        mParent->onMouseMoved(position);
    }
}

void State::onKeyPressed(sf::Keyboard::Key key, uint modifiers)
{ 
    if (mParent)
    {
        mParent->onKeyPressed(key, modifiers);
    }
}

void State::onMouseClicked(sf::Mouse::Button button, 
        sf::Vector2f position)
{ 
    if (mParent)
    {
        mParent->onMouseClicked(button, position);
    }
}

Application* State::getApplication()
{
    return mApplication;
}
    
}
