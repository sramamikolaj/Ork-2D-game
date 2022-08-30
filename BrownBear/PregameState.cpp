#include "PregameState.h"

void PregameState::variableInit()
{
}

void PregameState::bgInit()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	if (!bgTexture.loadFromFile("Resources/Images/pregame_bg.jpg")) throw "BG LOAD FAIL";
	background.setTexture(&bgTexture);
}

void PregameState::fontsInit()
{
	if (!font.loadFromFile("Fonts/comic.ttf")) {
		throw("FONT ERROR");
	}
}

void PregameState::keybindsInit()
{
}

PregameState::PregameState(sf::RenderWindow* window, std::map<std::string, int>* keys, std::stack<State*>* states_, sf::Music* music_) :State(window, keys, states_)
{
	variableInit();
	bgInit();
	keybindsInit();
	fontsInit();
	initButton();
	music = music_;
}

PregameState::~PregameState()
{
}

void PregameState::initButton()
{
	buttons["EASY"] = new Button(300, 300, 150, 50,
		&font,
		"Easy",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)); //0
	buttons["MEDIUM"] = new Button(500, 300, 150, 50,
		&font,
		"Medium",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)); //1
	buttons["HARD"] = new Button(700, 300, 150, 50,
		&font,
		"Hard",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)); //2
	buttons["EXIT_STATE"] = new Button(100, 500, 150, 50,
		&font,
		"Exit",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

void PregameState::updateBtn()
{
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
}

void PregameState::updateInput(const float& dTime)
{
}

void PregameState::renderBtn(sf::RenderTarget* target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}
void PregameState::update(const float& dt)
{
	updateMousePosition();
	updateInput(dt);
	updateBtn();
	if (buttons["EASY"]->isPressed()) {
		states->push(new GameState(window, &keys, states, 1, music));
		endState();
	}
	if (buttons["MEDIUM"]->isPressed()) {
		states->push(new GameState(window, &keys, states, 2, music));
		endState();
	}
	if (buttons["HARD"]->isPressed()) {
		states->push(new GameState(window, &keys, states, 3, music));
		endState();
	}
	if (buttons["EXIT_STATE"]->isPressed()) {
		endState();
	}
}

void PregameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	target->draw(background);
	renderBtn(target);
}
