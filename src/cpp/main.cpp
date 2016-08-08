//STL headers
#include <iostream>

//Tinyphysics
#include "tinyphysics/sfml/demo2/demo.h"
#include "tinyphysics/geometry/rectangle2d.h"

using namespace tinyphysics;

/**
 * @brief Main function
 * 
 * @param argc number of command line arguments
 * @param argv command line arguments
 * @return error code
 */
int main(int argc, char* argv[])
{
    std::cout << "TINY PHYSICS Engine" << std::endl;
    Demo3 app;
    app.run();
    return 0;
}
