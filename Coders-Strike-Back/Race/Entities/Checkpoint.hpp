#ifndef Checkpoint_hpp
#define Checkpoint_hpp

#include "Entity.hpp"

class Checkpoint : public Entity {
public:
    Checkpoint();
    Checkpoint(float, float, float);
    Checkpoint(sf::Vector2f, float);
    Checkpoint(float, float, float, sf::Color);
    Checkpoint(sf::Vector2f, float, sf::Color);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::CircleShape entityShape;
        
        entityShape.setOrigin(radius, radius);
        entityShape.setPointCount(64);
        
        entityShape.setRadius(radius);
        entityShape.setPosition(position.x, position.y);
        entityShape.setFillColor(color);
        
        target.draw(entityShape);
    }
};

#endif /* Checkpoint_hpp */
