#include "RenderRace.hpp"

RenderRace::RenderRace() : RenderRace((int)time(nullptr)) {
    frame = -1;
}

RenderRace::RenderRace(unsigned int seed) : Race(seed) {
    /* - - - Load resources - - -*/
    
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
    
    /* - - - Initialise shapes - - -*/
    
    // Background
    background.setSize(sf::Vector2f(RACE::WIDTH, RACE::HEIGHT));
    background.setTexture(&backgroundTexture);
    
    // Pods
    team1PodShape.setSize(sf::Vector2f(2.f*POD::RADIUS, 2.f*POD::RADIUS));
    team1PodShape.setOrigin(POD::RADIUS, POD::RADIUS);
    team1PodShape.setTexture(&team1Texture);
    
    team2PodShape.setSize(sf::Vector2f(2.f*POD::RADIUS, 2.f*POD::RADIUS));
    team2PodShape.setOrigin(POD::RADIUS, POD::RADIUS);
    team2PodShape.setTexture(&team2Texture);
    
    // Checkpoints
    numbering.setFont(font);
    numbering.setFillColor(sf::Color::White);
    numbering.setCharacterSize(CP::RADIUS*0.7f);
    
    CPShape.setSize(sf::Vector2f(2.f*CP::RADIUS, 2.f*CP::RADIUS));
    CPShape.setOrigin(CP::RADIUS, CP::RADIUS);
    CPShape.setTexture(&CPTexture);
    
    /* - - - Initialise Backup - - - */
    
    checkpoints_bu = checkpoints;
    team1_bu = team1;
    team2_bu = team2;
}

void RenderRace::render(sf::RenderWindow& window) {
    /* - - - Draw Background - - - */
    window.draw(background);
    
    /* - - - Draw checkpoints - - - */
    for (int i = 0; i < checkpoints.size(); i++) {
        Checkpoint cp = checkpoints[i];
        
        // Draw checkpoint
        CPShape.setPosition(cp.position);
        CPShape.setTexture(&CPTexture);
        window.draw(CPShape);
        
        // Draw numbering
        numbering.setString(std::to_string(i));
        sf::FloatRect textRect = numbering.getLocalBounds();
        numbering.setOrigin(textRect.left + textRect.width/2.f, textRect.top + textRect.height/2.f);
        numbering.setPosition(checkpoints[i].position);
        window.draw(numbering);
        
    }
    
    /* - - - Draw players - - - */
    // interpolation parameter
    float t = (float)frame/framePerTurn;
    
    // Team1
    for (int i = 0; i < team1Size; i++) {
        Pod pod = team1[i];
        Pod pod_bu = team1_bu[i];
        
        team1PodShape.setPosition(pod_bu.position + t*(pod.position - pod_bu.position));
        
        float diffAngle = reduceAngle(pod.angle - pod_bu.angle);
        team1PodShape.setRotation((pod_bu.angle + t*diffAngle) * 180.f / M_PI + 90.f);
        
        window.draw(team1PodShape);
    }
    
    // Team2
    for (int i = 0; i < team2Size; i++) {
        Pod pod = team2[i];
        Pod pod_bu = team2_bu[i];
                
        team2PodShape.setPosition(pod_bu.position + t*(pod.position - pod_bu.position));
        
        float diffAngle = reduceAngle(pod.angle - pod_bu.angle);
        team2PodShape.setRotation((pod_bu.angle + t*diffAngle) * 180.f / M_PI + 90.f);
        
        window.draw(team2PodShape);
    }
}

void RenderRace::renderUpdate() {
    frame = (frame+1)%framePerTurn;
    if (frame == 0) {
        checkpoints_bu = checkpoints;
        team1_bu = team1;
        team2_bu = team2;
        update();
    }
}

void RenderRace::renderReset() {
    frame = -1;
    
    reset();
    
    checkpoints_bu = checkpoints;
    team1_bu = team1;
    team2_bu = team2;
}

void RenderRace::renderReset(unsigned int s) {
    frame = -1;
    
    reset(s);
    
    checkpoints_bu = checkpoints;
    team1_bu = team1;
    team2_bu = team2;
}
