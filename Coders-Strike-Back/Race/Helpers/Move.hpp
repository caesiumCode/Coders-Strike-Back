#ifndef Move_hpp
#define Move_hpp

#include <vector>

#include <SFML/Graphics.hpp>

#include "Env.hpp"

class Move {
public:
    Move();
    Move(sf::Vector2f, int);
    Move(std::vector<float>);
    
    sf::Vector2f target;
    int thrust; // -1 BOOST | -2 SHIELD
};
#endif /* Move_hpp */
