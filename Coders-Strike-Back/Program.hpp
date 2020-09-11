#ifndef Program_hpp
#define Program_hpp

#include <SFML/Graphics.hpp>

#include "Race.hpp"
#include "RenderRace.hpp"

class Program {
public:
    Program();
    void run();
    
private:
    sf::RenderWindow window;
    
    sf::View viewRace;
};

#endif /* Program_hpp */
