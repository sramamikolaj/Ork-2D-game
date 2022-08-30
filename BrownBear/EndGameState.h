#pragma once
#include "State.h"
#include "Button.h"
#include <fstream>
class EndGameState :
    public State
{
private:
    int wave;
    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text text1;
    sf::Text text2;
    sf::Text text3;
    std::fstream file;
    std::map<std::string, Button*> buttons;
    std::map<std::string, int> bestScores;
    std::string difficulty;
    sf::Music* music;
    void keybindsInit();
    void variableInit(int wave_);
    void getScores();
    void openFile();
    void bgInit();
    void fontsInit();
    void setDifficulty(int diff);
public:
    EndGameState(sf::RenderWindow* window_, std::map<std::string, int>* keys_, std::stack<State*>* states_, int wave, int diff, sf::Music* music_);
    void initMusic(sf::Music* music_);
    ~EndGameState();

    void txtInit();
    void btnInit();
    void updateBtn();
    void renderBtn(sf::RenderTarget* target);
    void updateInput(const float& dTime);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

