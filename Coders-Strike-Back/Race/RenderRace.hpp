#ifndef RenderRace_hpp
#define RenderRace_hpp

#include <iostream>

#include "Race.hpp"

class RenderRace : public Race {
public:
    RenderRace();
    RenderRace(unsigned int);
    
    // Resources
    sf::Font font;
    sf::Texture team1Texture, team2Texture, CPTexture, backgroundTexture;
    
    // Shapes
    sf::RectangleShape background, CPShape, team1PodShape, team2PodShape;
    sf::Text numbering;
    
    // Render method
    void render(sf::RenderWindow&);
};

#endif /* RenderRace_hpp */
