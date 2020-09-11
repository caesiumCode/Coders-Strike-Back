#include "RenderRace.hpp"

RenderRace::RenderRace() : RenderRace((int)time(nullptr)) {
    
}

RenderRace::RenderRace(unsigned int seed) : Race(seed) {
    for (int i = 0; i < checkpoints.size(); i++)
        checkpoints[i].color = CHECKPOINT_COLOR;
    
    team1[0].color = TEAM1_COLOR;
    team1[1].color = TEAM1_COLOR;
    team2[0].color = TEAM2_COLOR;
    team2[1].color = TEAM2_COLOR;
    
    // Load resources
    std::string fontPath = resourcePath() + "Fonts/Sansation_Bold.ttf";
    if (!font.loadFromFile(fontPath))
        std::cout << "Resource not found : " << fontPath << std::endl;
}

void RenderRace::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw checkpoints
    sf::Text numbering;
    numbering.setFont(font);
    numbering.setFillColor(sf::Color::Black);
    numbering.setCharacterSize(CHECKPOINT_RADIUS);
    
    for (int i = 0; i < checkpoints.size(); i++) {
        // Draw entity
        target.draw(checkpoints[i]);
        
        // Draw numbering
        numbering.setString(std::to_string(i));
        sf::FloatRect textRect = numbering.getLocalBounds();
        numbering.setOrigin(textRect.left + textRect.width/2.f, textRect.top + textRect.height/2.f);
        numbering.setPosition(checkpoints[i].position);
        target.draw(numbering);
        
    }
    
    // Draw players
    target.draw(team1[0]);
    target.draw(team1[1]);
    target.draw(team2[0]);
    target.draw(team2[1]);
}
