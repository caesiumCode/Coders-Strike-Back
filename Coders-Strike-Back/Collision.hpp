#ifndef Collision_hpp
#define Collision_hpp

class Collision {
public:
    Collision();
    Collision(int, int, float);
    
    int id1, id2;
    float time;
};

#endif /* Collision_hpp */
