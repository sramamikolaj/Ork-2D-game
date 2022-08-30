#include "PauseState.h"
#include "sstream"
#include "string"
using namespace std;
void PauseState::keybindsInit()
{
	keybinds["ESCAPE"] = keys.at("ESC");
}
void PauseState::variableInit()
{
	timer = 0;
}

void PauseState::bgInit()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x)/3, static_cast<float>(window->getSize().y)/3));
	background.setPosition(sf::Vector2f(static_cast<float>(window->getSize().x) / 3, static_cast<float>(window->getSize().y) / 3));
	if (!bgTexture.loadFromFile("Resources/Images/pause.jpg")) throw "BG LOAD FAIL";
	background.setTexture(&bgTexture);
}

void PauseState::fontsInit()
{
	if (!font.loadFromFile("Fonts/comic.ttf")) {
		throw("FONT ERROR");
	}
}

PauseState::PauseState(sf::RenderWindow* window_, std::map<std::string, int>* keys_, std::stack<State*>* states_, sf::Music* music_)
	:State(window_, keys_, states_)
{
	variableInit();
	bgInit();
	keybindsInit();
	fontsInit();
	btnInit();
	txtInit();
	music = music_;
}

PauseState::~PauseState()
{
}

void PauseState::txtInit()
{
	
}

void PauseState::btnInit()
{
	buttons["CONTINUE_BTN"] = new Button(window->getSize().x / 2- 75, window->getSize().y/2, 150, 50,
		&font,
		"Continue game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	buttons["EXIT_BTN"] = new Button(window->getSize().x/ 2 - 75, window->getSize().y/2+55, 150, 50,
		&font,
		"Exit game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

void PauseState::updateBtn()
{
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
	if (buttons["CONTINUE_BTN"]->isPressed()) {
		endState();
	}
	if (buttons["EXIT_BTN"]->isPressed()) {
		if (!music->openFromFile("Resources/Sounds/music_menu.ogg"))
			throw("ERORR MUSIC");
		states->pop();
		states->top()->endState();
		endState();
	}
}

void PauseState::renderBtn(sf::RenderTarget* target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void PauseState::updateInput(const float& dTime)
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key(keybinds.at("ESCAPE"))))) {
		endState();
	}
}

void PauseState::update(const float& dTime)
{
	timer += dTime;
	if (timer < 1) return;
	updateMousePosition();
	updateInput(dTime);
	updateBtn();
}

void PauseState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	states->pop();
	states->top()->render();
	target->draw(background);
	renderBtn(target);
	states->push(this);


}

