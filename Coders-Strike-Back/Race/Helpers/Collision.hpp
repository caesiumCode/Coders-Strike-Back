#ifndef Collision_hpp
#define Collision_hpp

#include <vector>

#include "Pod.hpp"
#include "Checkpoint.hpp"

class Collision {
public:
    Collision();
    Collision(Checkpoint*, Pod*);
    Collision(Pod*, Pod*);
    
    int type; // 0 : CP collision | 1 : pod collision
    
    Checkpoint * cp;
    std::vector<Pod*> pods;
    float time;
};

Collision collide(Checkpoint&, Pod&);
Collision collide(Pod&, Pod&);

void bounce(Collision);

#endif /* Collision_hpp */
