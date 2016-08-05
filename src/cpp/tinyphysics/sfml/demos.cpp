#include "demos.h"

namespace tinyphysics
{

Demo1::Demo1():
        mState(State::Idle),
        mRectangles(),
        mClickedPoint(),
        mCurrentRectangle(Point2D(), Point2D()),
        mView(sf::FloatRect(0, 0, 800, 600))
{ }

void Demo1::handleInput(sf::Event& event)
{
    //Inherrit from basic handlers
    SfmlMainLoop::handleInput(event);
    
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
    }
    
    //Drawing state
    else if (mState == State::Drawing)
    {
        //Start drawing a rectangle
        if (event.type == event.MouseButtonPressed)
        {
            auto position = mWindow.mapPixelToCoords(
                    sf::Mouse::getPosition(mWindow));
            std::cout << "Start drawing rectangle from: " << position.x << ", " << position.y << std::endl;
            mState = State::DrawingOnGoing;
            mClickedPoint = Point2D(position.x, position.y);
            mCurrentRectangle = Rectangle2D(mClickedPoint, mClickedPoint);        
        }
        
        //Switch to click mode
        else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::C)))
        {
            mState = State::Clicking;
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
            mCurrentRectangle = Rectangle2D(mClickedPoint, Point2D(position.x, position.y));
        }
        //End rectangle
        else if (event.type == event.MouseButtonPressed)
        {
            auto position = mWindow.mapPixelToCoords(
                    sf::Mouse::getPosition(mWindow));
            std::cout << "End drawing rectangle to: " << position.x << ", " << position.y << std::endl;
            mState = State::Drawing;
            mCurrentRectangle = Rectangle2D(mClickedPoint, Point2D(position.x, position.y));
            mRectangles.push_back(mCurrentRectangle);            
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
    }
    else if (event.type == event.MouseWheelMoved)
    {
        if (event.mouseWheel.delta > 0)
            mView.zoom(1.01);
        else if (event.mouseWheel.delta < 0)
            mView.zoom(0.99);
    }
}

void Demo1::draw()
{   
    //Set view
    mWindow.setView(mView);

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
            //TODO fix: too many intersections found
            if (status)
            {
                for (size_t i = 0; i < algo.countIntersections(); ++i)
                {
                    Point2D point = algo.getIntersectionPoint(i);
                    sf::CircleShape circle(8.);
                    circle.setOutlineColor(sf::Color::Red);
                    circle.setOutlineThickness(1.);
                    sf::Color color(sf::Color::Red);
                    color.a = 100.;
                    circle.setFillColor(color);
                    circle.setPosition(point.getX() - 8., point.getY() - 8.);
                    mWindow.draw(circle);
                }
            }
        }
    }
    
    //Draw all rectangles
    for (const Rectangle2D& rect : mRectangles)
    {
        //Create SFML polygon
        sf::ConvexShape shape;
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(1);
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
    circle.setOutlineColor(sf::Color::Green);
    circle.setOutlineThickness(1.);
    sf::Color color(0, 255, 0, 100.);
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
    
}