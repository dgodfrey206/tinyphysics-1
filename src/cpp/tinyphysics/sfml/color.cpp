#include "color.h"

namespace tinyphysics
{

sf::Vector3f convertRgbToHslColor(sf::Color color)
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

sf::Color convertHslToRgbColor(sf::Vector3f color)
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