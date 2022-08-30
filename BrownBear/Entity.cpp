#include "Entity.h"
#include<sstream>
void Entity::initBoxes()
{
}
void Entity::initVariables()
{
	texture = nullptr;
	sprite = nullptr;
	movementSpeed = 100.f;
	hp = 100;
	currentCooldown = 0;
	attackCooldown = 0;
	attackStrength = 0;
}

void Entity::hpPrint(sf::RenderTarget* target)
{
	sf::Text hpText;
	hpText.setPosition(sprite->getPosition().x, sprite->getPosition().y - 20);
	hpText.setFont(font);
	hpText.setCharacterSize(10);
	std::stringstream str;
	str << this->hp;
	hpText.setString(str.str());
	target->draw(hpText);
}
void Entity::flip()
{
	sprite->setOrigin({ sprite->getLocalBounds().width, 0 });
	sprite->setScale({ -1, 1 });
}
void Entity::fontsInit()
{
	if (!font.loadFromFile("Fonts/comic.ttf")) {
		throw("FONT ERROR");
	}
}

Entity::Entity()
{
	initVariables();
	fontsInit();
}

Entity::~Entity()
{
	delete sprite;
	delete animationComponent;
}

void Entity::createSpirte(sf::Texture* texture_, float scale)
{
	texture = texture_;
	sprite = new sf::Sprite(*texture);
	sprite->setTexture(*texture);
	sprite->setScale(sf::Vector2f(scale, scale));
}


sf::FloatRect Entity::getSize()
{
	return sprite->getGlobalBounds();
}

sf::Vector2f Entity::getPosition()
{
	return sprite->getPosition();
}

sf::FloatRect Entity::getRect()
{
	return sprite->getGlobalBounds();
}

sf::FloatRect Entity::getAttackBox()
{
	return attackBox;
}

sf::FloatRect Entity::getHitBox()
{
	return hitBox;
}

void Entity::initAnimations()
{
}

void Entity::setPosition(float x, float y)
{
	if (sprite) {
		sprite->setPosition(x, y);
	}
}

void Entity::move(const float& dTime, const float dirX, const float dirY, char dir, sf::Vector2u windowSize)
{
	if (!sprite) return;
	switch (dir) {
	case 'l':
		if (sprite->getPosition().x > 0)
			sprite->move(dirX * movementSpeed * dTime, dirY * movementSpeed * dTime);
		break;
	case 'r':
		//if (sprite->getPosition().x < windowSize.x - sprite->getTexture()->getSize().x * sprite->getScale().x)
			sprite->move(dirX * movementSpeed * dTime, dirY * movementSpeed * dTime);
		break;
	case 'u':
		if (sprite->getPosition().y>0)
			sprite->move(dirX * movementSpeed * dTime, dirY * movementSpeed * dTime);
		break;
	case 'd':
		
		if (sprite->getPosition().y < windowSize.y - sprite->getTexture()->getSize().y * sprite->getScale().y)
			sprite->move(dirX * movementSpeed * dTime, dirY * movementSpeed * dTime);
		break;
	}
}
void Entity::createAnimationComponent(sf::Texture& textureSheet_)
{
	animationComponent = new AnimationComponent(*sprite, textureSheet_);
}
void Entity::updateCooldown(const float& dTime)
{
	if (currentCooldown > dTime) {
		currentCooldown -= dTime;
	}else{
		currentCooldown = 0;
	}
}
void Entity::update(const float& dTime)
{
	updateCooldown(dTime);
}

void Entity::render(sf::RenderTarget* target)
{
	if(sprite)
		target->draw(*sprite);
		
}
