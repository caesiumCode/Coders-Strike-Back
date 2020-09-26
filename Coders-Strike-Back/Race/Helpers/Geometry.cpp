#include "Geometry.hpp"

float norm(sf::Vector2f u) {
    return sqrt(u.x*u.x + u.y*u.y);
}

float norm2(sf::Vector2f u) {
    return u.x*u.x + u.y*u.y;
}

float scal(sf::Vector2f u, sf::Vector2f v) {
    return u.x*v.x + u.y*v.y;
}

sf::Vector2f orthonormal(sf::Vector2f u) {
    return (1.f / norm(u)) * sf::Vector2f(u.y, -u.x);
}

float absAngle(sf::Vector2f u) {
    if (u.x == 0.f && u.y == 0.f)
        return 0.f;
    else
        return atan2(u.y, u.x);
}

void reduceAngle(float& a) {
    if (a > M_PI)
        a = a - 2.f*M_PI;
    else if (a < -M_PI)
        a = a + 2.f*M_PI;
}
