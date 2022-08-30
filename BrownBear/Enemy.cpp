#include "Enemy.h"
#include <stdlib.h> 
#include <time.h> 
#include <sstream>
#include <fstream>
#include <random>
#include <math.h>
void Enemy::initVariables(unsigned hp_, unsigned cd_, unsigned str_) {
	hp = hp_;
	attackCooldown = cd_;
	attackStrength = str_;
	facing = 0;
	isAttacking = false; 
	madeHit = 0;
	attackTimer = 0;
	soundInit();
}
void Enemy::setHP(unsigned toSet)
{
	hp = toSet;
}
void Enemy::soundInit() {
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

	if (!hitBuffer.loadFromFile("Resources/Sounds/enemyHit.wav")) {
		throw "DEATH ERROR";
	}
	hitSound.setBuffer(hitBuffer);
	hitSound.setVolume(stof(tempString));
}
void Enemy::initAnimations() {
	animationComponent->addAnimation("WALK_RIGHT", 8.f, 0, 5, 17, 5, 720, 480);
	animationComponent->addAnimation("WALK_LEFT", 8.f, 0, 4, 17, 4, 720, 480);
	animationComponent->addAnimation("IDLE_RIGHT", 9.f, 0, 3, 11, 3, 720, 480);
	animationComponent->addAnimation("IDLE_LEFT", 9.f, 0, 2, 11, 2, 720, 480);
	animationComponent->addAnimation("ATTACK_RIGHT", 3.f, 0, 1, 11, 1, 720, 480);
	animationComponent->addAnimation("ATTACK_LEFT", 3.f, 0, 0, 11, 0, 720, 480);
}
void Enemy::generateDestination(Entity* player) {
	int tempX = player->getAttackBox().width;
	destination.x = rand() % tempX;
	int tempY = player->getAttackBox().height;
	destination.y = rand() % tempY;
}
void Enemy::setOrigin() {
	sprite->setOrigin(sf::Vector2f(sprite->getPosition().x+sprite->getLocalBounds().width/2,
		sprite->getPosition().y + sprite->getLocalBounds().height / 2));
}
Enemy::Enemy(unsigned hp, unsigned cd, unsigned str,  float speed, sf::Texture* texture_, sf::Vector2u windowSize, Entity* player)
{
	float startingX = rand() % windowSize.x + 1;
	float startingY = windowSize.y+rand()%250;

	initVariables(hp, cd, str);
	createSpirte(texture_, 0.12);
	
	setSpeed(speed);
	createAnimationComponent(*texture_);
	initAnimations();
	initBoxes();
	generateDestination(player);
	setPosition(startingX, startingY);
}
void Enemy::initBoxes()
{
	//Atack
	attackBox.height = sprite->getGlobalBounds().height;
	attackBox.width = sprite->getGlobalBounds().width/3;
	updateBoxes();
	//Movement
	moveBox.height = sprite->getGlobalBounds().height;
	moveBox.width = sprite->getGlobalBounds().width / 2;
	//Hit
	hitBox.height = sprite->getGlobalBounds().height;
	hitBox.width = sprite->getGlobalBounds().width / 3;


	/// /TEMP - to rem

	tempRect1.setFillColor(sf::Color::Transparent);
	tempRect1.setSize(sf::Vector2f(attackBox.width, attackBox.height));
	tempRect1.setOutlineColor(sf::Color::Red);
	tempRect1.setOutlineThickness(1);

	tempRect2.setFillColor(sf::Color::Transparent);
	tempRect2.setSize(sf::Vector2f(moveBox.width, moveBox.height));
	tempRect2.setOutlineColor(sf::Color::Blue);
	tempRect2.setOutlineThickness(1);

	tempRect3.setFillColor(sf::Color::Transparent);
	tempRect3.setSize(sf::Vector2f(hitBox.width, hitBox.height));
	tempRect3.setOutlineColor(sf::Color::Green);
	tempRect3.setOutlineThickness(1);
}
void Enemy::setSpeed(float speed)
{
	movementSpeed = speed;
}
void Enemy::updateBoxes() {
	//sprite->getLocalBounds().height / 2
	//sprite->getLocalBounds().width / 2
	moveBox.top = sprite->getPosition().y;
	moveBox.left = sprite->getPosition().x + sprite->getGlobalBounds().width / 4;

	hitBox.top = sprite->getPosition().y ;
	hitBox.left = sprite->getPosition().x +  sprite->getGlobalBounds().width / 4 + moveBox.width / 6;

	attackBox.top = hitBox.top;
	attackBox.left = hitBox.left;
	//TEMP - to rem
	tempRect1.setPosition(sf::Vector2f(attackBox.left, attackBox.top));
	tempRect2.setPosition(sf::Vector2f(moveBox.left, moveBox.top));
	tempRect3.setPosition(sf::Vector2f(hitBox.left, hitBox.top));
}
void Enemy::move(const float& dTime, sf::Vector2u windowSize, Entity* player)
{
	if (isAttacking) return;
	float dirX = ((moveBox.left + moveBox.width / 2) - (player->getAttackBox().left + destination.x) > 0) ? -1.f : 1.f;
	float dirY = ((moveBox.top + moveBox.height / 2) - (player->getAttackBox().top +  destination.y) > 0) ? -1.f : 1.f;
	
	int tem1 = abs(player->getAttackBox().top + destination.y - (moveBox.top + moveBox.height / 2));
	int tem2 = abs(player->getAttackBox().left + destination.x - (moveBox.left + moveBox.width / 2));
	
	//COS TU JESZCZE LATA
	if (!sprite) return;
	sprite->move(dirX*movementSpeed * dTime, dirY*movementSpeed * dTime);
	if (player->getAttackBox().left + destination.x - (moveBox.left + moveBox.width / 2) > 0) {
		facing = 0;
	}
	else if (player->getAttackBox().left + destination.x - (moveBox.left + moveBox.width / 2) < 0) {
		facing = 1;
	}
	if (isAttacking) return;
	if ((tem1 < 0.1) and (tem2 < 0.1)) {
		if (facing) {
			animationComponent->play("IDLE_LEFT", dTime);
		}
		else {
			animationComponent->play("IDLE_RIGHT", dTime);
		}
	}
	else if (abs((moveBox.left + moveBox.width / 2) - (player->getAttackBox().left + destination.x)) < 0.3) {
		animationComponent->play("WALK_RIGHT", dTime);
	}
	else{
		if (facing) {
			animationComponent->play("WALK_LEFT", dTime);
		}
		else {
			animationComponent->play("WALK_RIGHT", dTime);
		}
	}
}

void Enemy::update(const float& dTime, sf::Vector2u windowSize, Entity* player)
{
	updateCooldown(dTime);
	move(dTime, windowSize, player);
	updateBoxes();
}
void Enemy::render(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter)
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

unsigned Enemy::attack(Entity* player, const float& dTime)
{
	if (isAttacking) {
		if(facing) animationComponent->play("ATTACK_LEFT", dTime);
		else animationComponent->play("ATTACK_RIGHT", dTime);
		attackTimer += dTime;
		if (attackTimer > 0.37) {
			isAttacking = false;
			madeHit = false;
			attackTimer = 0;
		}
		return 0;
	}else {
		if (attackBox.intersects(player->getHitBox())) {
			if (madeHit || isAttacking || currentCooldown>0) return 0;
			isAttacking = true;
			madeHit = true;
			currentCooldown = attackCooldown;
			hitSound.play();
			return attackStrength;
		}
	}
	return 0;
}
