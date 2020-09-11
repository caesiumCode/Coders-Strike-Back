#include "Geometry.hpp"

float norm(sf::Vector2f u) {
    return sqrt(u.x*u.x + u.y*u.y);
}

float norm2(sf::Vector2f u) {
    return u.x*u.x + u.y*u.y;
}

sf::Vector2f orthonormal(sf::Vector2f u) {
    return (1.f / norm(u)) * sf::Vector2f(u.y, -u.x);
}
