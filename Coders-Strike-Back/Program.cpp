#include "Program.hpp"

Program::Program() {
    window.create(sf::VideoMode(1800, 1000), "Coders Strike Back");
    window.setFramerateLimit(45);
    
    
}

void Program::run() {
    RenderRace race;
    
    viewRace.reset(sf::FloatRect(0, 0, race.WIDTH, race.HEIGHT));
    viewRace.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    window.setView(viewRace);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        window.draw(race);

        window.display();
    }
}
