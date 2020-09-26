#include "Entity.hpp"

Entity::Entity() {
    position = sf::Vector2f(0.f, 0.f);
    radius = 0.f;
}

Entity::Entity(float posX, float posY, float r) {
    position = sf::Vector2f(posX, posY);
    radius = r;
}

Entity::Entity(sf::Vector2f pos, float r) {
    position = pos;
    radius = r;
}


Collision collide(const Entity& e1, const Entity& e2) {
    Collision collision(e1.id, e2.id);
    
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
