#ifndef Entity_hpp
#define Entity_hpp

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
public:
    Entity();
    Entity(float, float, float, sf::Color);
    
private:
    sf::CircleShape EntityShape;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {target.draw(EntityShape);}
};

#endif /* Entity_hpp */
