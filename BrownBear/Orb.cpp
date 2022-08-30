#include "Orb.h"
#include <math.h>
void Orb::initPath(sf::Vector2f startPos, sf::Vector2f destination, sf::Vector2u windowSize)
{
	path.x = (destination.x - startPos.x)/windowSize.x;
	path.y = (destination.y - startPos.y) / windowSize.y;

	while (abs(path.x * 1.1) < 1 && abs(path.y * 1.1) < 1) {
		path.x *= 1.1;
		path.y *= 1.1;
	}
}
void Orb::initTexture()
{
	if (!texture.loadFromFile("Resources/Images/Sprites/tempOrb.png"))
		throw "ERROR LOADING ORB";
}

void Orb::initBox()
{
	box.height = sprite->getGlobalBounds().height;
	box.width = sprite->getGlobalBounds().width;
	box.top = sprite->getPosition().y;
	box.left = sprite->getPosition().x;
}

void Orb::initSprite(sf::Vector2f startPos)
{
	sprite = new sf::Sprite();
	sprite->setTexture(texture);
	sprite->setPosition(startPos);
	sprite->setScale(0.1, 0.1);
}

Orb::Orb(sf::Vector2f startPos, sf::Vector2f destination, int ms, int dmg, sf::Vector2u windowSize_)
{

	initTexture();
	initSprite(startPos);
	initBox();
	movementSpeed = ms;
	damage = dmg;
	initPath(startPos, destination, windowSize_);
	windowSize = windowSize_;
}



int Orb::update(const float& dTime, sf::FloatRect playersBox)
{
	//ZWRACAJ -1 JAK POZA EKRANEM 
	sprite->move(path.x * movementSpeed * dTime, path.y * movementSpeed * dTime);

	if (playersBox.contains(sprite->getPosition())) {
		return damage;
	}
	return 0;

}

void Orb::render(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter)
{
	shader->setUniform("hasTexture", true);
	shader->setUniform("light", playerCenter);
	target->draw(*sprite, shader);
}
