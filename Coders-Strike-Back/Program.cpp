#include "Program.hpp"

Program::Program() {
    // Set window
    window.create(windowDim(), "Coders Strike Back");
    window.setFramerateLimit(120);
    
    // Set variable
    play = true;
}

void Program::run() {
    RenderRace race;
    
    // Program loop
    while (window.isOpen()) {
        
        // Manage events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::R)
                    race.renderReset();
                
                if (event.key.code == sf::Keyboard::S)
                    race.renderReset(race.seed);
                
                if (event.key.code == sf::Keyboard::Space)
                    play = not play;
                
                if (event.key.code == sf::Keyboard::N)
                    if (not play)
                        race.renderUpdate();
            }
        }
        
        // Render
        window.clear();
        race.render(window);
        window.display();
        
        // Update
        if (play)
            race.renderUpdate();
    }
}
