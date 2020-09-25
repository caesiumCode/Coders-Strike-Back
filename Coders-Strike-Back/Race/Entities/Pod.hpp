#ifndef Pod_hpp
#define Pod_hpp

#include <vector>

#include "Entity.hpp"
#include "Checkpoint.hpp"
#include "Move.hpp"
#include "Geometry.hpp"

#include "Env.hpp"

class Pod : public Entity {
public:
    Pod();
    Pod(float, float, float);
    Pod(sf::Vector2f, float);
    
    void initRace(Checkpoint);
    
    void update(const std::vector<Checkpoint>&);
    
    
    // Physical state
    sf::Vector2f speed;
    float angle;
    
    // Special move
    int shieldCooldown;
    bool boost;
    
    // Race state
    int nextCheckpointId;
    int checkedCheckpoint;
    int timeout;
    
private:
    void init();
    
    // NeuralNet brain;
    
    Move nextMove(const std::vector<Checkpoint>&);
    void update(Move);
    
    
};

#endif /* Pod_hpp */
