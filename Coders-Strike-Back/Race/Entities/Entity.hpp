#ifndef Entity_hpp
#define Entity_hpp

#include <SFML/Graphics.hpp>
#include "Collision.hpp"
#include "Geometry.hpp"

class Entity {
public:
    Entity();
    Entity(float, float, float);
    Entity(sf::Vector2f, float);
    
    sf::Vector2f position;
    sf::Vector2f speed;
    float radius;
    int id;
};

Collision collide(const Entity&, const Entity&);

#endif /* Entity_hpp */
