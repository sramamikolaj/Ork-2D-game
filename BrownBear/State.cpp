



#include "State.h"

State::State(sf::RenderWindow* window_, std::map<std::string, int>* keys_, std::stack<State*>* states_)
{
	keys = *keys_;
	window = window_;
	states = states_;
	quit = false;
}

State::~State()
{
}

const bool& State::getQuit()
{
	return quit;
}

void State::updateMousePosition()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::endState()
{
	quit = true;
}
