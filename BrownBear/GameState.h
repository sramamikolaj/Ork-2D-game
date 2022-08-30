#pragma once
#include<list>
#include<State.h>
#include"Object.h"
#include"Entity.h"
#include"Player.h"
#include"Enemy.h"
#include"Item.h"
#include "EnemyRanged.h"
#include "Orb.h"
class GameState
	:public State
{
protected:
	Player* player;
	sf::Font font;
	sf::RectangleShape background;
	sf::RectangleShape playerPanel;
	sf::RectangleShape itemDescriptionRect;
	sf::Text itemDescription;

	sf::Text hpText;
	sf::Text asText;
	sf::Text msText;

	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music* music;

	sf::Shader core_shader;

	float difficulty;
	float escapeTimer;

	void playerInit();
	void soundInit();
	void keybindsInit();
	std::list<Item*> items;
	std::list<Enemy*> enemies;
	std::list<EnemyRanged*> rangedEnemies;
	std::list<Orb*> orbs;
	unsigned currentWave;

	void setDifficulty(int d);
	void initShader();
	void backgroundInit(sf::RenderTarget* target, int diff);
	void initMusic(sf::Music* music_);
	void fontsInit();
	void texturesInit();
	void initItemDescription();
	void initPlayerPanel();
	void dropItem(const int x, const int y);
	void updateItems(const float& dTime);
	void updateEnemies(const float& dTime, sf::Vector2u windowSize);
	void updateRangedEnemies(const float& dTime, sf::Vector2u windowSize);
	void printWave(sf::RenderTarget* target);
	void updateInput(const float& dTime);
	void checkDeath();
	void pickItem();

	//Render
	void renderItems(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter);
	void renderEnemies(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter);
	void renderRangedEnemies(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter);
	void renderPlayerPanelInfo(sf::RenderTarget* target);
	void initEnemies();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* keys, std::stack<State*>* states_, int diff, sf::Music* music_);
	~GameState();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target=nullptr);
};

