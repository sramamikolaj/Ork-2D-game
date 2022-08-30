#pragma once
#include "GameState.h"
#include<list>
class GameStateField :
    public GameState
{
protected: 
    sf::RectangleShape background;
    
public:
    GameStateField(sf::RenderWindow* window, std::map<std::string, int>* keys_, std::stack<State*>* states_);
    ~GameStateField();

    

    

    void backgroundInit(sf::RenderTarget* target);
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target = nullptr);
};

