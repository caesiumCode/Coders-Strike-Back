#ifndef RenderRace_hpp
#define RenderRace_hpp

#include "iostream"

#include "Race.hpp"
#include "ResourceFile.hpp"

class RenderRace : public Race, public sf::Drawable {
public:
    RenderRace();
    RenderRace(unsigned int);
    
    // Constant variables
    const sf::Color CHECKPOINT_COLOR = sf::Color::White, TEAM1_COLOR = sf::Color::Blue, TEAM2_COLOR = sf::Color::Red;
    
    // Resources
    sf::Font font;
    
    // Render method ( ex: window.draw(renderrace) )
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif /* RenderRace_hpp */
