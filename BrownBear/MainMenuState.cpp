#include "MainMenuState.h"
#include "GameStateField.h"

#include <sstream>
void MainMenuState::variableInit()
{
	clickTimer = 0;
}
void MainMenuState::bgInit()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	if (!bgTexture.loadFromFile("Resources/Images/mainmenu_bg.jpg")) throw "BG LOAD FAIL";
	background.setTexture(&bgTexture);
}
void MainMenuState::fontsInit()
{
	if (!font.loadFromFile("Fonts/comic.ttf")) {
		throw("FONT ERROR");
	}
}

void MainMenuState::keybindsInit()
{
	keybinds["MOVE_LEFT"] = keys.at("A");
	keybinds["MOVE_UP"] = keys.at("W");
	keybinds["MOVE_RIGHT"] = keys.at("D");
	keybinds["MOVE_DOWN"] = keys.at("S");
}
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* keys_, std::stack<State*>* states_, sf::Music* music_)
	:State(window, keys_, states_)
{
	variableInit();
	bgInit();
	keybindsInit();
	fontsInit();
	initButton();
	music = music_;
	/*gameStateButton = new Button(100, 100, 150, 50,
		&font,
		"Start game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));*/

}

MainMenuState::~MainMenuState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::initButton()
{
	buttons["GAME_STATE_BTN"] = new Button(100, 300, 150, 50,
		&font,
		"Start game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	buttons["SETTINGS"] = new Button(100, 400, 150, 50,
		&font,
		"Settings",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	buttons["EXIT_STATE"] = new Button(100, 500, 150, 50,
		&font,
		"Exit",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

void MainMenuState::updateBtn()
{
	//gameStateButton->update(mousePosView);
	
	for (auto &it : buttons)
	{
		it.second->update(mousePosView);
	}
	if (clickTimer) return;
	if (buttons["EXIT_STATE"]->isPressed()) {
		endState();
	}
	if (buttons["GAME_STATE_BTN"]->isPressed()) {
		
		states->push(new PregameState(window, &keys, states, music));
		clickTimer = 0.8;
	}
	if (buttons["SETTINGS"]->isPressed()) {
		clickTimer = 0.8;
		states->push(new SettingsState(window, &keys, states));
	}
}

void MainMenuState::renderBtn(sf::RenderTarget* target)
{
	//gameStateButton->render(target);
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::updateInput(const float& dTime)
{
	
}
void MainMenuState::updateCounter(const float& dTime) {
	if (!clickTimer) return;
	if ((clickTimer -= dTime) < 0) clickTimer = 0;
}


void MainMenuState::update(const float& dTime)
{
	updateCounter(dTime);
	updateMousePosition();
	updateInput(dTime);
	updateBtn();
}
void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	target->draw(background);
	renderBtn(target);
}
