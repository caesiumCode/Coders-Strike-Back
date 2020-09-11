#ifndef Pod_hpp
#define Pod_hpp

#include "Entity.hpp"

class Pod : public Entity {
public:
    Pod();
    Pod(float, float, float);
    Pod(sf::Vector2f, float);
    
    // Physical state
    sf::Vector2f speed;
    int thrust;
    
    // Special move
    int shieldCooldown;
    bool boost;
    
    // Race state
    int nextCheckpointId;
    int checkedCheckpoint;
    int timeout;
    
    // NeuralNet brain;
};

#endif /* Pod_hpp */
