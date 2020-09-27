#include "Program.hpp"

Program::Program() {
    // Set window
    window.create(windowDim(), "Coders Strike Back");
    window.setFramerateLimit(30);
    
    // Set view
    viewRace.reset(sf::FloatRect(-MARGIN, -MARGIN, RACE::WIDTH + 2*MARGIN, RACE::HEIGHT + 2*MARGIN));
    viewRace.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    window.setView(viewRace);
    
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
                    race.reset();
                
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
