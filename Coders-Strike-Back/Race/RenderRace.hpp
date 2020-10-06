#ifndef RenderRace_hpp
#define RenderRace_hpp

#include <iostream>

#include "Race.hpp"

class RenderRace : public Race {
public:
    RenderRace();
    RenderRace(int, int);
    
    void renderUpdate();
    void renderReset();
    void renderReset(unsigned int);
    
    // Render method
    void render(sf::RenderWindow&);
    void renderBackground(sf::RenderWindow&);
    void renderPlayers(sf::RenderWindow&);
    void renderInfo(sf::RenderWindow&);
    
    // Views
    sf::View raceView;
    
    // Resources
    sf::Font font;
    sf::Texture team1Texture, team2Texture, CPTexture, backgroundTexture, shieldTexture;
    
    // Shapes
    sf::RectangleShape background, CPShape, team1PodShape, team2PodShape, shieldShape;
    sf::Text numberingTxt, lapsTxt, turnsTxt, winnerTxt;
    
private:    
    void init();
    
    // Backup
    std::vector<Pod> team1_bu, team2_bu;
    std::vector<Checkpoint> checkpoints_bu;
    
    // Frame
    const int framePerTurn = 9;
    int frame;
};

#endif /* RenderRace_hpp */
