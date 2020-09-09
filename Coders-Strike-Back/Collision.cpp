#include "Collision.hpp"

Collision::Collision() {
    id1 = 0;
    id2 = 0;
    time = 0.;
}

Collision::Collision(int a, int b, float t) {
    id1 = a;
    id2 = b;
    time = t;
}
