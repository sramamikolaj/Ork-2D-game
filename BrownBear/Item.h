#pragma once
#include"Entity.h"
#include"string"
class Item
{
private:
	sf::Sprite* sprite;
	sf::FloatRect box;
	sf::Texture texture;


	void initBox();
	void initSprite(const int x, const int y);

	float lifetime;
	float timer;
	float animTimer;
	short animCounter;
	short int type;
	short int valueAdded;

public:
	Item(const int x, const int y, const int type_, const int value_, sf::Texture& texture_);

	short int getType();
	short int getValue();
	std::string getText();
	sf::FloatRect getBox();

	void animate(const float& dTime);

	void setLifetime(int time);

	bool isAlive();
	sf::Sprite* getSprite();

	void update(const float& dTime);
	void render(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter);
};

