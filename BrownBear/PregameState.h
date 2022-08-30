#pragma once
#include"State.h"
#include "Button.h"
#include "GameState.h"
class PregameState:public State
{
protected:
	sf::Texture bgTexture;
	sf::RectangleShape background;
	sf::Font font, bigFont;
	sf::Music* music;

	std::map<std::string, Button*> buttons;

	void variableInit();
	virtual void bgInit();
	void fontsInit();
	void keybindsInit();
	virtual void initButton();
	virtual void updateBtn();
	void updateInput(const float& dTime);
	void renderBtn(sf::RenderTarget* target);
public:
	PregameState(sf::RenderWindow* window, std::map<std::string, int>* keys, std::stack<State*>* states_, sf::Music* music);
	~PregameState();

	
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

