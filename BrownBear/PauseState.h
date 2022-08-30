#pragma once
#include "State.h"
#include "Button.h"
class PauseState :
    public State
{
private:
    int wave;
    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text text1;
    sf::Text text2;
    sf::Music* music;
    std::map<std::string, Button*> buttons;
    float timer;

    void keybindsInit();
    void variableInit();
    void bgInit();
    void fontsInit();

    void txtInit();
    void btnInit();
    void updateBtn();
    void renderBtn(sf::RenderTarget* target);
    void updateInput(const float& dTime);
public:
    PauseState(sf::RenderWindow* window_, std::map<std::string, int>* keys_, std::stack<State*>* states_, sf::Music* music_);
    ~PauseState();

    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

