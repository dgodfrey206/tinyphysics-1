#include "tinyphysics/sfml/demo2/demo.h"

namespace tinyphysics
{

//==============================================================================
// STATE
//==============================================================================

Demo2State::Demo2State(Application* application): State(application), 
        mHslColor(convertRgbToHslColor(sf::Color::Red)), 
        mTexture(),
        mUseTexture(false),
        mUseShader(false)
{
    mTexture.loadFromFile("/files/cedric/personnel/informatique/projets/"
                          "tinyphysics/data/textures/ball.png");
    mTexture.setSmooth(true);
}

void Demo2State::onKeyPressed(sf::Keyboard::Key key, uint modifiers)
{
    if (key == sf::Keyboard::Right)
    {
        //Increase hue
        mHslColor.x = mHslColor.x + 1.;
        if (mHslColor.x >= 360.) mHslColor.x -= 360.;
    }
    else if (key == sf::Keyboard::Left)
    {
        //Decrease hue
        mHslColor.x = mHslColor.x - 1.;
        if (mHslColor.x < 0.) mHslColor.x = (360. + mHslColor.x);
    }
    else if (key == sf::Keyboard::Up)
    {
        //Increase saturation
        mHslColor.y += 0.01;
        mHslColor.y = std::min(1.f, mHslColor.y);
    }
    else if (key == sf::Keyboard::Down)
    {
        //Increase saturation
        mHslColor.y -= 0.01;
        mHslColor.y = std::max(0.f, mHslColor.y);
    }
    else if (key == sf::Keyboard::PageUp)
    {
        //Increase luminance
        mHslColor.z += 0.01;
        mHslColor.z = std::min(1.f, mHslColor.z);
    }
    else if (key == sf::Keyboard::PageDown)
    {
        //Increase luminance
        mHslColor.z -= 0.01;
        mHslColor.z = std::max(0.f, mHslColor.z);
    }
    else if (key == sf::Keyboard::T)
    {
        //Toggle texture
        mUseTexture = !mUseTexture;
    }
    else if (key == sf::Keyboard::S)
    {
        //Toggle shader
        mUseShader = !mUseShader;
    }
}

void Demo2State::draw(double dtime)
{
    sf::Color color = convertHslToRgbColor(mHslColor);
    if (mUseTexture)
    {
        sf::Sprite sprite;
        sprite.setTexture(mTexture);
        sprite.setPosition(400 - 64, 300 - 64);
        sprite.setColor(color);
        if (mUseShader)
        {
            sf::Shader shader;
            shader.loadFromFile("/files/cedric/personnel/informatique/projets/"
                            "tinyphysics/data/shaders/passthrough-vertex.glsl",
                            "/files/cedric/personnel/informatique/projets/"
                            "tinyphysics/data/shaders/blur-fragment.glsl");
            shader.setParameter("blur_radius", 0.02);
            getApplication()->getRenderWindow()->draw(sprite, &shader);
        }
        else
        {
            getApplication()->getRenderWindow()->draw(sprite);
        }
    }
    else
    {
        sf::CircleShape circle(64.);
        circle.setPosition(400 - 64, 300 - 64);
        circle.setFillColor(color);
        getApplication()->getRenderWindow()->draw(circle);
    }
    std::stringstream ss;
    ss << "Hue: " << mHslColor.x << "\tSaturation: " << mHslColor.y << "\tLuminance = " << mHslColor.z << std::endl;
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf");
    sf::Text text(ss.str(), font);
    text.setCharacterSize(16);
    getApplication()->getRenderWindow()->draw(text);
    ss << "Red: " << int(color.r) << "\tGreen: " << int(color.g) << "\tBlue = " << int(color.b) << std::endl;
    text.setString(ss.str());
    getApplication()->getRenderWindow()->draw(text);
    ss << "Press T to toggle texture." << std::endl;
    text.setString(ss.str());    
    getApplication()->getRenderWindow()->draw(text);
    ss << "Press S to toggle blur shader." << std::endl;
    text.setString(ss.str());    
    getApplication()->getRenderWindow()->draw(text);
}

//==============================================================================
// DEMO2
//==============================================================================

Demo2::Demo2(): Application(), mDefaultState(new Demo2State(this))   
{
    setState(mDefaultState);
}

Demo2::~Demo2()
{
    delete mDefaultState;
}

} // namespace tinyphysics