//STL headers
#include <iostream>

//Tinyphysics
#include "tinyphysics/sfml/demos.h"
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
    Demo1 app;
    app.run();
    return 0;
}
