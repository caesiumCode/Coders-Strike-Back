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
    
    void check(int);
    
    void startTurn(const std::vector<Checkpoint>&);
    void partialTurn(float);
    void endTurn();
    
    
    // Physical state
    float angle;
    sf::Vector2f speed;
    
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
};

#endif /* Pod_hpp */
