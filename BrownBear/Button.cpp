#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font_, std::string text_, sf::Color idleColor_, sf::Color hoverColor_, sf::Color activeColor_)
{
	btnState = 0;
	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	font = font_;

	text.setFont(*font);
	text.setString(text_);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(12);
	text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width/2.f,
					 shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height/2.f);

	idleColor = idleColor_;
	hoverColor = hoverColor_;
	activeColor = activeColor_;
	shape.setFillColor(idleColor);

}
Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (btnState == BTN_ACTIVE) return true;
	return false;
}



void Button::render(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
}

void Button::update(sf::Vector2f mousePos)
{
	btnState = BTN_IDLE;
	//hover
	if (shape.getGlobalBounds().contains(mousePos)) {
		btnState = BTN_HOVER;
		//pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			btnState = BTN_ACTIVE;
		}
	}

	switch (btnState) {
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		break;
	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		break;
	case BTN_ACTIVE:
		shape.setFillColor(activeColor);
		break;
	default:
		shape.setFillColor(sf::Color::Red);
		break;
	}
}
