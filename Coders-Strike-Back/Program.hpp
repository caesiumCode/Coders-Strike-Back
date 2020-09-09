#ifndef Program_hpp
#define Program_hpp

#include <SFML/Graphics.hpp>

#include "Pod.hpp"
#include "Checkpoint.hpp"

class Program {
public:
    Program();
    void run();

private:
    sf::RenderWindow window;
};

#endif /* Program_hpp */
