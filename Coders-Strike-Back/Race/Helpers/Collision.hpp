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
    
    int type;
    
    Checkpoint * cp;
    std::vector<Pod*> pods;
    float time;
};

Collision collide(Checkpoint&, Pod&);
Collision collide(Pod&, Pod&);

#endif /* Collision_hpp */
