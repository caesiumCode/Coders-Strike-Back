#ifndef Entity_hpp
#define Entity_hpp

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
public:
    Entity();
    Entity(float, float, float, sf::Color);
    
    float x, y, radius;
    sf::Color color;
            
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::CircleShape entityShape;
        
        entityShape.setOrigin(radius, radius);
        entityShape.setPointCount(64);
        
        entityShape.setRadius(radius);
        entityShape.setPosition(x, y);
        entityShape.setFillColor(color);
        
        target.draw(entityShape);
    }
};

#endif /* Entity_hpp */
