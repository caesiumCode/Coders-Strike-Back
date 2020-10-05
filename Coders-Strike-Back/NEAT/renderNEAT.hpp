#ifndef renderNEAT_hpp
#define renderNEAT_hpp

#include <SFML/Graphics.hpp>

#include "NEAT.hpp"

class renderNEAT : public NEAT {
public:
    renderNEAT();
    
    void render(sf::RenderWindow&);
};

#endif /* renderNEAT_hpp */
