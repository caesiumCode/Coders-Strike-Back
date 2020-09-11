#include "Move.hpp"

Move::Move() {
    target = sf::Vector2f(0.f, 0.f);
    thrust = 0;
}

Move::Move(sf::Vector2f p, int t) {
    target = p;
    thrust = t;
}
