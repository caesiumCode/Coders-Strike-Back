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
};

#endif /* Entity_hpp */
