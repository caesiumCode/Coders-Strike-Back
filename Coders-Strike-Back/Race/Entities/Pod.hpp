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
    Pod(float, float, float, sf::Color);
    Pod(sf::Vector2f, float, sf::Color);
    
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
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::CircleShape entityShape;
        
        entityShape.setOrigin(radius, radius);
        entityShape.setPointCount(3);
        
        entityShape.setRadius(radius);
        entityShape.setPosition(position.x, position.y);
        entityShape.setFillColor(color);
        
        entityShape.setRotation(angle * 180.f / M_PI + 90.f);
        
        target.draw(entityShape);
    }
    
private:
    
    // NeuralNet brain;
    
    Move nextMove(const std::vector<Checkpoint>&);
    void update(Move);
    
    
};

#endif /* Pod_hpp */
