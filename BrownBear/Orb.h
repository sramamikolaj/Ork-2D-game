#pragma once
#include"Entity.h"
class Orb
{
private:
	int movementSpeed;
	int damage;


	sf::Sprite* sprite;
	sf::FloatRect box;
	sf::Texture texture;
    
	sf::Vector2f path;
	sf::Vector2u windowSize;

	void initPath(sf::Vector2f startPos, sf::Vector2f destination_, sf::Vector2u windowSize);
	void initTexture();
	void initBox();
	void initSprite(sf::Vector2f startPos);
public:
	Orb(sf::Vector2f startPos, sf::Vector2f destination, int ms, int dmg, sf::Vector2u windowSize);

	int update(const float& dTime, sf::FloatRect playersBox);
	void render(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter);
};

