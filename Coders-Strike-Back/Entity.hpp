#ifndef Entity_hpp
#define Entity_hpp

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
public:
    Entity();
    Entity(float, float, float, sf::Color);
    
private:
    float x, y, radius;
    sf::Color color;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::CircleShape texture;
        texture.setRadius(radius);
        texture.setPosition(x - radius, y - radius);
        texture.setFillColor(color);
        
        target.draw(texture);
    }
};

#endif /* Entity_hpp */
