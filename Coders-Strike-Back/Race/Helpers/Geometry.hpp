#ifndef Geometry_hpp
#define Geometry_hpp

#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

float norm(sf::Vector2f);
float norm2(sf::Vector2f);

// Normalized Perpendicular vecteur (clockwise)
sf::Vector2f orthonormal(sf::Vector2f);

float absAngle(sf::Vector2f);

#endif /* Geometry_hpp */
