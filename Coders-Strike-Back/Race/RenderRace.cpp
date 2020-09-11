#include "RenderRace.hpp"

RenderRace::RenderRace() : RenderRace((int)time(nullptr)) {
    
}

RenderRace::RenderRace(unsigned int seed) : Race(seed) {
    // Load resources
    std::string fontPath = resourcePath() + "Fonts/Sansation_Bold.ttf";
    if (!font.loadFromFile(fontPath))
        std::cout << "Resource not found : " << fontPath << std::endl;
}

void RenderRace::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    /* - - - Draw checkpoints - - - */
    
    // Initialise numbering
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
    
    /* - - - Draw players - - - */
    
    // Team1
    for (int i = 0; i < team1Size; i++)
        target.draw(team1[i]);
    
    // Team2
    for (int i = 0; i < team2Size; i++)
        target.draw(team2[i]);
}
