#include "Player.h"
#include <sstream>
#include<list>
#include <sstream>
#include <fstream>

void Player::initComponents()
{
	itemAS = nullptr;
	itemMS = nullptr;
}
void Player::variablesInit()
{
	this->hp = 30;
	attackCooldown = 0.73;
	attackStrength = 10;
	isAttacking = false;
	madeHit = false;
	makeAttack = false;
	facing = 0;
}
void Player::initBoxes()
{
	//Atack
	attackBox.height = sprite->getGlobalBounds().height;
	attackBox.width = sprite->getGlobalBounds().width;
	updateBoxes();
	//Movement
	moveBox.height = sprite->getGlobalBounds().height;
	moveBox.width = sprite->getGlobalBounds().width/2;
	//Hit
	hitBox.height = sprite->getGlobalBounds().height;
	hitBox.width = sprite->getGlobalBounds().width/3;


	/// /TEMP - to rem

	tempRect1.setFillColor(sf::Color::Transparent);
	tempRect1.setSize(sf::Vector2f(attackBox.width, attackBox.height));
	tempRect1.setOutlineColor(sf::Color(222, 218, 193, 70));
	tempRect1.setOutlineThickness(1);

	tempRect2.setFillColor(sf::Color::Transparent);
	tempRect2.setSize(sf::Vector2f(moveBox.width,moveBox.height));
	tempRect2.setOutlineColor(sf::Color::Blue);
	tempRect2.setOutlineThickness(1);

	tempRect3.setFillColor(sf::Color::Transparent);
	tempRect3.setSize(sf::Vector2f(hitBox.width, hitBox.height));
	tempRect3.setOutlineColor(sf::Color::Green);
	tempRect3.setOutlineThickness(1);
}
void Player::initAnimations()
{
	animationComponent->addAnimation("IDLE_RIGHT", 9.f, 0, 2, 11, 2, 720, 490);
	animationComponent->addAnimation("WALK_RIGHT", 4.f, 0, 3, 17, 3, 720, 490);
	animationComponent->addAnimation("ATTACK_RIGHT", 3.f, 0, 1, 11, 1, 720, 490);
	animationComponent->addAnimation("IDLE_LEFT", 9.f, 0, 0, 11, 0, 720, 490);
	animationComponent->addAnimation("WALK_LEFT", 4.f, 0, 4, 17, 4, 720, 490);
	animationComponent->addAnimation("ATTACK_LEFT", 3.f, 0, 5, 11, 5, 720, 490);
	
}
void Player::soundInit() {
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

	if (!hitBuffer.loadFromFile("Resources/Sounds/hit.wav")) {
		throw "HIT ERROR";
	}
	hitSound.setBuffer(hitBuffer);
	hitSound.setVolume(stof(tempString));

	if (!swoshBuffer.loadFromFile("Resources/Sounds/swosh.wav")) {
		throw "SWOSH ERROR";
	}
	swoshSound.setBuffer(swoshBuffer);
	swoshSound.setVolume(stof(tempString));
}

sf::Vector2f Player::getCenter()
{
	sf::Vector2f center;
	center.x = (moveBox.left + (moveBox.width / 2));
	center.y = (moveBox.top + (moveBox.height / 2));
	return center;
}
void Player::setItemCords(sf::Vector2f asItemCords_, sf::Vector2f msItemCords_) {
	asItemCords =  asItemCords_;
	msItemCords =  msItemCords_;
}

Player::Player(float x, float y, sf::Texture& textureSheet_)
{
	variablesInit();
	createSpirte(&textureSheet_, 0.16);
	setPosition(x, y);
	createAnimationComponent(textureSheet_);
	initComponents();
	initAnimations();
	soundInit();
	initBoxes();
}
Player::~Player()
{
}
void::Player::updateBoxes() {
	attackBox.top = sprite->getPosition().y ;
	attackBox.left = sprite->getPosition().x ;
	moveBox.top = sprite->getPosition().y;
	moveBox.left = sprite->getPosition().x + sprite->getGlobalBounds().width/4;

	hitBox.top = sprite->getPosition().y;
	hitBox.left = sprite->getPosition().x + sprite->getGlobalBounds().width / 4 + moveBox.width/6;

	//TEMP - to rem
	tempRect1.setPosition(sf::Vector2f(attackBox.left, attackBox.top));
	tempRect2.setPosition(sf::Vector2f(moveBox.left, moveBox.top));
	tempRect3.setPosition(sf::Vector2f(hitBox.left, hitBox.top));
}
void Player::move(const float& dTime, const float dirX, const float dirY, char dir, sf::Vector2u windowSize)
{
	if (!sprite || isAttacking) return;
	switch (dir) {
	case 'l':
		if (moveBox.left > 0)
			sprite->move(dirX * movementSpeed * dTime, dirY * movementSpeed * dTime);
		break;
	case 'r':
		if((moveBox.left+moveBox.width)<windowSize.x)
		sprite->move(dirX * movementSpeed * dTime, dirY * movementSpeed * dTime);
		break;
	case 'u':
		if (moveBox.top > 0)
			sprite->move(dirX * movementSpeed * dTime, dirY * movementSpeed * dTime);
		break;
	case 'd':
		if ((moveBox.top + moveBox.height) < windowSize.y)
			sprite->move(dirX * movementSpeed * dTime, dirY * movementSpeed * dTime);
		break;
	}
}
float Player::getMS()
{
	return movementSpeed;
}
int Player::getAS()
{
	return attackStrength;
}
void Player::setFacing(int x)
{
	facing = x;
}
int Player::getFacing()
{
	return facing;
}
Item* Player::getItemAS()
{
	return itemAS;
}
Item* Player::getItemMS()
{
	return itemMS;
}
void Player::makeHit(std::list<Enemy*>* enemies, std::list<EnemyRanged*>* rangedEnemies) {
	bool soundPlayed = false;
	for (auto it = enemies->begin(); it != enemies->end(); it++)
	{
		if (attackBox.intersects((*it)->getHitBox())) {
			if (hitSound.getStatus() != sf::Sound::Status::Playing && !soundPlayed) {
				hitSound.play();
				soundPlayed = true;
			}
			(*it)->hp -= attackStrength;
			currentCooldown = attackCooldown;
		}
	}
	for (auto it = rangedEnemies->begin(); it != rangedEnemies->end(); it++)
	{
		if (attackBox.intersects((*it)->getHitBox())) {
			if (hitSound.getStatus() != sf::Sound::Status::Playing && !soundPlayed) {
				hitSound.play();
				soundPlayed = true;
			}
			(*it)->hp -= attackStrength;
			currentCooldown = attackCooldown;
		}
	}
	if (!soundPlayed) swoshSound.play();
}
void Player::attack(std::list<Enemy*>* enemies, std::list<EnemyRanged*>* rangedEnemies, const float& dTime) {
	if (makeAttack) {
		currentCooldown = attackCooldown;
		makeAttack = false;
		isAttacking = true;
	}
	if (!madeHit) {
		makeHit(enemies, rangedEnemies);
		madeHit = true;
	}
	if (facing) { animationComponent->play("ATTACK_RIGHT", dTime); }
	else { animationComponent->play("ATTACK_LEFT", dTime); }
	updateCooldown(dTime);
	if (currentCooldown == 0) {
		isAttacking = false;
		madeHit = false;
	}
}
void Player::updateCooldown(const float& dTime)
{
	if (currentCooldown > dTime) {
		currentCooldown -= dTime;
	}
	else {
		currentCooldown = 0;
	}
}
void Player::addItem(Item toAdd) {
	switch (toAdd.getType()) {
	case 0:
		hp += toAdd.getValue();
		break;
	case 1:
		if (itemAS) {
			attackStrength -= itemAS->getValue();
			delete itemAS;
		}
		itemAS = new Item(toAdd);
		attackStrength += itemAS->getValue();
		itemAS->getSprite()->setScale(0.12, 0.12);
		itemAS->getSprite()->setPosition(asItemCords);

		break;
	case 2:
		if (itemMS) {
			movementSpeed -= itemMS->getValue();
			delete itemMS;
		}
		itemMS = new Item(toAdd);
		movementSpeed += itemMS->getValue();
		itemMS->getSprite()->setScale(0.12, 0.12);
		itemMS->getSprite()->setPosition(msItemCords);

		break;
	}
}
void Player::update(const float& dTime, std::list<Enemy*>* enemies, std::list<EnemyRanged*>* rangedEnemies)
{
	updateCooldown(dTime);
	if((makeAttack && currentCooldown == 0) || isAttacking) attack(enemies,rangedEnemies, dTime);
	updateBoxes();
}
void Player::renderItems(sf::RenderTarget* target) {
	if(itemAS) target->draw(*(itemAS->getSprite()));
	if(itemMS) target->draw(*(itemMS->getSprite()));
}
void Player::render(sf::RenderTarget* target, sf::Shader* shader)
{
	
	target->draw(tempRect1);
	target->draw(tempRect2);
	target->draw(tempRect3);
	
	shader->setUniform("hasTexture", true);
	shader->setUniform("light", getCenter());

	if (sprite) {
		target->draw(*sprite, shader);
		hpPrint(target);
	}
}
