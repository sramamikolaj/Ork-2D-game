#pragma once
#include<Entity.h>

class State
{
protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int> keys;
	std::map<std::string, int> keybinds;
	std::map<std::string, sf::Texture> textures;
	bool quit;
	
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	virtual void keybindsInit() = 0;
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* keys, std::stack<State*>* states_);
	virtual ~State();
	const bool& getQuit();

	virtual void updateMousePosition();
	virtual void updateInput(const float& dTime) = 0;
	virtual void endState();
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

