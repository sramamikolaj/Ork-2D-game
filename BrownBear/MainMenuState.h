#pragma once
#include "State.h"
#include "Button.h"
#include "SettingsState.h"
#include "PregameState.h"
#include "PregameState.h"
class MainMenuState :
    public State
{
protected:
	sf::Texture bgTexture;
	sf::RectangleShape background;
	sf::Font font;
	float clickTimer;
	sf::Music* music;

	std::map<std::string, Button*> buttons;

	void variableInit();
	virtual void bgInit();
	void fontsInit();
	void keybindsInit();

	virtual void initButton();
	virtual void updateBtn();
	void renderBtn(sf::RenderTarget* target);
	void updateInput(const float& dTime);
	void updateCounter(const float& dTime);
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* keys, std::stack<State*>* states_, sf::Music* music);
	~MainMenuState();

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

