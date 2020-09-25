#include "Program.hpp"

Program::Program() {
    // Set window
    window.create(windowDim(), "Coders Strike Back");
    window.setFramerateLimit(45);
    
    // Set view
    viewRace.reset(sf::FloatRect(0, 0, Race::WIDTH, Race::HEIGHT));
    viewRace.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    window.setView(viewRace);
}

void Program::run() {
    RenderRace race;
    
    sf::Vector2f u = sf::Vector2f(1.f, -1.f);
    std::cout << absAngle(u) << std::endl;
    
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
