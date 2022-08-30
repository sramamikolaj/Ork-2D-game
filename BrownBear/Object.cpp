#include "Object.h"

void Object::initTexture(sf::Texture* texture_)
{
	texture = texture_;
}

void Object::initSprite()
{
	sprite = new sf::Sprite(*texture);
	sprite->setTexture(*texture);
	sprite->setScale(sf::Vector2f(0.15, 0.15));
}

Object::Object(float x, float y, sf::Texture* texture_)
{
	initTexture(texture_);
	initSprite();
	setPosition(x, y);
}

Object::~Object()
{
	delete sprite;
}

void Object::setScale(float x, float y)
{
	sprite->setScale(x, y);
}

void Object::setPosition(float x, float y)
{
	if (sprite) {
		sprite->setPosition(x, y);
	}
}

void Object::update(const float& dTime)
{
}

void Object::render(sf::RenderTarget* target)
{
	if (sprite)
		target->draw(*sprite);
}
