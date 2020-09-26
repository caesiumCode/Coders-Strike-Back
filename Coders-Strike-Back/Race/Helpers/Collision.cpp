#include "Collision.hpp"

Collision::Collision() {
    e1 = nullptr;
    e2 = nullptr;
    time = -1.f;
}

Collision::Collision(Entity* a, Entity* b) {
    e1 = a;
    e2 = b;
    time = -1.f;
}


Collision collide(Entity& e1, Entity& e2) {
    Collision collision(&e1, &e2);
    
    float S = scal(e1.position - e2.position, e1.speed - e2.speed);
    
    if (S < 0.f) {
        float vtemp = norm2(e1.speed - e2.speed);
        float delta = 4.f*(S*S - vtemp*(norm2(e1.position - e2.position) - (e1.radius+e2.radius)*(e1.radius+e2.radius)));
        
        if (delta > 0.f) {
            collision.time = (-2.f*S - sqrt(delta))/(2.f*vtemp);
        } else {
            collision.time = -1.f;
        }
    } else {
        collision.time = -1.f;
    }
    
    return collision;
}
