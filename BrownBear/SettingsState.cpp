#include"SettingsState.h"
#include <sstream>
#include <utility>
#include <string>
void SettingsState::getSettings(fstream& toOpen, string type)
{
	std::string setting, value, line;
	std::istringstream iss;
	while (!toOpen.eof()) {
		getline(toOpen, line);
		std::istringstream iss(line);
		getline(iss, setting, '=');
		getline(iss, value);
		if (type == "settings") settings.insert(std::pair<std::string, int>(setting, stoi(value)));
		else if (type == "keys") keybinds.insert(std::pair < std::string, std::string > (setting, value));
		else throw "ERROR TYPE";
	}
}
void SettingsState::openFile() {
	keyFile.open("Datafiles/keybinds.ini");
	if (!keyFile) throw "FILE ERROR";
	file.open("Datafiles/settings.ini");
	if (!file) throw "FILE ERROR";
}
void SettingsState::variableInit()
{
	timer = 0;
	keyChange = "";
}
void SettingsState::bgInit()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	if (!bgTexture.loadFromFile("Resources/Images/settings_bg.jpg")) throw "BG LOAD FAIL";
	background.setTexture(&bgTexture);
}
void SettingsState::fontsInit()
{
	if (!font.loadFromFile("Fonts/comic.ttf")) {
		throw("FONT ERROR");
	}
}
void SettingsState::initResolutions() {
	resolutions.push_back(sf::Vector2u(1280, 720));
	resolutions.push_back(sf::Vector2u(1600, 900));
	resolutions.push_back(sf::Vector2u(1920, 1080));
}

void SettingsState::keybindsInit()
{
	
}
SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* keys_, std::stack<State*>* states_)
	:State(window, keys_, states_)
{
	settingsType = 0;
	changesMade = false;
	variableInit();
	bgInit();
	keybindsInit();
	fontsInit();
	initButton();
	initResolutions();
	openFile();
	getSettings(file, "settings");
	getSettings(keyFile, "keys");
}
void SettingsState::saveSettings() {
	std::ofstream file;
	file.open("Datafiles/settings.ini", std::ofstream::out | std::ofstream::trunc);
	for (auto it = settings.begin(); it != settings.end(); it++)
	{
		file << it->first;
		file << "=";
		file << it->second;
		file << "\n";
	}
	file.close();

	file.open("Datafiles/keybinds.ini", std::ofstream::out | std::ofstream::trunc);
	for (auto it = keybinds.begin(); it != keybinds.end(); it++)
	{
		file << it->first;
		file << "=";
		file << it->second;
		file << "\n";
	}
	file.close();

}
SettingsState::~SettingsState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
	file.close();
	saveSettings();

}
void SettingsState::initButton()
{
	/*buttons["GAME_STATE_BTN"] = new Button(100, 300, 150, 50,
		&font,
		"Start game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));*/
	buttons["GRAPHIC_SET"] = new Button(20, 300, 150, 50,
		&font,
		"Graphic settings", 
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)); //0
	buttons["AUDIO_SET"] = new Button(20, 400, 150, 50,
		&font,
		"Audio settings",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)); //1
	buttons["CONTROL_SET"] = new Button(20, 500, 150, 50,
		&font,
		"Control settings",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)); //2
	buttons["EXIT_STATE"] = new Button(20, 600, 150, 50,
		&font,
		"Exit",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	graphicButtons["CHANGE_RES"] = new Button(300, 300, 150, 50,
		&font,
		"Change resolution",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	graphicButtons["FULL_SCR"] = new Button(500, 300, 150, 50,
		&font,
		"Full screen",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	graphicButtons["FRAME_LIMIT"] = new Button(700, 300, 150, 50,
		&font,
		"Frame limit",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	graphicButtons["VERTICAL_SYNC"] = new Button(900, 300, 150, 50,
		&font,
		"Vertical sync",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	audioButtons["MUSIC_VLM"] = new Button(300, 300, 150, 50,
		&font,
		"Music volume",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	audioButtons["EFFECTS_VLM"] = new Button(500, 300, 150, 50,
		&font,
		"Effects volume",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	//Control
	controlButtons["UP"] = new Button(300, 300, 80, 50,
		&font,
		"Up",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	controlButtons["DOWN"] = new Button(450, 300, 80, 50,
		&font,
		"Down",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	controlButtons["LEFT"] = new Button(600, 300, 80, 50,
		&font,
		"Left",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	controlButtons["RIGHT"] = new Button(750, 300, 80, 50,
		&font,
		"Right",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)); 
	controlButtons["PICK_UP"] = new Button(900, 300, 80, 50,
		&font,
		"Pick up",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
	controlButtons["ATTACK"] = new Button(1050, 300, 80, 50,
		&font,
		"Attack",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

void SettingsState::updateGraphicBtn() {
	if (timer) return;
	if (graphicButtons["CHANGE_RES"]->isPressed()) {
		if (settings["width"] == 1280) {
			settings["height"] = 1080;
			settings["width"] = 1920;
		}else{
			settings["height"] = 720;
			settings["width"] = 1280;
		}
		setTimer();
	}
	if (graphicButtons["FULL_SCR"]->isPressed()) {
		if (settings["fullscreen"] == 0)settings["fullscreen"] = 1;
		else settings["fullscreen"] = 0;
		setTimer();
	}
	if (graphicButtons["FRAME_LIMIT"]->isPressed()) {
		switch (settings["frame_limit"]) {
		case 0:
			settings["frame_limit"] = 30;
			break;
		case 30:
			settings["frame_limit"] = 0;
			break;
		}
		setTimer();
	}
	if (graphicButtons["VERTICAL_SYNC"]->isPressed()) {
		switch (settings["vertical_sync"]) {
		case 0:
			settings["vertical_sync"] = 1;
			break;
		case 1:
			settings["vertical_sync"] = 0;
			break;
		}
		setTimer();
	}
}
void SettingsState::updateAudioBtn() {
	if (audioButtons["MUSIC_VLM"]->isPressed() && !timer) {
		if (settings["music_vlm"] >= 10) settings["music_vlm"] = 0;
		else settings["music_vlm"]++;
		setTimer(0.3);
	}
	if (audioButtons["EFFECTS_VLM"]->isPressed() && !timer) {
		if (settings["effects_vlm"] >= 10) settings["effects_vlm"] = 0;
		else settings["effects_vlm"]++;
		setTimer(0.3);
	}
}
void SettingsState::updateControlBtn() {
	if (controlButtons["UP"]->isPressed()) {
		keyChange = "up";
	}
	if (controlButtons["DOWN"]->isPressed()) {
		keyChange = "down";
	}
	if (controlButtons["LEFT"]->isPressed()) {
		keyChange = "left";
	}
	if (controlButtons["RIGHT"]->isPressed()) {
		keyChange = "right";
	}
	if (controlButtons["PICK_UP"]->isPressed()) {
		keyChange = "pick_up";
	}
	if (controlButtons["ATTACK"]->isPressed()) {
		keyChange = "attack";
	}
	if (keyChange != "") {
		for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
		{
			if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k))) {
				keybinds[keyChange] = getKey(static_cast<sf::Keyboard::Key>(k));
				keyChange = "";
			}
				
		}
	}

}
string SettingsState::getKey(const sf::Keyboard::Key& k) {
	switch (k) {
	case sf::Keyboard::A:
		return "A";
	case sf::Keyboard::B:
		return "B";
	case sf::Keyboard::C:
		return "C";
	case sf::Keyboard::D:
		return "D";
	case sf::Keyboard::E:
		return "E";
	case sf::Keyboard::F:
		return "F";
	case sf::Keyboard::G:
		return "G";
	case sf::Keyboard::H:
		return "H";
	case sf::Keyboard::I:
		return "I";
	case sf::Keyboard::J:
		return "J";
	case sf::Keyboard::K:
		return "K";
	case sf::Keyboard::L:
		return "L";
	case sf::Keyboard::M:
		return "M";
	case sf::Keyboard::N:
		return "N";
	case sf::Keyboard::O:
		return "O";
	case sf::Keyboard::P:
		return "P";
	case sf::Keyboard::Q:
		return "Q";
	case sf::Keyboard::R:
		return "R";
	case sf::Keyboard::S:
		return "S";
	case sf::Keyboard::T:
		return "T";
	case sf::Keyboard::U:
		return "U";
	case sf::Keyboard::V:
		return "V";
	case sf::Keyboard::W:
		return "W";
	case sf::Keyboard::X:
		return "X";
	case sf::Keyboard::Y:
		return "Y";
	case sf::Keyboard::Z:
		return "Z";
	case sf::Keyboard::Space:
		return "Space";
	}
}
void SettingsState::updateBtn()
{
	//gameStateButton->update(mousePosView);
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
	if (buttons["GRAPHIC_SET"]->isPressed()) {
		settingsType = 0;
	}
	if (buttons["AUDIO_SET"]->isPressed()) {
		settingsType = 1;
	}
	if (buttons["CONTROL_SET"]->isPressed()) {
		settingsType = 2;
	}
	if (buttons["EXIT_STATE"]->isPressed()) {
		endState();
	}
	switch (settingsType) {
	case 0:
		for (auto& it : graphicButtons)
		{
			it.second->update(mousePosView);
			
			updateGraphicBtn();

		}
		break;
	case 1:
		for (auto& it : audioButtons)
		{
			it.second->update(mousePosView);
			updateAudioBtn();
		}
		break;
	case 2:
		for (auto& it : controlButtons)
		{
			it.second->update(mousePosView);
			updateControlBtn();
		}
		break;
	}
}

void SettingsState::renderBtn(sf::RenderTarget* target)
{
	//gameStateButton->render(target);
	for (auto& it : buttons)
	{
		it.second->render(target);
	}


	switch (settingsType) {
	case 0:
		for (auto& it : graphicButtons)
		{
			it.second->render(target);
		}
		break;
	case 1:
		for (auto& it : audioButtons)
		{
			it.second->render(target);
		}
		break;
	case 2:
		for (auto& it : controlButtons)
		{
			it.second->render(target);
		}
		break;
	}
	
}

void SettingsState::updateInput(const float& dTime)
{

}
void SettingsState::printSettings(sf::RenderTarget* target) {
	sf::Text text1;
	text1.setCharacterSize(50);
	text1.setFillColor(sf::Color(222, 218, 193));
	text1.setFont(font);
	text1.setOrigin(sf::Vector2f(text1.getLocalBounds().width / 2, text1.getLocalBounds().height / 2));
	target->draw(text1);

	switch (settingsType) {
	case 0: {
		text1.setString(to_string(settings["height"]));
		text1.setPosition(300, 370);
		target->draw(text1);
		text1.setString(to_string(settings["width"]));
		text1.setPosition(300, 430);
		target->draw(text1);

		stringstream tempSS;
		if (settings["fullscreen"]) tempSS << "On";
		else tempSS << "Off";
		text1.setString(tempSS.str());
		text1.setPosition(550, 370);
		target->draw(text1);

		text1.setString(to_string(settings["frame_limit"]));
		text1.setPosition(750, 370);
		target->draw(text1);

		tempSS.str("");
		if (settings["vertical_sync"]) tempSS << "On";
		else tempSS << "Off";
		text1.setString(tempSS.str());
		text1.setPosition(950, 370);
		target->draw(text1);

		break;
	}
	case 1: {
		text1.setString(to_string(settings["music_vlm"]));
		text1.setPosition(350, 370);
		target->draw(text1);

		text1.setString(to_string(settings["effects_vlm"]));
		text1.setPosition(570, 370);
		target->draw(text1);
		break;
	}
	case 2:
		text1.setString(keybinds["up"]);
		text1.setPosition(350, 350);
		target->draw(text1);

		text1.setString(keybinds["down"]);
		text1.setPosition(500, 350);
		target->draw(text1);

		text1.setString(keybinds["left"]);
		text1.setPosition(650, 350);
		target->draw(text1);

		text1.setString(keybinds["right"]);
		text1.setPosition(800, 350);
		target->draw(text1);

		text1.setString(keybinds["pick_up"]);
		text1.setPosition(950, 350);
		target->draw(text1);

		text1.setString(keybinds["attack"]);
		text1.setPosition(1100, 350);
		target->draw(text1);

		if (keyChange != "") {
			std::stringstream str; str << "Now changing: " << keyChange;
			text1.setString(str.str());
			text1.setPosition(450, 500);
			target->draw(text1);
		}
		break;
	}
}
void SettingsState::setTimer(float toSet) {
	timer = toSet;
}

void SettingsState::updateTimer(const float& dTime)
{
}

void SettingsState::update(const float& dTime)
{
	updateMousePosition();
	updateInput(dTime);
	updateBtn();

	if ((timer - dTime) <= 0) { 
		timer = 0; }
	else { 
		timer -= dTime; 
	}
}
void SettingsState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	target->draw(background);
	renderBtn(target);
	printSettings(target);


	sf::Text mouseText;
	mouseText.setPosition(mousePosView.x, mousePosView.y - 10);
	mouseText.setFont(font);
	mouseText.setCharacterSize(12);
	std::stringstream str;
	str << mousePosView.x << " " << mousePosView.y;
	mouseText.setString(str.str());
	target->draw(mouseText);
}