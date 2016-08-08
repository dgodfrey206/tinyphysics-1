#include "demo.h"

namespace tinyphysics
{

//==============================================================================
// DEMO1
//==============================================================================

//Demo1::Demo1():
//        mState(State::Idle),
//        mRectangles(),
//        mClickedPoints(),
//        mCurrentRectangle(Point2D(), Point2D()),
//        mView(sf::FloatRect(0, 0, 800, 600)),
//        mDrawingMode(DrawingMode::Rectangle2Points)
//{ }
//
//void Demo1::handleInput(sf::Event& event)
//{
//    //Inherrit from basic handlers
//    Application::handleInput(event);
//    
//    //Idle state
//    if (mState == State::Idle)
//    {
//        if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
//        {
//            mState = State::Drawing;
//            std::cout << "Enterring DRAWING mode" << std::endl;
//        }
//        else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::C)))
//        {
//            mState = State::Clicking;
//            std::cout << "Enterring CLICKING mode" << std::endl;
//            mClickedPoints.clear();
//        }
//    }
//    
//    //Clicking state
//    else if (mState == State::Clicking)
//    {
//        if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
//        {
//            mState = State::Drawing;
//            std::cout << "Enterring DRAWING mode" << std::endl;
//        }
//        else if (event.type == event.MouseButtonPressed)
//        {
//            mClickedPoints.clear();
//            auto position = mWindow.mapPixelToCoords(
//                    sf::Mouse::getPosition(mWindow));
//            std::cout << "Clicking at: " << position.x << ", " << position.y << std::endl;
//            mClickedPoints.emplace_back(position.x, position.y);
//        }
//    }
//    
//    //Drawing state
//    else if (mState == State::Drawing)
//    {
//        //Start drawing
//        if (event.type == event.MouseButtonPressed)
//        {
//            mClickedPoints.clear();
//            auto position = mWindow.mapPixelToCoords(
//                    sf::Mouse::getPosition(mWindow));
//            if (mDrawingMode == DrawingMode::Rectangle2Points)
//            {
//                std::cout << "Start drawing rectangle from: " << position.x << ", " << position.y << std::endl;
//                mState = State::DrawingOnGoing;
//                mClickedPoints.emplace_back(position.x, position.y);
//                mCurrentRectangle = Rectangle2D(mClickedPoints.front(), mClickedPoints.front());
//            }
//            else if (mDrawingMode == DrawingMode::Rectangle3Points)
//            {
//                std::cout << "Start drawing rectangle from: " << position.x << ", " << position.y << std::endl;
//                mState = State::DrawingOnGoing;
//                mClickedPoints.emplace_back(position.x, position.y);
//                mCurrentRectangle = Rectangle2D(mClickedPoints.front(), mClickedPoints.front(), mClickedPoints.front());
//            }
//        }
//        
//        //Start contextual menu
//        else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::M)))
//        {
//            std::cout << "DRAWING mode menu" << std::endl;
//            std::cout << "1 - Draw rectangle with two points\n";
//            std::cout << "2 - Draw rectangle with three points\n";
//            std::cout << "Enter your choice: ";
//            int answer;
//            std::cin >> answer;
//            switch (answer)
//            {
//                case 1:
//                    mDrawingMode = DrawingMode::Rectangle2Points;
//                    break;
//                case 2:
//                    mDrawingMode = DrawingMode::Rectangle3Points;
//                    break;
//                default:
//                    mDrawingMode = DrawingMode::Rectangle2Points;
//            }
//        }
//        
//        //Switch to click mode
//        else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::C)))
//        {
//            mState = State::Clicking;
//            mClickedPoints.clear();
//            std::cout << "Enterring CLICKING mode" << std::endl;
//        }
//        
//    }
//  
//    //Drawing on going
//    else if (mState == State::DrawingOnGoing)
//    {
//        //Update rectangle
//        if (event.type == event.MouseMoved)
//        {
//            auto position = mWindow.mapPixelToCoords(
//                        sf::Mouse::getPosition(mWindow));
//            if (mDrawingMode == Rectangle2Points)
//            {
//                mCurrentRectangle = Rectangle2D(mClickedPoints.front(), Point2D(position.x, position.y));
//            }
//            else if (mDrawingMode == Rectangle3Points)
//            {
//                if (mClickedPoints.size() == 1)
//                {
//                    mCurrentRectangle = Rectangle2D(mClickedPoints[0], Point2D(position.x, position.y), Point2D(position.x, position.y));
//                }
//                else if (mClickedPoints.size() == 2)
//                {
//                    mCurrentRectangle = Rectangle2D(mClickedPoints[0], mClickedPoints[1], Point2D(position.x, position.y));
//                }
//            }
//        }
//        //End rectangle
//        else if (event.type == event.MouseButtonPressed)
//        {
//            auto position = mWindow.mapPixelToCoords(
//                    sf::Mouse::getPosition(mWindow));
//            if (mDrawingMode == Rectangle2Points)
//            {
//                std::cout << "End drawing rectangle to: " << position.x << ", " << position.y << std::endl;
//                mState = State::Drawing;
//                mCurrentRectangle = Rectangle2D(mClickedPoints.front(), Point2D(position.x, position.y));
//                mRectangles.push_back(mCurrentRectangle);
//            }
//            else if (mDrawingMode == Rectangle3Points)
//            {
//                if (mClickedPoints.size() == 1)
//                {
//                    std::cout << "2nd point: " << position.x << ", " << position.y << std::endl;
//                    mClickedPoints.emplace_back(position.x, position.y);
//                    mCurrentRectangle = Rectangle2D(mClickedPoints[0], mClickedPoints[1], mClickedPoints[1]);
//                }
//                else if (mClickedPoints.size() == 2)
//                {
//                    std::cout << "End drawing rectangle to: " << position.x << ", " << position.y << std::endl;
//                    mState = State::Drawing;
//                    mCurrentRectangle = Rectangle2D(mClickedPoints[0], mClickedPoints[1], Point2D(position.x, position.y));
//                    mRectangles.push_back(mCurrentRectangle);
//                }
//            }
//        }
//        //Cancel drawing
//        else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
//        {
//            std::cout << "Cancel drawing" << std::endl;
//            mState = State::Drawing;
//        }
//    }
//    
//    //Apply whatever the mode - modify view
//    if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
//    {
//        mView.move(5, 0);
//    }
//    else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
//    {
//        mView.move(-5, 0);
//    }
//    if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
//    {
//        mView.move(0, -5);
//    }
//    else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
//    {
//        mView.move(0, 5);
//    }
//    else if ((event.type == event.KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Home)))
//    {
//        mView.setSize(800, 600);
//        mView.setCenter(400, 300);
//    }
//    else if (event.type == event.MouseWheelMoved)
//    {
//        if (event.mouseWheel.delta > 0)
//            mView.zoom(0.99);
//        else if (event.mouseWheel.delta < 0)
//            mView.zoom(1.01);
//    }
//}
//
//void Demo1::draw(double dtime)
//{   
//    //Set view
//    mWindow.setView(mView);
//    
//    //Local variable
//    std::vector<bool> selectedRectangles;
//
//    //Update on-going drawing
//    if (mState == State::DrawingOnGoing)
//    {
//        //Create SFML polygon
//        sf::ConvexShape shape;
//        shape.setFillColor(sf::Color::Transparent);
//        shape.setOutlineThickness(1);
//        shape.setPointCount(mCurrentRectangle.countPoints());
//        for (size_t i = 0; i < mCurrentRectangle.countPoints(); ++i)
//        {
//            Point2D point = mCurrentRectangle.getPoint(i);
//            shape.setPoint(i, sf::Vector2f(point.getX(), point.getY()));
//        }
//        mWindow.draw(shape);
//        
//        //Check intersection with existing rectangles
//        Intersection2D algo;
//        for (const Rectangle2D& rect : mRectangles)
//        {
//            bool status = algo.intersect(mCurrentRectangle, rect);
//            if (status)
//            {
//                for (size_t i = 0; i < algo.countIntersections(); ++i)
//                {
//                    Point2D point = algo.getIntersectionPoint(i);
//                    sf::Color color(200, 0, 0);
//                    sf::CircleShape circle(8.);
//                    circle.setOutlineColor(color);
//                    circle.setOutlineThickness(1.);
//                    color.a = 100.;
//                    circle.setFillColor(color);
//                    circle.setPosition(point.getX() - 8., point.getY() - 8.);
//                    mWindow.draw(circle);
//                }
//            }
//        }
//    }
//    else if (mState == State::Clicking)
//    {
//        //Loop over all rectangles to check which ones are selected
//        if (!mClickedPoints.empty())
//        {
//            for (const Rectangle2D& rect : mRectangles)
//            {
//                if (areCoincident(rect, mClickedPoints.front()))
//                    selectedRectangles.push_back(true);
//                else
//                    selectedRectangles.push_back(false);
//            }
//        }
//    }
//    
//    //Draw all rectangles
//    size_t j = 0;
//    for (const Rectangle2D& rect : mRectangles)
//    {
//        //Create SFML polygon
//        sf::ConvexShape shape;
//        shape.setFillColor(sf::Color::Transparent);
//        shape.setOutlineThickness(1);
//        if (!selectedRectangles.empty())
//        {
//            if (selectedRectangles[j++])
//            {
//                shape.setOutlineColor(sf::Color::Cyan);
//                shape.setOutlineThickness(2.);
//            }
//            
//            else
//                shape.setOutlineColor(sf::Color::White);
//        }
//        else
//        {
//            shape.setOutlineColor(sf::Color::White);
//        }
//        shape.setPointCount(rect.countPoints());
//        for (size_t i = 0; i < rect.countPoints(); ++i)
//        {
//            Point2D point = rect.getPoint(i);
//            shape.setPoint(i, sf::Vector2f(point.getX(), point.getY()));
//        }
//        mWindow.draw(shape);
//    }
//            
//    //Check intersections with existing rectangles
//    Intersection2D algo;
//    sf::CircleShape circle(8.);
//    sf::Color color(0, 200, 0);
//    circle.setOutlineColor(color);
//    circle.setOutlineThickness(1.);
//    color.a = 100;
//    circle.setFillColor(color);
//    for (size_t i = 0; i < mRectangles.size(); ++i)
//    {
//        for (size_t j = i+1; j < mRectangles.size(); ++j)
//        {
//            bool status = algo.intersect(mRectangles[i], mRectangles[j]);
//            if (status)
//            {
//                for (size_t i = 0; i < algo.countIntersections(); ++i)
//                {
//                    Point2D point = algo.getIntersectionPoint(i);
//                    circle.setPosition(point.getX() - 8., point.getY() - 8.);
//                    mWindow.draw(circle);
//                }
//            }
//        }
//    }
//}

}