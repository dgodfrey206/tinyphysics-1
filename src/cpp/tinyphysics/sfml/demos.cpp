#include "demos.h"

namespace tinyphysics
{

//==============================================================================
// DEMO1
//==============================================================================

Demo1::Demo1():
        mState(State::Idle),
        mRectangles(),
        mClickedPoints(),
        mCurrentRectangle(Point2D(), Point2D()),
        mView(sf::FloatRect(0, 0, 800, 600)),
        mDrawingMode(DrawingMode::Rectangle2Points)
{ }

void Demo1::handleInput(sf::Event& event)
{
    //Inherrit from basic handlers
    SfmlApplication::handleInput(event);
    
    //Idle state
    if (mState == State::Idle)
    {
        if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
        {
            mState = State::Drawing;
            std::cout << "Enterring DRAWING mode" << std::endl;
        }
        else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::C)))
        {
            mState = State::Clicking;
            std::cout << "Enterring CLICKING mode" << std::endl;
            mClickedPoints.clear();
        }
    }
    
    //Clicking state
    else if (mState == State::Clicking)
    {
        if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
        {
            mState = State::Drawing;
            std::cout << "Enterring DRAWING mode" << std::endl;
        }
        else if (event.type == event.MouseButtonPressed)
        {
            mClickedPoints.clear();
            auto position = mWindow.mapPixelToCoords(
                    sf::Mouse::getPosition(mWindow));
            std::cout << "Clicking at: " << position.x << ", " << position.y << std::endl;
            mClickedPoints.emplace_back(position.x, position.y);
        }
    }
    
    //Drawing state
    else if (mState == State::Drawing)
    {
        //Start drawing
        if (event.type == event.MouseButtonPressed)
        {
            mClickedPoints.clear();
            auto position = mWindow.mapPixelToCoords(
                    sf::Mouse::getPosition(mWindow));
            if (mDrawingMode == DrawingMode::Rectangle2Points)
            {
                std::cout << "Start drawing rectangle from: " << position.x << ", " << position.y << std::endl;
                mState = State::DrawingOnGoing;
                mClickedPoints.emplace_back(position.x, position.y);
                mCurrentRectangle = Rectangle2D(mClickedPoints.front(), mClickedPoints.front());
            }
            else if (mDrawingMode == DrawingMode::Rectangle3Points)
            {
                std::cout << "Start drawing rectangle from: " << position.x << ", " << position.y << std::endl;
                mState = State::DrawingOnGoing;
                mClickedPoints.emplace_back(position.x, position.y);
                mCurrentRectangle = Rectangle2D(mClickedPoints.front(), mClickedPoints.front(), mClickedPoints.front());
            }
        }
        
        //Start contextual menu
        else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::M)))
        {
            std::cout << "DRAWING mode menu" << std::endl;
            std::cout << "1 - Draw rectangle with two points\n";
            std::cout << "2 - Draw rectangle with three points\n";
            std::cout << "Enter your choice: ";
            int answer;
            std::cin >> answer;
            switch (answer)
            {
                case 1:
                    mDrawingMode = DrawingMode::Rectangle2Points;
                    break;
                case 2:
                    mDrawingMode = DrawingMode::Rectangle3Points;
                    break;
                default:
                    mDrawingMode = DrawingMode::Rectangle2Points;
            }
        }
        
        //Switch to click mode
        else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::C)))
        {
            mState = State::Clicking;
            mClickedPoints.clear();
            std::cout << "Enterring CLICKING mode" << std::endl;
        }
        
    }
  
    //Drawing on going
    else if (mState == State::DrawingOnGoing)
    {
        //Update rectangle
        if (event.type == event.MouseMoved)
        {
            auto position = mWindow.mapPixelToCoords(
                        sf::Mouse::getPosition(mWindow));
            if (mDrawingMode == Rectangle2Points)
            {
                mCurrentRectangle = Rectangle2D(mClickedPoints.front(), Point2D(position.x, position.y));
            }
            else if (mDrawingMode == Rectangle3Points)
            {
                if (mClickedPoints.size() == 1)
                {
                    mCurrentRectangle = Rectangle2D(mClickedPoints[0], Point2D(position.x, position.y), Point2D(position.x, position.y));
                }
                else if (mClickedPoints.size() == 2)
                {
                    mCurrentRectangle = Rectangle2D(mClickedPoints[0], mClickedPoints[1], Point2D(position.x, position.y));
                }
            }
        }
        //End rectangle
        else if (event.type == event.MouseButtonPressed)
        {
            auto position = mWindow.mapPixelToCoords(
                    sf::Mouse::getPosition(mWindow));
            if (mDrawingMode == Rectangle2Points)
            {
                std::cout << "End drawing rectangle to: " << position.x << ", " << position.y << std::endl;
                mState = State::Drawing;
                mCurrentRectangle = Rectangle2D(mClickedPoints.front(), Point2D(position.x, position.y));
                mRectangles.push_back(mCurrentRectangle);
            }
            else if (mDrawingMode == Rectangle3Points)
            {
                if (mClickedPoints.size() == 1)
                {
                    std::cout << "2nd point: " << position.x << ", " << position.y << std::endl;
                    mClickedPoints.emplace_back(position.x, position.y);
                    mCurrentRectangle = Rectangle2D(mClickedPoints[0], mClickedPoints[1], mClickedPoints[1]);
                }
                else if (mClickedPoints.size() == 2)
                {
                    std::cout << "End drawing rectangle to: " << position.x << ", " << position.y << std::endl;
                    mState = State::Drawing;
                    mCurrentRectangle = Rectangle2D(mClickedPoints[0], mClickedPoints[1], Point2D(position.x, position.y));
                    mRectangles.push_back(mCurrentRectangle);
                }
            }
        }
        //Cancel drawing
        else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
        {
            std::cout << "Cancel drawing" << std::endl;
            mState = State::Drawing;
        }
    }
    
    //Apply whatever the mode - modify view
    if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
    {
        mView.move(5, 0);
    }
    else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
    {
        mView.move(-5, 0);
    }
    if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
    {
        mView.move(0, -5);
    }
    else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
    {
        mView.move(0, 5);
    }
    else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Home)))
    {
        mView.setSize(800, 600);
        mView.setCenter(400, 300);
    }
    else if (event.type == event.MouseWheelMoved)
    {
        if (event.mouseWheel.delta > 0)
            mView.zoom(0.99);
        else if (event.mouseWheel.delta < 0)
            mView.zoom(1.01);
    }
}

void Demo1::draw()
{   
    //Set view
    mWindow.setView(mView);
    
    //Local variable
    std::vector<bool> selectedRectangles;

    //Update on-going drawing
    if (mState == State::DrawingOnGoing)
    {
        //Create SFML polygon
        sf::ConvexShape shape;
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(1);
        shape.setPointCount(mCurrentRectangle.countPoints());
        for (size_t i = 0; i < mCurrentRectangle.countPoints(); ++i)
        {
            Point2D point = mCurrentRectangle.getPoint(i);
            shape.setPoint(i, sf::Vector2f(point.getX(), point.getY()));
        }
        mWindow.draw(shape);
        
        //Check intersection with existing rectangles
        Intersection2D algo;
        for (const Rectangle2D& rect : mRectangles)
        {
            bool status = algo.intersect(mCurrentRectangle, rect);
            if (status)
            {
                for (size_t i = 0; i < algo.countIntersections(); ++i)
                {
                    Point2D point = algo.getIntersectionPoint(i);
                    sf::Color color(200, 0, 0);
                    sf::CircleShape circle(8.);
                    circle.setOutlineColor(color);
                    circle.setOutlineThickness(1.);
                    color.a = 100.;
                    circle.setFillColor(color);
                    circle.setPosition(point.getX() - 8., point.getY() - 8.);
                    mWindow.draw(circle);
                }
            }
        }
    }
    else if (mState == State::Clicking)
    {
        //Loop over all rectangles to check which ones are selected
        if (!mClickedPoints.empty())
        {
            for (const Rectangle2D& rect : mRectangles)
            {
                if (areCoincident(rect, mClickedPoints.front()))
                    selectedRectangles.push_back(true);
                else
                    selectedRectangles.push_back(false);
            }
        }
    }
    
    //Draw all rectangles
    size_t j = 0;
    for (const Rectangle2D& rect : mRectangles)
    {
        //Create SFML polygon
        sf::ConvexShape shape;
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(1);
        if (!selectedRectangles.empty())
        {
            if (selectedRectangles[j++])
            {
                shape.setOutlineColor(sf::Color::Cyan);
                shape.setOutlineThickness(2.);
            }
            
            else
                shape.setOutlineColor(sf::Color::White);
        }
        else
        {
            shape.setOutlineColor(sf::Color::White);
        }
        shape.setPointCount(rect.countPoints());
        for (size_t i = 0; i < rect.countPoints(); ++i)
        {
            Point2D point = rect.getPoint(i);
            shape.setPoint(i, sf::Vector2f(point.getX(), point.getY()));
        }
        mWindow.draw(shape);
    }
            
    //Check intersections with existing rectangles
    Intersection2D algo;
    sf::CircleShape circle(8.);
    sf::Color color(0, 200, 0);
    circle.setOutlineColor(color);
    circle.setOutlineThickness(1.);
    color.a = 100;
    circle.setFillColor(color);
    for (size_t i = 0; i < mRectangles.size(); ++i)
    {
        for (size_t j = i+1; j < mRectangles.size(); ++j)
        {
            bool status = algo.intersect(mRectangles[i], mRectangles[j]);
            if (status)
            {
                for (size_t i = 0; i < algo.countIntersections(); ++i)
                {
                    Point2D point = algo.getIntersectionPoint(i);
                    circle.setPosition(point.getX() - 8., point.getY() - 8.);
                    mWindow.draw(circle);
                }
            }
        }
    }
}

//==============================================================================
// DEMO2
//==============================================================================

Demo2::Demo2(): 
        mHslColor(convertRgbToHslColor(sf::Color::Red)),
        mTexture(),
        mUseTexture(false),
        mUseShader(false)
{
    mTexture.loadFromFile("/files/cedric/personnel/informatique/projets/"
                          "tinyphysics/data/textures/ball.png");
    mTexture.setSmooth(true);
}

void Demo2::draw()
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
            mWindow.draw(sprite, &shader);
        }
        else
        {
            mWindow.draw(sprite);
        }
    }
    else
    {
        sf::CircleShape circle(64.);
        circle.setPosition(400 - 64, 300 - 64);
        circle.setFillColor(color);
        mWindow.draw(circle);
    }
    std::stringstream ss;
    ss << "Hue: " << mHslColor.x << "\tSaturation: " << mHslColor.y << "\tLuminance = " << mHslColor.z << std::endl;
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf");
    sf::Text text(ss.str(), font);
    text.setCharacterSize(16);
    mWindow.draw(text);
    ss << "Red: " << int(color.r) << "\tGreen: " << int(color.g) << "\tBlue = " << int(color.b) << std::endl;
    text.setString(ss.str());
    mWindow.draw(text);
    ss << "Press T to toggle texture." << std::endl;
    text.setString(ss.str());    
    mWindow.draw(text);
    ss << "Press S to toggle blur shader." << std::endl;
    text.setString(ss.str());    
    mWindow.draw(text);
}

void Demo2::onKeyPressed(sf::Keyboard::Key key, uint modifiers)
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

sf::Vector3f Demo2::convertRgbToHslColor(sf::Color color) const
{
    sf::Vector3f hsl;
    hsl.x = 0.;
    hsl.y = 0.;
    hsl.z = 0.;
    double r = color.r / 255.;
    double g = color.g / 255.;
    double b = color.b / 255.;
    double cmax = std::max({r, g, b});
    double cmin = std::min({r, g, b});
    double delta = cmax - cmin;
    //Luminance
    hsl.z = (cmax - cmin) / 2.;
    //Saturation
    if (delta <= 0.)
    {
        hsl.y = 0.;
    }
    else
    {
        hsl.y = delta / (1. - std::abs(2. * hsl.z - 1.));
    }
    //Hue
    if (delta <= 0.)
    {
        hsl.x = 0.;
    }
    else if (cmax == r)
    {
        hsl.x = (g - b) / delta;
        while (hsl.x >= 6.) hsl.x -= 6.;
        hsl.x *= 60.;
        //hsl.x = 60. * (((g - b) / delta) % 6);
    }
    else if (cmax == g)
    {
        hsl.x = 60. * ((b - r) / delta + 2.);
    }
    else if (cmax == b)
    {
        hsl.x = 60. * ((r - g) / delta + 4.);
    }
    return hsl;
}

sf::Color Demo2::convertHslToRgbColor(sf::Vector3f color) const
{
    double c = (1. - std::abs(2. * color.z - 1)) * color.y;
    double x = (color.x / 60.);
    while (x >= 2.) x -= 2.;
    x = c * (1. - std::abs(x - 1));
    //double x = c * (1. - std::abs((color.x / 60.) % 2 - 1.));
    double m = color.z - c / 2;
    double r, g, b;
    if ((color.x >= 0.) && (color.x < 60.))
    {
        r = c;
        g = x;
        b = 0.;
    }
    else if ((color.x >= 60.) && (color.x < 120.))
    {
        r = x;
        g = c;
        b = 0.;
    }
    else if ((color.x >= 120.) && (color.x < 180.))
    {
        r = 0.;
        g = c;
        b = x;
    }
    else if ((color.x >= 180.) && (color.x < 240.))
    {
        r = 0.;
        g = x;
        b = c;
    }
    else if ((color.x >= 240.) && (color.x < 300.))
    {
        r = x;
        g = 0.;
        b = c;
    }
    else if ((color.x >= 300.) && (color.x < 360.))
    {
        r = c;
        g = 0.;
        b = x;
    }
    sf::Color rgb;
    rgb.r = (r + m) * 255;
    rgb.g = (g + m) * 255;
    rgb.b = (b + m) * 255;
    return rgb; 
}


}