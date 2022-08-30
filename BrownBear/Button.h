#pragma once
#pragma once
#include <iostream>
#include <ctime>
/* DO USTAWIEN Z PLIKu
#include<fstream>
#include<sstream>
*/
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>

enum button_states {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button
{
private:
	short unsigned btnState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float height, float width, sf::Font* font_, std::string text_, sf::Color idleColor_, sf::Color hoverColor_, sf::Color activeColor_);
	~Button();

	const bool isPressed() const;

	void render(sf::RenderTarget* target);
	void update(sf::Vector2f);
};

