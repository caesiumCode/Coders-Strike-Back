#ifndef RenderRace_hpp
#define RenderRace_hpp

#include <iostream>

#include "Race.hpp"

class RenderRace : public Race, public sf::Drawable {
public:
    RenderRace();
    RenderRace(unsigned int);
    
    // Resources
    sf::Font font;
    
    // Render method ( ex: window.draw(renderrace) )
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif /* RenderRace_hpp */
