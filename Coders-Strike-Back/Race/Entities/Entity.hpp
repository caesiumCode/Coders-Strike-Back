#ifndef Entity_hpp
#define Entity_hpp

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
public:
    Entity();
    Entity(float, float, float);
    Entity(sf::Vector2f, float);
    Entity(float, float, float, sf::Color);
    Entity(sf::Vector2f, float, sf::Color);
    
    sf::Vector2f position;
    float radius;
    sf::Color color;
            
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

#endif /* Entity_hpp */
