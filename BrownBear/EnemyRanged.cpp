#include "EnemyRanged.h"
#include <stdlib.h> 
#include <time.h> 
#include <random>
#include <fstream>
#include<sstream>
#include <math.h>
void EnemyRanged::initVariables(unsigned hp_, unsigned cd_, unsigned str_) {
	hp = hp_;
	attackCooldown = cd_;
	attackStrength = str_;
	facing = 0;
	isAttacking = false;
	madeHit = 0;
	attackTimer = 0;
	soundInit();
}
void EnemyRanged::setHP(unsigned toSet)
{
	hp = toSet;
}
void EnemyRanged::soundInit() {
	std::fstream file;
	std::string line, tempString;
	file.open("Datafiles/settings.ini");
	if (!file) throw "FILE ERROR";
	while (!file.eof()) {
		getline(file, line);
		std::istringstream iss(line);
		getline(iss, tempString, '=');
		if (tempString != "effects_vlm") continue;
		else {
			getline(iss, tempString);
			break;
		}
	}

	if (!hitBuffer.loadFromFile("Resources/Sounds/pop.wav")) {
		throw "DEATH ERROR";
	}
	hitSound.setBuffer(hitBuffer);
	hitSound.setVolume(stof(tempString));
}
void EnemyRanged::initAnimations() {
	animationComponent->addAnimation("FLOAT_RIGHT", 9.f, 0, 3, 11, 3, 520, 420);
	animationComponent->addAnimation("FLOAT_LEFT", 9.f, 0, 2, 11, 2, 520, 420);
	animationComponent->addAnimation("ATTACK_RIGHT", 3.f, 0, 1, 11, 1, 520, 420);
	animationComponent->addAnimation("ATTACK_LEFT", 3.f, 0, 0, 11, 0, 520, 420);
}
void EnemyRanged::generateDestination(sf::Vector2u windowSize) {
	destination.x = rand() % windowSize.x;
	destination.y = rand() % windowSize.y;
}
void EnemyRanged::setOrigin() {
	sprite->setOrigin(sf::Vector2f(sprite->getPosition().x + sprite->getLocalBounds().width / 2,
		sprite->getPosition().y + sprite->getLocalBounds().height / 2));
}
EnemyRanged::EnemyRanged(unsigned hp, unsigned cd, unsigned str, float speed, sf::Texture* texture_, sf::Vector2u windowSize, Entity* player)
{
	float startingX = rand() % windowSize.x + 1;
	float startingY = windowSize.y + rand() % 250;

	initVariables(hp, cd, str);
	createSpirte(texture_, 0.12);

	setSpeed(speed);
	createAnimationComponent(*texture_);
	initAnimations();
	initBoxes();
	generateDestination(windowSize);
	setPosition(startingX, startingY);
}
void EnemyRanged::initBoxes()
{
	//Atack
	attackBox.height = sprite->getGlobalBounds().height;
	attackBox.width = sprite->getGlobalBounds().width / 3;
	updateBoxes();
	//Movement
	moveBox.height = sprite->getGlobalBounds().height;
	moveBox.width = sprite->getGlobalBounds().width / 2;
	//Hit
	hitBox.height = sprite->getGlobalBounds().height;
	hitBox.width = sprite->getGlobalBounds().width / 3;



}
void EnemyRanged::setSpeed(float speed)
{
	movementSpeed = speed;
}
void EnemyRanged::updateBoxes() {
	//sprite->getLocalBounds().height / 2
	//sprite->getLocalBounds().width / 2
	moveBox.top = sprite->getPosition().y;
	moveBox.left = sprite->getPosition().x + sprite->getGlobalBounds().width / 4;

	hitBox.top = sprite->getPosition().y;
	hitBox.left = sprite->getPosition().x + sprite->getGlobalBounds().width / 4 + moveBox.width / 6;

	attackBox.top = hitBox.top;
	attackBox.left = hitBox.left;
}
void EnemyRanged::move(const float& dTime, sf::Vector2u windowSize, Entity* player)
{
	if (isAttacking) return;
	float dirX = ((destination.x - (moveBox.left+moveBox.width/2)) > 0) ? 1.f : -1.f;
	float dirY = ((destination.y - (moveBox.top + moveBox.height / 2)) > 0) ? 1.f : -1.f;
	//COS TU JESZCZE LATA
	if (!sprite) return;
	float xBefor =  sprite->getPosition().x;
	sprite->move(dirX * movementSpeed * dTime, dirY * movementSpeed * dTime);
	float xAfter = sprite->getPosition().x;
	animationComponent->play("FLOAT_RIGHT", dTime);
	
}
void EnemyRanged::attack(Entity* player, const float& dTime, std::list<Orb*>* orbs, sf::Vector2u windowSize)
{
	bool onPosition = ((abs(destination.x - (moveBox.left + moveBox.width / 2)) < 1)
		and (abs(destination.y - (moveBox.top + moveBox.height / 2)) < 1)) ? true : false;
	if (!onPosition) return;

	if (isAttacking) {
		animationComponent->play("ATTACK_RIGHT", dTime);
		attackTimer += dTime;
		if (attackTimer > 0.36) {
			isAttacking = 0;
			attackTimer = 0;
		}
	}
	if (currentCooldown == 0 && !isAttacking) {
		isAttacking = 1;
		currentCooldown = attackCooldown;
		hitSound.play();
		sf::Vector2f destination;
		destination.x = (player->getHitBox().left + (player->getHitBox().width / 2));
		destination.y = (player->getHitBox().top + (player->getHitBox().height / 2));
		orbs->push_back(new Orb(sf::Vector2f(moveBox.left, moveBox.top), destination, movementSpeed * 1.6, attackStrength, windowSize));
	}
}
void EnemyRanged::update(const float& dTime, sf::Vector2u windowSize, Entity* player)
{
	updateCooldown(dTime);
	move(dTime, windowSize, player);
	updateBoxes();
}
void EnemyRanged::render(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter)
{
	//target->draw(tempRect1);
	//target->draw(tempRect2);
	//target->draw(tempRect3);
	shader->setUniform("hasTexture", true);
	shader->setUniform("light", playerCenter);
	if (sprite) {
		target->draw(*sprite, shader);
		hpPrint(target);
	}
}

