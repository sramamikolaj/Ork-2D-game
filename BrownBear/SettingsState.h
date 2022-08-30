#pragma once
#include "State.h"
#include "Button.h"
#include <vector>
#include <fstream>
#include <map>
using namespace std;
class SettingsState :
    public State
{
private: 
	sf::Texture bgTexture;
	sf::RectangleShape background;
	sf::Font font;
	std::vector<sf::Vector2u> resolutions;
	std::map<std::string, Button*> buttons;
	std::map<std::string, Button*> graphicButtons;
	std::map<std::string, Button*> audioButtons;
	std::map<std::string, Button*> controlButtons;
	std::fstream file;
	std::fstream keyFile;
	std::map<string, int> settings;
	std::map<string, string> keybinds;
	short int settingsType;
	bool changesMade;
	float timer;
	std::string keyChange;
	

	void getSettings(fstream& toOpen, string type);
	void openFile();
	void variableInit();
	virtual void bgInit();
	void fontsInit();
	void initResolutions();
	void keybindsInit();
	void saveSettings();
	virtual void initButton();
	void updateGraphicBtn();
	void updateAudioBtn();
	void updateControlBtn();
	string getKey(const sf::Keyboard::Key& k);
	virtual void updateBtn();
	void renderBtn(sf::RenderTarget* target);
	void updateInput(const float& dTime);
	void printSettings(sf::RenderTarget* target);
	void setTimer(float toSet = 0.7);
	void updateTimer(const float& dTime);
public:
    SettingsState(sf::RenderWindow* window, std::map<std::string, int>* keys, std::stack<State*>* states_);
	~SettingsState();
	
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

