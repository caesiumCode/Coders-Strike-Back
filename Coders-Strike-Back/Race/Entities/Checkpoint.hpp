#ifndef Checkpoint_hpp
#define Checkpoint_hpp

#include "Entity.hpp"

class Checkpoint : public Entity {
public:
    Checkpoint();
    Checkpoint(float, float, float, sf::Color);
};

#endif /* Checkpoint_hpp */
