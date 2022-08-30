#include "EndGameState.h"
#include "sstream"
#include "string"
using namespace std;
void EndGameState::keybindsInit()
{
}
void EndGameState::variableInit(int wave_)
{
	wave = wave_;
}

void EndGameState::getScores()
{
	std::string setting, value, line;
	std::istringstream iss;
	while (!file.eof()) {
		getline(file, line);
		std::istringstream iss(line);
		getline(iss, setting, '=');
		getline(iss, value);
		bestScores.insert(std::pair<std::string, int>(setting, stoi(value)));
	}
}

void EndGameState::openFile() {
	file.open("Datafiles/scores.txt");
	if (!file) throw "FILE ERROR";
}

void EndGameState::bgInit()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	if (!bgTexture.loadFromFile("Resources/Images/endgame_bg.png")) throw "BG LOAD FAIL";
	background.setTexture(&bgTexture);
}

void EndGameState::fontsInit()
{
	if (!font.loadFromFile("Fonts/comic.ttf")) {
		throw("FONT ERROR");
	}
}
void EndGameState::setDifficulty(int diff)
{
	switch (diff) {
	case 1:
		difficulty = "easy";
		break;
	case 2:
		difficulty = "medium";
		break;
	case 3:
		difficulty = "hard";
		break;
	}
}		
EndGameState::EndGameState(sf::RenderWindow* window_, std::map<std::string, int>* keys_, std::stack<State*>* states_, int wave_, int diff, sf::Music* music_)
	:State(window_, keys_, states_)
{
	setDifficulty(diff);
	openFile();
	getScores();
	variableInit(wave_);
	bgInit();
	keybindsInit();
	fontsInit();
	btnInit();
	txtInit();
	initMusic(music_);
	
	
}
void EndGameState::initMusic(sf::Music* music_) {
	music = music_;
	if (!music->openFromFile("Resources/Sounds/music_menu.ogg"))
		throw("ERORR MUSIC");
}
EndGameState::~EndGameState()
{
	//Save scores
	std::ofstream file;
	file.open("Datafiles/scores.txt", std::ofstream::out | std::ofstream::trunc);
	for (auto it = bestScores.begin(); it != bestScores.end(); it++)
	{
		file << it->first;
		file << "=";
		file << it->second;
		file << "\n";
	}
	file.close();
}

void EndGameState::txtInit()
{
	stringstream txt1;
	txt1 << "You lost!";
	stringstream txt2;
	txt2<< "But you got to " << wave << " wave";

	text1.setString(txt1.str());
	text1.setCharacterSize(100);
	text1.setFillColor(sf::Color(222, 218, 193));
	text1.setFont(font);
	text1.setOrigin(sf::Vector2f(text1.getLocalBounds().width / 2, text1.getLocalBounds().height / 2));
	text1.setPosition(window->getSize().x/2, window->getSize().y*0.43);
	

	text2.setString(txt2.str());
	text2.setCharacterSize(50);
	text2.setFillColor(sf::Color(222, 218, 193));
	text2.setFont(font);
	text2.setOrigin(sf::Vector2f(text2.getLocalBounds().width / 2, text2.getLocalBounds().height / 2));
	text2.setPosition(window->getSize().x / 2, window->getSize().y * 0.43+text1.getLocalBounds().height*1.1);

	stringstream txt3;
	if (wave > bestScores[difficulty]) {
		txt3 << "It's your best score yet on " << difficulty << " level!";
		bestScores[difficulty] = wave;
	}
	else if(wave == bestScores[difficulty]){
		txt3 << "It ties your best score at " << difficulty << " level!";
	}
	else {
		txt3 << "Your best score on " << difficulty << " level is " << bestScores[difficulty] << ", try harder!";
	}

	text3.setString(txt3.str());
	text3.setCharacterSize(50);
	text3.setFillColor(sf::Color(222, 218, 193));
	text3.setFont(font);
	text3.setOrigin(sf::Vector2f(text3.getLocalBounds().width / 2, text3.getLocalBounds().height / 2));
	text3.setPosition(window->getSize().x / 2, window->getSize().y * 0.46 + 2*text2.getLocalBounds().height * 1.2);
}

void EndGameState::btnInit()
{
	buttons["MENU_BTN"] = new Button(window->getSize().x/3-75, window->getSize().y * 0.70, 150, 50,
		&font,
		"Exit to menu",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	buttons["EXIT_BTN"] = new Button(window->getSize().x *2 / 3-75, window->getSize().y * 0.70, 150, 50,
		&font,
		"Exit game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

void EndGameState::updateBtn()
{
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
	if (buttons["MENU_BTN"]->isPressed()) {
		endState();
	}
	if (buttons["EXIT_BTN"]->isPressed()) {
		exit(0);
	}
}

void EndGameState::renderBtn(sf::RenderTarget* target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void EndGameState::updateInput(const float& dTime)
{
}

void EndGameState::update(const float& dTime)
{
	updateMousePosition();
	updateInput(dTime);
	updateBtn();
}

void EndGameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	target->draw(background);
	renderBtn(target);
	target->draw(text1);
	target->draw(text2);
	target->draw(text3);


}

