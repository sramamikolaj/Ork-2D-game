#include "Item.h"
#include<sstream>
void Item::initBox()
{
	box.height = sprite->getGlobalBounds().height;
	box.width = sprite->getGlobalBounds().width;
	box.top = sprite->getPosition().y;
	box.left = sprite->getPosition().x;
}

void Item::initSprite(const int x, const int y)
{
	sprite = new sf::Sprite();
	sprite->setTexture(texture);
	sprite->setPosition(sf::Vector2f(x, y));
	sprite->setScale(0.2, 0.2);
}

Item::Item(const int x, const int y, const int type_, const int value_, sf::Texture& texture_)
{
	lifetime = 12; // <- LIFETIME
	timer = 0;
	texture = texture_;
	type = type_;
	valueAdded = value_;
	animTimer = 0;
	animCounter = 0;
	initSprite(x, y);
	initBox();
}

short int Item::getType()
{
	return type;
}

short int Item::getValue()
{
	return valueAdded;
}

std::string Item::getText()
{
	std::stringstream temp; 
	temp << "+" << valueAdded << " ";
	switch (type) {
	case 0:
		temp << "health!";
		break;
	case 1:
		temp << "attack strength!";
		break;
	case 2:
		temp << "movement speed!";
		break;
	}
	return temp.str();
}
sf::FloatRect Item::getBox()
{
	return box;
}
void Item::animate(const float& dTime) {
	animTimer += 100.f * dTime;
	if (animTimer >= 8) {
		//reset
		animTimer = 0.f;
		if (animCounter < 10) {
			sprite->setPosition(sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y - 1));
			animCounter++;
		}
		else {
			sprite->setPosition(sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y + 1));
			animCounter++;
			if (animCounter == 20) animCounter = 0;
		}
	}
}
void Item::setLifetime(int time) {
	lifetime = time;
}
bool Item::isAlive() {
	if (timer >= lifetime) return false;
	return true;
}
sf::Sprite* Item::getSprite()
{
	return sprite;
}
void Item::update(const float& dTime)
{
	animate(dTime);
	timer += dTime;
}

void Item::render(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter)
{
	shader->setUniform("hasTexture", true);
	shader->setUniform("light", playerCenter);
	target->draw(*sprite, shader);
}
