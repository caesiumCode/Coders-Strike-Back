#include "RenderRace.hpp"

RenderRace::RenderRace() : RenderRace((int)time(nullptr)) {
    
}

RenderRace::RenderRace(unsigned int seed) : Race(seed) {
    // Load font
    std::string path = resourcePath() + "Fonts/Sansation_Bold.ttf";
    if (!font.loadFromFile(path))
        std::cout << "Resource not found : " << path << std::endl;
    
    // Load textures
    path = resourcePath() + "Textures/Spaceship_Blue.png";
    if (!team1Texture.loadFromFile(path))
        std::cout << "Resource not found : " << path << std::endl;
    
    path = resourcePath() + "Textures/Spaceship_Red.png";
    if (!team2Texture.loadFromFile(path))
        std::cout << "Resource not found : " << path << std::endl;
    
    path = resourcePath() + "Textures/Space.png";
    if (!backgroundTexture.loadFromFile(path))
        std::cout << "Resource not found : " << path << std::endl;
    
    path = resourcePath() + "Textures/Checkpoint.png";
    if (!CPTexture.loadFromFile(path))
        std::cout << "Resource not found : " << path << std::endl;
}

void RenderRace::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    /* - - - Draw Background - - - */
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(RACE::WIDTH, RACE::HEIGHT));
    background.setTexture(&backgroundTexture);
    target.draw(background);
    
    /* - - - Draw checkpoints - - - */
    
    // Initialise numbering
    sf::Text numbering;
    numbering.setFont(font);
    numbering.setFillColor(sf::Color::White);
    numbering.setCharacterSize(CP::CHECKPOINT_RADIUS*0.7f);
    
    for (int i = 0; i < checkpoints.size(); i++) {
        Checkpoint cp = checkpoints[i];
        // Draw entity
        sf::RectangleShape entityShape;
        entityShape.setSize(sf::Vector2f(2.f*cp.radius, 2.f*cp.radius));
        entityShape.setOrigin(cp.radius, cp.radius);
        entityShape.setPosition(cp.position.x, cp.position.y);
        entityShape.setTexture(&CPTexture);
        
        target.draw(entityShape);
        
        // Draw numbering
        numbering.setString(std::to_string(i));
        sf::FloatRect textRect = numbering.getLocalBounds();
        numbering.setOrigin(textRect.left + textRect.width/2.f, textRect.top + textRect.height/2.f);
        numbering.setPosition(checkpoints[i].position);
        target.draw(numbering);
        
    }
    
    /* - - - Draw players - - - */
    
    // Team1
    for (int i = 0; i < team1Size; i++) {
        Pod pod = team1[i];
        sf::RectangleShape entityShape;
        
        entityShape.setSize(sf::Vector2f(2.f*pod.radius, 2.f*pod.radius));
        entityShape.setOrigin(pod.radius, pod.radius);
        
        entityShape.setPosition(pod.position.x, pod.position.y);
        entityShape.setTexture(&team1Texture);
        
        entityShape.setRotation(pod.angle * 180.f / M_PI + 90.f);
        
        target.draw(entityShape);
    }
    
    // Team2
    for (int i = 0; i < team2Size; i++) {
        Pod pod = team2[i];
        sf::RectangleShape entityShape;
        
        entityShape.setSize(sf::Vector2f(2.f*pod.radius, 2.f*pod.radius));
        entityShape.setOrigin(pod.radius, pod.radius);
        
        entityShape.setPosition(pod.position.x, pod.position.y);
        entityShape.setTexture(&team2Texture);
        
        entityShape.setRotation(pod.angle * 180.f / M_PI + 90.f);
        
        target.draw(entityShape);
    }
}
