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
    
    // Initialise Checkpoint
    sf::RectangleShape CPShape;
    CPShape.setSize(sf::Vector2f(2.f*CP::RADIUS, 2.f*CP::RADIUS));
    CPShape.setOrigin(CP::RADIUS, CP::RADIUS);
    
    // Initialise numbering
    sf::Text numbering;
    numbering.setFont(font);
    numbering.setFillColor(sf::Color::White);
    numbering.setCharacterSize(CP::RADIUS*0.7f);
    
    for (int i = 0; i < checkpoints.size(); i++) {
        Checkpoint cp = checkpoints[i];
        
        // Draw checkpoint
        CPShape.setPosition(cp.position.x, cp.position.y);
        CPShape.setTexture(&CPTexture);
        target.draw(CPShape);
        
        // Draw numbering
        numbering.setString(std::to_string(i));
        sf::FloatRect textRect = numbering.getLocalBounds();
        numbering.setOrigin(textRect.left + textRect.width/2.f, textRect.top + textRect.height/2.f);
        numbering.setPosition(checkpoints[i].position);
        target.draw(numbering);
        
    }
    
    /* - - - Draw players - - - */
    sf::RectangleShape PodShape;
    PodShape.setSize(sf::Vector2f(2.f*POD::RADIUS, 2.f*POD::RADIUS));
    PodShape.setOrigin(POD::RADIUS, POD::RADIUS);
    
    // Team1
    PodShape.setTexture(&team1Texture);
    for (int i = 0; i < team1Size; i++) {
        Pod pod = team1[i];
                
        PodShape.setPosition(pod.position.x, pod.position.y);
        PodShape.setRotation(pod.angle * 180.f / M_PI + 90.f);
        
        target.draw(PodShape);
    }
    
    // Team2
    PodShape.setTexture(&team2Texture);
    for (int i = 0; i < team2Size; i++) {
        Pod pod = team2[i];
                
        PodShape.setPosition(pod.position.x, pod.position.y);
        PodShape.setRotation(pod.angle * 180.f / M_PI + 90.f);
        
        target.draw(PodShape);
    }
}
