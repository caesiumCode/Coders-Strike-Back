#include "Move.hpp"

Move::Move() {
    target = sf::Vector2f(0.f, 0.f);
    thrust = 0;
}

Move::Move(sf::Vector2f p, int t) {
    target = p;
    thrust = t;
}

Move::Move(std::vector<float> u) {
    if (u.size() == 5) {
        target = sf::Vector2f(u[0], u[1]);
        thrust = u[2];
        
        if (u[3] > 0.5f)
            thrust = -2.f;
        else if (u[4] > 0.5f)
            thrust = -1.f;
    } else {
        target = sf::Vector2f(0.f, 0.f);
        thrust = 0;
    }
}
