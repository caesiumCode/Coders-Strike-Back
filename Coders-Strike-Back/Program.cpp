#include "Program.hpp"

Program::Program() {
    // Set window
    window.create(windowDim(), "Coders Strike Back");
    window.setFramerateLimit(30);
    
    // Set view
    viewRace.reset(sf::FloatRect(-MARGIN, -MARGIN, RACE::WIDTH + 2*MARGIN, RACE::HEIGHT + 2*MARGIN));
    viewRace.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    window.setView(viewRace);
}

void Program::run() {
    RenderRace race;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::R)
                    race.reset();
            }
        }

        window.clear();
        
        window.draw(race);

        window.display();
        
        race.update();
    }
}
