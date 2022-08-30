#pragma once
#include<vector>
#include <iostream>
#include <ctime>
/* DO USTAWIEN Z PLIKU
#include<fstream>
#include<sstream>
*/
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include<stack>
#include<map>
#include"Object.h"
#include "AnimationComponent.h"
class Entity
{
private:
	
protected:
	sf::Texture* texture;
	sf::Sprite* sprite;
	sf::RectangleShape shape;
	sf::Font font;
	

	sf::FloatRect attackBox;
	sf::FloatRect moveBox;
	sf::FloatRect hitBox;

	virtual void initBoxes();
	void initVariables();

	float movementSpeed;
	float currentCooldown;
	float attackCooldown;
	unsigned attackStrength;
	int facing;
	

	void hpPrint(sf::RenderTarget* target);
	void fontsInit();

	void createAnimationComponent(sf::Texture& textureSheet_);
	virtual void initAnimations();
	void createSpirte(sf::Texture* texture, float scale);
public:
	AnimationComponent* animationComponent;
	int hp;


	Entity();
	~Entity();
	


	virtual sf::FloatRect getSize();
	sf::Vector2f getPosition();
	sf::FloatRect getRect();
	sf::FloatRect getAttackBox();


	
	sf::FloatRect getHitBox();
	void flip();
	virtual void setPosition(float x, float y);
	virtual void move(const float& dTime, const float x, const float y, char dir, sf::Vector2u windowSize);
	virtual void updateCooldown(const float& dTime);

	virtual void update(const float& dTime);
	virtual void render(sf::RenderTarget* target);
};

