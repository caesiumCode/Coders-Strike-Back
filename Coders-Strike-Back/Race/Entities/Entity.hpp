#ifndef Entity_hpp
#define Entity_hpp

#include <SFML/Graphics.hpp>
#include "Geometry.hpp"

class Entity {
public:
    Entity();
    Entity(float, float, float);
    Entity(sf::Vector2f, float);
    
    sf::Vector2f position;
    float radius;
};

#endif /* Entity_hpp */
