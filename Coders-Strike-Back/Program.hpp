#ifndef Program_hpp
#define Program_hpp

#include <SFML/Graphics.hpp>

#include "Race.hpp"
#include "RenderRace.hpp"
#include "ResourceFile.hpp"

#include "Env.hpp"

class Program {
public:
    Program();
    void run();
    
    bool play;
    
private:
    sf::RenderWindow window;
    
    const int MARGIN = 1000;
    sf::View viewRace;
};

#endif /* Program_hpp */
