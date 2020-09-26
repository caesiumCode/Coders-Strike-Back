#ifndef Collision_hpp
#define Collision_hpp

#include "Entity.hpp"

class Collision {
public:
    Collision();
    Collision(Entity*, Entity*);
    
    Entity * e1;
    Entity * e2;
    float time;
};

Collision collide(Entity&, Entity&);

#endif /* Collision_hpp */
