#ifndef Move_hpp
#define Move_hpp

#include <SFML/Graphics.hpp>

class Move {
public:
    Move();
    Move(sf::Vector2f, int);
    
    sf::Vector2f target;
    int thrust;
};
#endif /* Move_hpp */
