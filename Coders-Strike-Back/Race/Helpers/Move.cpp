#include "Move.hpp"

Move::Move() {
    target = sf::Vector2f(0., 0.);
    thrust = 0;
}

Move::Move(sf::Vector2f p, int t) {
    target = p;
    thrust = t;
}
