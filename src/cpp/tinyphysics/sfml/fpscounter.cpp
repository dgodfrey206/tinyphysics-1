#include "fpscounter.h"

//==============================================================================
// FPSCOUNTER STATE
//==============================================================================

namespace tinyphysics
{

FpsCounter::FpsCounter(Application* application, State* parent)
    :State(application, parent),
        mCumulatedTime(0.), mNumberOfFrames(0), mFramesPerSecond(0.), mFont()
{ 
    mFont.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf");
}

void FpsCounter::update(double dtime)
{
    mCumulatedTime += dtime;
    mNumberOfFrames += 1;
    if (mCumulatedTime >= 1.)
    {
        mFramesPerSecond = mNumberOfFrames / mCumulatedTime;
        mCumulatedTime = 0.;
        mNumberOfFrames = 0;
    }
    State::update(dtime);
}

void FpsCounter::draw(double dtime)
{
    State::draw(dtime);
    auto window = getApplication()->getRenderWindow();
    sf::Text text;
    std::stringstream ss;
    ss << std::setprecision(3) << mFramesPerSecond << " fps" << std::endl;
    text.setString(ss.str());
    text.setFont(mFont);
    text.setCharacterSize(16);
    auto view = window->getView();
    auto position = view.getCenter();
    position.x -= view.getSize().x / 2.;
    position.y -= view.getSize().y / 2.;
    text.setPosition(position.x, position.y);
    window->draw(text);
}

}