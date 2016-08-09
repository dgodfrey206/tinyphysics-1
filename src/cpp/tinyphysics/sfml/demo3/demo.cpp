#include "tinyphysics/sfml/demo3/demo.h"

namespace tinyphysics
{

//==============================================================================
// STATE
//==============================================================================

Demo3State::Demo3State(Application* application): State(application), 
        mTexture(), mParticles(), mAttractors(), mRepulsionMagnitude(0.), 
        mShader(), mDrawField(false)
{ 
    mTexture.loadFromFile("/files/cedric/personnel/informatique/projets/"
                          "tinyphysics/data/textures/fulldisk.png");
    mTexture.setSmooth(true);
    mShader.loadFromFile("/files/cedric/personnel/informatique/projets/"
                    "tinyphysics/data/shaders/passthrough-vertex.glsl",
                    "/files/cedric/personnel/informatique/projets/"
                    "tinyphysics/data/shaders/blur-fragment.glsl");
    mShader.setParameter("blur_radius", 0.1);

    
    //Generate particles
    for (size_t i = 0; i < 30000; ++i)
    {
        Particle particle;
        particle.position[0] = std::rand() % 800;
        particle.position[1] = std::rand() % 600;                
        particle.speed[0] = std::rand() % 200 / 10. - 10.;
        particle.speed[1] = std::rand() % 200 / 10. - 10.;
        particle.weight = 100.;
        particle.color = 0.;
        particle.luminance = 0.5;
        mParticles.push_back(particle);
    }
    
    //Create an attractor
    Particle attractor;
    attractor.position[0] = std::rand() % 800;
    attractor.position[1] = std::rand() % 600;
    attractor.weight = 1.e8;
    mAttractors.push_back(attractor);
    attractor.position[0] = std::rand() % 800;
    attractor.position[1] = std::rand() % 600;
    attractor.weight = 1.e8;
    mAttractors.push_back(attractor);
    attractor.position[0] = std::rand() % 800;
    attractor.position[1] = std::rand() % 600;
    attractor.weight = 1.e8;
    mAttractors.push_back(attractor);
    attractor.position[0] = std::rand() % 800;
    attractor.position[1] = std::rand() % 600;
    attractor.weight = 1.e8;
    mAttractors.push_back(attractor);
}

void Demo3State::onKeyPressed(sf::Keyboard::Key key, uint modifiers)
{

}

void Demo3State::onMouseClicked(sf::Mouse::Button button, sf::Vector2f position)
{
    if (button == sf::Mouse::Button::Left)
    {
        mRepulsionMagnitude = 1.e6;
        mRepulsionSource[0] = position.x;
        mRepulsionSource[1] = position.y;
    }
}

void Demo3State::onMouseMoved(sf::Vector2f position)
{
    Particle attractor;
    attractor.position[0] = position.x;
    attractor.position[1] = position.y;
    attractor.weight = 1.e8;
    mAttractors[0] = attractor;
}

void Demo3State::update(double dtime)
{
    //double gravity = 6.674e-11;
    double gravity = 1.e-4;
    mMaxSpeed = -1.e10;
    mMinSpeed = 1.e10;
    //Calculate displacement for each particle
    for (Particle& part : mParticles)
    {
        //Calculate all forces applied from attractors
        Vector2D forces;
        double minDistance = 100000.;
        for (Particle& att : mAttractors)
        {
            //Gravitational force
            double dist = distance(part.position, att.position);
            minDistance = std::min(minDistance, dist);
            double magnitude = gravity * part.weight * att.weight / dist;
            Vector2D force(part.position, att.position);
            force.normalize();
            force *= magnitude;
            forces += force;
        }
        //Calculate repulsion forces
        if (mRepulsionMagnitude > 0)
        {
            Vector2D force(mRepulsionSource, part.position);
            force.normalize();
            double dist = distance(part.position, mRepulsionSource);
            force *= mRepulsionMagnitude * std::exp(-0.0001 * dist * dist);
            forces += force;
        }
//        //Calculate damping
//        Vector2D force = -part.speed;
//        force.normalize();
//        force *= 1000.;
//        forces += force;
        //Apply Newton law (sum of forces = m.a) to update speed
        Vector2D accel = forces / part.weight;
        part.speed += accel * dtime;
        double speed = part.speed.getNorm();
        mMaxSpeed = std::max(mMaxSpeed, speed);
        mMinSpeed = std::min(mMinSpeed, speed);
        //Update position
        part.position[0] += part.speed[0] * dtime;
        part.position[1] += part.speed[1] * dtime;
        //Update color
//        part.color += 10 * dtime;
//        if (part.color >= 360)
//            part.color -= 360.;
        part.color = 180 + angleBetween(part.speed, Vector2D(1.0, 0.)) * 180. / PI;
        //Update luminance
        part.luminance = std::exp(-0.0001*minDistance*minDistance) + 0.25;
        part.luminance = std::min(1.0, part.luminance);
    }
    //Reset repulsion
    mRepulsionMagnitude = 0.;
}

void Demo3State::draw(double dtime)
{        
    if (mDrawField)
    {
        
    }
    else
    {
        //Draw particles
        double particleSize = 4.;
        //sf::CircleShape object(particleSize, 8);
        sf::Sprite object;
        object.setTexture(mTexture);
        object.scale(0.1, 0.1);
        sf::Vector3f hslColor;
        hslColor.y = 1.;
        sf::Color color;
        auto window = getApplication()->getRenderWindow();
        for (const Particle& part : mParticles)
        {
            object.setPosition(part.position[0] - particleSize, part.position[1] - particleSize);
            hslColor.x = part.color;
            hslColor.z = part.luminance;
            color = convertHslToRgbColor(hslColor);
            color.a = 127;
            //object.setFillColor(color);
            object.setColor(color);
            //getApplication()->getRenderWindow()->draw(circle, &mShader);
            window->draw(object);
        }
    }
}

//==============================================================================
// FPSCOUNTER STATE
//==============================================================================

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
    window->draw(text);
}

//==============================================================================
// DEMO3
//==============================================================================

Demo3::Demo3(): Application(), mDefaultState(new Demo3State(this))   
{
    mFpsCounterState = new FpsCounter(this, mDefaultState);
    setState(mFpsCounterState);
}

Demo3::~Demo3()
{
    delete mDefaultState;
    delete mFpsCounterState;
}

} // namespace tinyphysics