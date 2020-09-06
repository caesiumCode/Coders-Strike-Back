#include "Program.hpp"
#include "Entity.hpp"

Program::Program() {
    window.create(sf::VideoMode(1000, 1000), "Coders Strike Back");
    window.setFramerateLimit(45);
}

void Program::run() {
    Entity entity(0, 0, 100, sf::Color::Red);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        window.draw(entity);

        window.display();
    }
}
