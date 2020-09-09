#ifndef Program_hpp
#define Program_hpp

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Pod.hpp"

class Program {
public:
    Program();
    void run();

private:
    sf::RenderWindow window;
};

#endif /* Program_hpp */
