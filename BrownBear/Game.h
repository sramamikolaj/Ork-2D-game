#pragma once

#include<GameState.h>
#include"MainMenuState.h"
class Game
{
private:
	sf::RenderWindow *window;
	sf::Event event;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSetting;
	std::fstream file;
	std::fstream keyFile;
	std::map<string, int> settings;
	std::map<string, sf::Keyboard::Key> keybinds;
	sf::Music music;

	float dTime;
	sf::Clock dClock;
	std::stack<State*> states;
	

public:
	std::map<std::string, int> keys;
	Game();
	~Game();
	sf::Keyboard::Key getKey(string key);
	void stateInitializer();
	void updateDTime();
	void getSettings(fstream& toOpen, string type);
	void initMusic();
	void openFile();
	void windowInitializer();
	void keysInitializer();
	void updateSFMLEvents();
	void run();
	void update();
	void render();
};

