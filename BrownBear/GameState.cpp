#include "GameState.h"
#include <sstream>
#include <string>
#include <cmath>
#include <fstream>
#include "EndGameState.h"
#include "PauseState.h"
void GameState::playerInit()
{
	sf::Vector2u windowSize = window->getSize();
	player = new Player(windowSize.x*0.3, windowSize.y*0.3, textures["PLAYER_SHEET"]);
}
void GameState::soundInit() {
	std::fstream file;
	std::string line, tempString;
	file.open("Datafiles/settings.ini");
	if (!file) throw "FILE ERROR";
	while (!file.eof()) {
		getline(file, line);
		std::istringstream iss(line);
		getline(iss, tempString, '=');
		if (tempString != "effects_vlm") continue;
		else {
			getline(iss, tempString);
			break;
		}
	}

	if (!buffer.loadFromFile("Resources/Sounds/pogczamp.wav")) {
		throw "DEATH ERROR";
	}
	sound.setBuffer(buffer);
	sound.setVolume(stof(tempString));
}
void GameState::keybindsInit()
{
	keybinds["MOVE_LEFT"] = keys.at("A");
	keybinds["MOVE_UP"] = keys.at("W");
	keybinds["MOVE_RIGHT"] = keys.at("D");
	keybinds["MOVE_DOWN"] = keys.at("S");
	keybinds["ESCAPE"] = keys.at("ESC");
	keybinds["ATTACK"] = keys.at("Space");
	keybinds["PICK"] = keys.at("E");
}

void GameState::setDifficulty(int d)
{
	switch (d) {
	case 1:
		difficulty = 0.8;
		break;
	case 2:
		difficulty = 1;
		break;
	case 3:
		difficulty = 1.4;
		break;
	}
}

void GameState::initShader()
{
	core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag");
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* keys_, std::stack<State*>* states_, int diff, sf::Music* music_)
	:State(window, keys_, states_)
{
	currentWave = 1;
	setDifficulty(diff);
	texturesInit();
	backgroundInit(window, diff);
	keybindsInit();
	fontsInit();
	playerInit();
	initEnemies();
	soundInit();
	initPlayerPanel();
	initItemDescription();
	initShader();
	initMusic(music_);
	player->setItemCords(sf::Vector2f(playerPanel.getPosition().x + 210,
		playerPanel.getPosition().y + 0.32 * playerPanel.getLocalBounds().height), sf::Vector2f(playerPanel.getPosition().x + 222,
			playerPanel.getPosition().y + 0.62 * playerPanel.getLocalBounds().height));
	
}

GameState::~GameState()
{
	delete player;
}

void GameState::initMusic(sf::Music* music_) {
	music = music_;
	if (!music->openFromFile("Resources/Sounds/music_game.ogg"))
		throw("ERORR MUSIC");
}
void GameState::fontsInit()
{
	if (!font.loadFromFile("Fonts/comic.ttf")) {
		throw("FONT ERROR");
	}
}
void GameState::texturesInit()
{
	if (!textures["GOLEM_1"].loadFromFile("Resources/Images/Sprites/golem_1.png"))
		throw "ERROR LOADING SPRITE GOLEM";
	if (!textures["GOLEM_2"].loadFromFile("Resources/Images/Sprites/golem_2.png"))
		throw "ERROR LOADING SPRITE GOLEM";
	if (!textures["GOLEM_3"].loadFromFile("Resources/Images/Sprites/golem_3.png"))
		throw "ERROR LOADING SPRITE GOLEM";
	if (!textures["WRAITH_1"].loadFromFile("Resources/Images/Sprites/wraith_1.png"))
		throw "ERROR LOADING SPRITE WRAITH";
	if (!textures["WRAITH_2"].loadFromFile("Resources/Images/Sprites/wraith_2.png"))
		throw "ERROR LOADING SPRITE WRAITH";
	if (!textures["WRAITH_3"].loadFromFile("Resources/Images/Sprites/wraith_3.png"))
		throw "ERROR LOADING SPRITE WRAITH";
	if (!textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/ogr_sheet.png"))
		throw "ERROR LOADING SPRITE PLAYER";
	if (!textures["SCROLL"].loadFromFile("Resources/Images/GUI/scroll.png"))
		throw "ERROR LOADING SCROLL";
}
void GameState::updateInput(const float& dTime)
{
	bool isPressed = false;
	if (player->isAttacking) return;
	window->getSize();
	if (escapeTimer != 0) {
		escapeTimer -= dTime;
		if (escapeTimer < 0) escapeTimer = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))) {
		player->move(dTime, -1.f, 0.f, 'l', window->getSize()); // ZMIENIĆ OBJECT NA STRUKTURE DANYCH TRZUMAJACA OBIEKTY
		if (!isPressed) {
			player->setFacing(0);
			player->animationComponent->play("WALK_LEFT", dTime);
			isPressed = true;
		}
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))) {
		player->move(dTime, 1.f, 0.f, 'r', window->getSize());
		if (!isPressed) {
			player->setFacing(1);
			player->animationComponent->play("WALK_RIGHT", dTime);
			isPressed = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))) {
		player->move(dTime, 0.f, -1.f, 'u', window->getSize());
		if (!isPressed) {
			if (player->getFacing()) {
				player->animationComponent->play("WALK_RIGHT", dTime);
			}
			else {
				player->animationComponent->play("WALK_LEFT", dTime);
			}
			isPressed = true;
		}
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))) {
		player->move(dTime, 0.f, 1.f, 'd', window->getSize());
		if (!isPressed) {
			if (player->getFacing()) {
				player->animationComponent->play("WALK_RIGHT", dTime);
			}
			else {
				player->animationComponent->play("WALK_LEFT", dTime);
			}
			isPressed = true;
		}
		
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key(keybinds.at("ATTACK"))))) {
		player->makeAttack = true;
		if (!isPressed) {
			isPressed = true;
		}
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key(keybinds.at("PICK"))))) {
		pickItem();
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key(keybinds.at("ESCAPE")))) && !escapeTimer) {
		escapeTimer = 1;
		states->push(new PauseState(window, &keys, states, music));
	}
	if (!isPressed) {
		if (player->getFacing()) {
			player->animationComponent->play("IDLE_RIGHT", dTime);
		}
		else {
			player->animationComponent->play("IDLE_LEFT", dTime);
		}
	}
}
void GameState::checkDeath() {
	//TU JEST FIXED MAX HP I TZREBA UWAZAC!!!!!!!!!!!!!!!
	if (player->hp <= 0) {
		states->pop();
		int diff = 1;
		if (difficulty == 1) diff = 2;
		if (difficulty > 1.1) diff = 3;
		states->push(new EndGameState(window, &keys, states, currentWave, diff, music));	 
	}
}
void GameState::pickItem() {
	for (auto it = items.begin(); it != items.end(); it++)
	{
		if (player->getHitBox().intersects((*it)->getBox())) {
			player->addItem(**it);
			
			//DEL ITEM
			it = items.erase(it);
			if (it == items.end()) break;
		}
	}
}
void GameState::initPlayerPanel() {
	float playerPanelWidth = static_cast<float>(window->getSize().x) / 5;
	float playerPanelHeight = playerPanelWidth*0.3;
	playerPanel.setSize(sf::Vector2f(playerPanelWidth, playerPanelHeight));
	playerPanel.setTexture(&textures["SCROLL"]);
	playerPanel.setPosition(sf::Vector2f(static_cast<float>(window->getSize().x) - playerPanel.getLocalBounds().width,
		static_cast<float>(window->getSize().y) - playerPanel.getLocalBounds().height));

	//Texts
	hpText.setCharacterSize(16);
	hpText.setFillColor(sf::Color::Black);
	hpText.setFont(font);
	hpText.setPosition(sf::Vector2f(playerPanel.getPosition().x+0.05*playerPanel.getLocalBounds().width, 
		playerPanel.getPosition().y + 0.1 * playerPanel.getLocalBounds().height));
	asText.setCharacterSize(16);
	asText.setFillColor(sf::Color::Black);
	asText.setFont(font);
	asText.setPosition(sf::Vector2f(playerPanel.getPosition().x + 0.05 * playerPanel.getLocalBounds().width,
		playerPanel.getPosition().y + 0.4 * playerPanel.getLocalBounds().height));
	msText.setCharacterSize(16);
	msText.setFillColor(sf::Color::Black);
	msText.setFont(font);
	msText.setPosition(sf::Vector2f(playerPanel.getPosition().x + 0.05 * playerPanel.getLocalBounds().width,
		playerPanel.getPosition().y + 0.7 * playerPanel.getLocalBounds().height));
}

void GameState::initItemDescription() {
	itemDescriptionRect.setFillColor(sf::Color(222, 218, 193));
	itemDescription.setFillColor(sf::Color::Black);
	itemDescription.setFont(font);
	itemDescription.setCharacterSize(16);
}
void GameState::renderItems(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter) {\
	
	for (auto it = items.begin(); it != items.end(); it++)
	{
		(*it)->render(target, shader, playerCenter);
	}
	//RENDER DESC
	for (auto it = items.begin(); it != items.end(); it++)
	{
		if ((*it)->getBox().contains(mousePosView)) {
			target->draw(itemDescriptionRect);
			target->draw(itemDescription);
		}
	}
}
void GameState::renderEnemies(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter)
{
	for (auto it = enemies.begin(); it != enemies.end(); it++)
	{
		(*it)->render(target, shader, playerCenter);
	}
}
void GameState::renderRangedEnemies(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter)
{
	for (auto it = rangedEnemies.begin(); it != rangedEnemies.end(); it++)
	{
		(*it)->render(target, shader, playerCenter);
	}
	for (auto it = orbs.begin(); it != orbs.end(); it++)
	{
		(*it)->render(window, shader, playerCenter);
	}
}
void GameState::initEnemies()
{
	sf::Vector2u windowSize = window->getSize();
	for (int i = 1; i <= (currentWave+1)/2; i++){
		std::string tex = "GOLEM_";
		tex += std::to_string(rand()%3+1);
		enemies.push_back(new Enemy(ceil(difficulty*(18 + rand() % (i * 5))), 1.5, ceil(difficulty*i), rand() % 35 + 38, &textures[tex], windowSize, player));
	}
	for (int i = 1; i <= currentWave/2; i++) {
		std::string tex = "WRAITH_";
		tex += std::to_string(rand() % 3 + 1);
		rangedEnemies.push_back(new EnemyRanged(ceil(difficulty * (18 + rand() % (i * 5))), 2, ceil(difficulty*2 * i), 100 /*rand() % 35 + 38*/, &textures[tex], windowSize, player));
	}
}
void GameState::backgroundInit(sf::RenderTarget* target, int diff)
{
	switch (diff) {
	case 1:
		if (!textures["BACKGROUND"].loadFromFile("Resources/Images/Background/game_easy_bg.png"))
			throw "ERROR LOADING BACKGROUND";
		break;
	case 2:
		if (!textures["BACKGROUND"].loadFromFile("Resources/Images/Background/game_medium_bg.png"))
			throw "ERROR LOADING BACKGROUND";
		break;
	case 3:
		if (!textures["BACKGROUND"].loadFromFile("Resources/Images/Background/game_hard_bg.png"))
			throw "ERROR LOADING BACKGROUND";
		break;
	}
	
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	background.setTexture(&textures.at("BACKGROUND"));
}
void GameState::dropItem(const int x, const int y) {
    int chance = rand() % 100 + 1;
    if (chance > 50) return;

	int textureNumber = rand() % 4 + 1;
	int type = rand() % 3;
	int value = currentWave + rand() % currentWave/2;
	std::stringstream path;
	path << "Resources/Images/Alchemy/" << type << textureNumber << ".png";

	sf::Texture tempItem;
	if (!tempItem.loadFromFile(path.str())) {
		throw("ERROR RADING ALCHEMY");
	}
	items.push_back(new Item(x, y, type, value, tempItem));
}
void GameState::updateItems(const float& dTime)
{
	//UPDATE
	for (auto it = items.begin(); it != items.end(); it++)
	{
		(*it)->update(dTime);
	}
	//CHECK IF DEATH 
	for (auto it = items.begin(); it != items.end(); it++)
	{
		if (!(*it)->isAlive()) {
			it = items.erase(it);
			if (it == items.end()) break;
		}
	}
	//CHECK IF HOVER
	for (auto it = items.begin(); it != items.end(); it++)
	{
		if ((*it)->getBox().contains(mousePosView)) {
			itemDescription.setString((*it)->getText());
			if((*it)->getType() == 0) itemDescriptionRect.setSize(sf::Vector2f(itemDescription.getLocalBounds().width * 1.1, itemDescription.getLocalBounds().height * 1.8));
			else itemDescriptionRect.setSize(sf::Vector2f(itemDescription.getLocalBounds().width * 1.1, itemDescription.getLocalBounds().height * 1.5));
			itemDescriptionRect.setPosition(sf::Vector2f(mousePosView.x+10, mousePosView.y));
			itemDescription.setPosition(sf::Vector2f(itemDescriptionRect.getPosition().x + itemDescriptionRect.getLocalBounds().width * 0.05,
				itemDescriptionRect.getPosition().y + itemDescriptionRect.getLocalBounds().height * 0.05));
		}
	}
}
void GameState::updateEnemies(const float& dTime, sf::Vector2u windowSize)
{
	//CHECK DEATH
	for (auto it = enemies.begin(); it != enemies.end(); it++)
	{
		if ((*it)->hp <= 0) {
			int x, y;
			x = (*it)->getPosition().x;
			y = (*it)->getPosition().y;
			it = enemies.erase(it);
			dropItem(x, y);
			if (sound.getStatus() != sf::Sound::Status::Playing) {
				sound.play();
			}
			if (it == enemies.end()) break;
			
			//ITEM DROP
			
		}
	}
	if (rangedEnemies.empty() && enemies.empty()) {
		currentWave++;
		initEnemies();
	}
	//UPDATE
	sf::Vector2f currPosition = player->getPosition();
	for (auto it = enemies.begin(); it != enemies.end(); it++)
	{
		(*it)->update(dTime, windowSize, player);
	}
	//ATTACK
	for (auto it = enemies.begin(); it != enemies.end(); it++)
	{
		player->hp -= (*it)->attack(player, dTime);
	}
}
void GameState::updateRangedEnemies(const float& dTime, sf::Vector2u windowSize)
{
	//CHECK DEATH
	for (auto it = rangedEnemies.begin(); it != rangedEnemies.end(); it++)
	{
		if ((*it)->hp <= 0) {
			int x, y;
			x = (*it)->getPosition().x;
			y = (*it)->getPosition().y;
			it = rangedEnemies.erase(it);
			dropItem(x, y);
			if (sound.getStatus() != sf::Sound::Status::Playing) {
				sound.play();
			}
			if (it == rangedEnemies.end()) break;

			//ITEM DROP

		}
	}
	if (rangedEnemies.empty() && enemies.empty()) {
		currentWave++;
		initEnemies();
	}
	//UPDATE
	sf::Vector2f currPosition = player->getPosition();
	for (auto it = rangedEnemies.begin(); it != rangedEnemies.end(); it++)
	{
		(*it)->update(dTime, windowSize, player);
	}
	//ATTACK
	for (auto it = rangedEnemies.begin(); it != rangedEnemies.end(); it++)
	{
		(*it)->attack(player, dTime, &orbs, windowSize);
	}

	//Orbs
	for (auto it = orbs.begin(); it != orbs.end(); it++)
	{
		int orbReturned = (*it)->update(dTime, player->getHitBox());
		if (orbReturned > 0 ) {
			player->hp -= orbReturned;
			it = orbs.erase(it);
			if (it == orbs.end()) break;
		}
	}
}
void GameState::printWave(sf::RenderTarget* target) {
	sf::Text waveText;
	waveText.setPosition(0, 0);
	waveText.setCharacterSize(20);
	waveText.setFont(font);
	std::stringstream str1;
	str1 << "Current wave: " << " " << currentWave;
	waveText.setString(str1.str());
	target->draw(waveText);
}
void GameState::renderPlayerPanelInfo(sf::RenderTarget* target) {
	std::stringstream hpSS; hpSS << "Health: " << player->hp;
	hpText.setString(hpSS.str());
	target->draw(hpText);
	std::stringstream asSS; asSS << "Attack strength: 10"; if(player->getItemAS()) asSS<<" + " << player->getItemAS()->getValue();
	asText.setString(asSS.str());
	target->draw(asText);
	std::stringstream msSS; msSS << "Movement speed: 100"; if (player->getItemMS()) msSS << " + " << player->getItemMS()->getValue();
	msText.setString(msSS.str());
	target->draw(msText);
}
void GameState::update(const float& dTime)
{


	updateMousePosition();
	updateInput(dTime);
	updateItems(dTime);
	player->update(dTime, &enemies, &rangedEnemies);
	updateEnemies(dTime, window->getSize());
	updateRangedEnemies(dTime, window->getSize());
	checkDeath();
}
void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	core_shader.setUniform("hasTexture", true);
	core_shader.setUniform("light", player->getCenter());

	target->draw(background, &core_shader);

	renderItems(target, &core_shader, player->getCenter());
	renderEnemies(target, &core_shader, player->getCenter());
	renderRangedEnemies(target, &core_shader, player->getCenter());
	player->render(target, &core_shader);

	printWave(target);
	target->draw(playerPanel);
	renderPlayerPanelInfo(window);
	player->renderItems(window);

}
