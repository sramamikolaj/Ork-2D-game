#include "GameStateField.h"
#include<sstream>

void GameStateField::backgroundInit(sf::RenderTarget* target)
{
	if (!textures["BACKGROUND"].loadFromFile("Resources/Images/Background/temp_bg.jpg"))
		throw "ERROR LOADING BACKGROUND";
	if (!textures["ENEMY1"].loadFromFile("Resources/Images/Sprites/Enemies/enemy1.png"))
		throw "ERROR LOADING ENEMY1";
	if (!textures["ENEMY2"].loadFromFile("Resources/Images/Sprites/Enemies/enemy2.png"))
		throw "ERROR LOADING ENEMY1";



	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	background.setTexture(&textures.at("BACKGROUND"));
}

GameStateField::GameStateField(sf::RenderWindow* window, std::map<std::string, int>* keys_, std::stack<State*>* states_):GameState(window, keys_, states_)
{
	
	backgroundInit(window);
	initEnemies();
}

GameStateField::~GameStateField()
{

}



void GameStateField::update(const float& dTime)
{
	updateMousePosition();
	updateInput(dTime);
	player->update(dTime);
	updateEnemies(dTime, window->getSize());
	checkDeath();
}

void GameStateField::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	target->draw(background);
	renderEnemies(target);
	player->render(target);
	

	//MOUSE POS////
	sf::Text mouseText;
	mouseText.setPosition(mousePosView.x, mousePosView.y - 10);
	mouseText.setCharacterSize(12);

	mouseText.setFont(font);
	std::stringstream str;
	str << mousePosView.x << " " << mousePosView.y;
	mouseText.setString(str.str());
	target->draw(mouseText);

	/////WAVE///
	sf::Text waveText;
	waveText.setPosition(0, 0);
	waveText.setCharacterSize(15);
	waveText.setFont(font);
	std::stringstream str1;
	str1 << "Obecna fala: " << " " << currentWave;
	waveText.setString(str1.str());
	target->draw(waveText);
	//////////////
}