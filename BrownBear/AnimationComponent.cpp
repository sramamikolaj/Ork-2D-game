#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite_, sf::Texture& textureSheet_)
	:sprite(sprite_), textureSheet(textureSheet_)
{
	
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : animations)
	{
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const std::string key,
	float animationTimer_, int startFrameX, int  startFrameY, int  framesX,
	int framesY, int width_, int height_)
{
	animations[key] = new Animation(sprite, textureSheet, animationTimer_, startFrameX, startFrameY, framesX, framesY, width_, height_);
}

void AnimationComponent::play(const std::string key, const float& dTime)
{
	animations[key]->play(dTime);
}

bool AnimationComponent::hasEnded(const std::string key)
{
	if (animations[key]->currRect == animations[key]->endRect) {
		return true;
	}
	return false;
}
