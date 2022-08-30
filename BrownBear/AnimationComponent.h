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
class AnimationComponent
{
private:
	class Animation {
	public:
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		int width, height;
		sf::IntRect startRect;
		sf::IntRect currRect;
		sf::IntRect endRect;
		Animation(sf::Sprite& sprite_, sf::Texture& textureSheet_, 
				float animationTimer_, int startFrameX, int  startFrameY, int  framesX,
				int framesY, int width_, int height_):sprite(sprite_), textureSheet(textureSheet_), animationTimer(animationTimer_),
				width(width_), height(height_){
			timer = 0.f;
			startRect = sf::IntRect(startFrameX*width, startFrameY*height, width, height);
			endRect = sf::IntRect(framesX*width, framesY*height, width, height);
			sprite.setTexture(textureSheet, true);
			sprite.setTextureRect(startRect);
			currRect = startRect;
		}

		void play(const float& dTime) {
			timer += 100.f * dTime;
			if (timer >= animationTimer) {
				//reset
				timer = 0.f;

				if (currRect != endRect) {
					currRect.left += width;
				}
				else {
					currRect.left = startRect.left;
				}
				sprite.setTextureRect(currRect);
			}
		}
		void reset() {
			timer = 0.f;
			currRect = startRect;
		}
	};


	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet_);
	~AnimationComponent();

	void addAnimation(const std::string key, 
		float animationTimer_, int startFrameX, int  startFrameY, int  framesX,
		int framesY, int width_, int height_);

	void play(const std::string key,  const float& dTime);
	bool hasEnded(const std::string key);
};

