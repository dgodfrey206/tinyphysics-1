#include "tinyphysics/sfml/demo4/demo.h"

namespace tinyphysics
{

//==============================================================================
// STATE
//==============================================================================

Demo4State::Demo4State(Application* application): State(application), 
        mSpaceBackground(), mView(sf::FloatRect(0, 0, 800, 600)),
        mBackgroundTextRect(sf::Vector2f(0., 0.)), mBackgroundSprite(),
        mFighterTextures(), mFighterSprite()
{ 
    mSpaceBackground.loadFromFile("/files/cedric/personnel/informatique/projets/"
                          "tinyphysics/data/textures/space-field-1.jpg");
    mSpaceBackground.setSmooth(true);
    mSpaceBackground.setRepeated(true);
    mBackgroundSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
    mBackgroundSprite.setTexture(mSpaceBackground);
    //Fighter texture is 95*151
    mFighterTextures.resize(11);
    mFighterTextures[5].loadFromFile("/files/cedric/personnel/informatique/"
            "projets/tinyphysics/data/textures/fighter-01-straight.png");
    mFighterTextures[5].setSmooth(true);
    mFighterSprite.setTexture(mFighterTextures[5]);
    mFighterSprite.setPosition(400 - 95/2., 300 - 151/2.);
}

void Demo4State::onKeyPressed(sf::Keyboard::Key key, uint modifiers)
{
    sf::Vector2f position = mFighterSprite.getPosition();
    sf::Vector2f move;
    double fighterSpeed = 10.;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        move.x -= fighterSpeed;   
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move.x += fighterSpeed;
    }    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        move.y -= fighterSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        move.y += fighterSpeed;
    }
    mFighterSprite.setPosition(position + move);
}

void Demo4State::onMouseClicked(sf::Mouse::Button button, sf::Vector2f position)
{

}

void Demo4State::onMouseMoved(sf::Vector2f position)
{

}

void Demo4State::update(double dtime)
{
    //Update background sprite
    double gameSpeed = 50.; //move 50 pixel / second
    sf::Vector2f gameOffset(0., -gameSpeed * dtime);
    mBackgroundTextRect += gameOffset;
    mBackgroundSprite.setTextureRect(sf::IntRect(mBackgroundTextRect.x, 
            mBackgroundTextRect.y, 800, 600));
    
    //Update fighter position
    double fighterSpeed = 600.;
    sf::Vector2f mousePosition = getApplication()->getMousePosition();
    sf::Vector2f currentPosition = mFighterSprite.getPosition();
    sf::Vector2f center = currentPosition;
    center.x += 95./2.;
    center.y += 151./2.;
    sf::Vector2f move = mousePosition - center;
    double distance = std::sqrt(move.x * move.x + move.y * move.y);
    if (distance >= 5.)
    {
        move.x = move.x / distance * fighterSpeed * dtime;
        move.y = move.y / distance * fighterSpeed * dtime;
        sf::Vector2f destination = currentPosition + move;
        destination.x = std::max(0.f, destination.x);
        destination.x = std::min(800.f-95.f, destination.x);
        destination.y = std::max(0.f, destination.y);
        destination.y = std::min(600.f-151.f, destination.y);
        mFighterSprite.setPosition(destination);
    }  
}

void Demo4State::draw(double dtime)
{        
    //Get window
    auto window = getApplication()->getRenderWindow();
    //window->setMouseCursorVisible(false);
    
    //Update view
    window->setView(mView);
        
    //Draw backgound
    window->draw(mBackgroundSprite);
    
    //Draw fighter
    window->draw(mFighterSprite);
    
}

//==============================================================================
// DEMO4
//==============================================================================

Demo4::Demo4(): Application(), mDefaultState(new Demo4State(this))
{
    mFpsCounterState = new FpsCounter(this, mDefaultState);
    setState(mFpsCounterState);
}

Demo4::~Demo4()
{
    delete mDefaultState;
    delete mFpsCounterState;
}

} // namespace tinyphysics