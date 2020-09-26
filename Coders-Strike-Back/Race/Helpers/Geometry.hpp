#ifndef Geometry_hpp
#define Geometry_hpp

#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

float norm(sf::Vector2f);
float norm2(sf::Vector2f);
float scal(sf::Vector2f, sf::Vector2f);

// Normalized orthogonal vecteur (clockwise)
sf::Vector2f orthonormal(sf::Vector2f);

float absAngle(sf::Vector2f);
void reduceAngle(float&);

#endif /* Geometry_hpp */
