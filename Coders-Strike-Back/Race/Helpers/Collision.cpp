#include "Collision.hpp"

Collision::Collision() {
    id1 = 0;
    id2 = 0;
    time = -1.f;
}

Collision::Collision(int a, int b) {
    id1 = a;
    id2 = b;
    time = -1.f;
}
