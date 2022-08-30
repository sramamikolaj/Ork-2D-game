#pragma once
#include"Entity.h"
class Object
{
private:
	sf::Texture* texture;
	sf::Sprite* sprite;

	void initTexture( sf::Texture* texture_);
	void initSprite();
public:
	Object(float x, float y, sf::Texture*);
	~Object();
	
	virtual void setScale(float x, float y);
	virtual void setPosition(float x, float y);
	virtual void update(const float& dTime);
	virtual void render(sf::RenderTarget* target);
};

