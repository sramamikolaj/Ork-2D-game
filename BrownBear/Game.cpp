#include "Game.h"
#include <fstream>
#include <sstream>
#include <utility>
Game::Game()
{
    openFile();
    getSettings(file, "settings");
    getSettings(keyFile, "keys");
    windowInitializer();
    keysInitializer();
    stateInitializer(); 
    initMusic();
}

Game::~Game()
{
	delete window;
    while (!states.empty()) {
        delete states.top();
        states.pop();
    }
}

sf::Keyboard::Key Game::getKey(string key)
{
    if (key == "A") {
        return sf::Keyboard::A;
    }
    if (key == "B") {
        return sf::Keyboard::B;
    }
    if (key == "C") {
        return sf::Keyboard::C;
    }
    if (key == "D") {
        return sf::Keyboard::D;
    }
    if (key == "E") {
        return sf::Keyboard::E;
    }
    if (key == "F") {
        return sf::Keyboard::F;
    }
    if (key == "G") {
        return sf::Keyboard::G;
    }
    if (key == "H") {
        return sf::Keyboard::H;
    }
    if (key == "I") {
        return sf::Keyboard::I;
    }
    if (key == "J") {
        return sf::Keyboard::J;
    }
    if (key == "K") {
        return sf::Keyboard::K;
    }
    if (key == "L") {
        return sf::Keyboard::L;
    }
    if (key == "M") {
        return sf::Keyboard::M;
    }
    if (key == "N") {
        return sf::Keyboard::N;
    }
    if (key == "O") {
        return sf::Keyboard::O;
    }
    if (key == "P") {
        return sf::Keyboard::P;
    }
    if (key == "R") {
        return sf::Keyboard::R;
    }
    if (key == "S") {
        return sf::Keyboard::S;
    }
    if (key == "T") {
        return sf::Keyboard::T;
    }
    if (key == "P") {
        return sf::Keyboard::P;
    }
    if (key == "R") {
        return sf::Keyboard::R;
    }
    if (key == "S") {
        return sf::Keyboard::S;
    }
    if (key == "T") {
        return sf::Keyboard::T;
    }
    if (key == "U") {
        return sf::Keyboard::U;
    }
    if (key == "V") {
        return sf::Keyboard::V;
    }
    if (key == "W") {
        return sf::Keyboard::W;
    }
    if (key == "Y") {
        return sf::Keyboard::Y;
    }
    if (key == "X") {
        return sf::Keyboard::X;
    }
    if (key == "Z") {
        return sf::Keyboard::Z;
    }
    if (key == "Space") {
        return sf::Keyboard::Space;
    }
}


void Game::stateInitializer()
{
    states.push(new MainMenuState(window, &keys, &states, &music));
}

void Game::updateDTime()
{
    dTime = dClock.restart().asSeconds();
    //system("cls");
    //std::cout << dTime << std::endl;
}
void Game::getSettings(fstream& toOpen, string type)
{
    std::string setting, value, line;
    std::istringstream iss;
    while (!toOpen.eof()) {
        getline(toOpen, line);
        std::istringstream iss(line);
        getline(iss, setting, '=');
        getline(iss, value);
        if (type == "settings") settings.insert(std::pair<std::string, int>(setting, stoi(value)));
        else if (type == "keys") keybinds.insert(std::pair<std::string, sf::Keyboard::Key>(setting, getKey(value)));
        else throw "ERROR TYPE";
    }
}
void Game::initMusic() {
    if (!music.openFromFile("Resources/Sounds/music_menu.ogg"))
        throw("ERORR MUSIC");
    music.setVolume(float(settings["music_vlm"]));
    music.setLoop(true);
}
void Game::openFile() {
    file.open("Datafiles/settings.ini");
    if (!file) throw "FILE ERROR";
    keyFile.open("Datafiles/keybinds.ini");
    if (!keyFile) throw "FILE ERROR";
}
void Game::windowInitializer()
{
    
    //videoModes = sf::VideoMode::getFullscreenModes();


    std::string title = "Ork";
    bool fullscreen = settings["fullscreen"];
    int framerate = settings["frame_limit"];
    bool vertical_sync = settings["vertical_sync"];
    unsigned antialising = 0;

    sf::VideoMode bounds = sf::VideoMode(settings["width"], settings["height"]);
    //sf::VideoMode bounds = sf::VideoMode(1920, 1080);
 
    
    windowSetting.antialiasingLevel = antialising;
    if(fullscreen)
        window = new sf::RenderWindow(bounds, title, sf::Style::Fullscreen, windowSetting);
    else
        window = new sf::RenderWindow(bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSetting);
    if(framerate)window->setFramerateLimit(framerate);
    if(vertical_sync)window->setVerticalSyncEnabled(vertical_sync);
    


    sf::Image icon;
    icon.loadFromFile("Resources/Icons/icon.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    /*USTAWIENIA GRAFICZNE:
    200x200
    120 frame limit
    VerticalSync off
    */
}

void Game::keysInitializer()
{

    keys["W"] = keybinds["up"];
    keys["A"] = keybinds["left"];
    keys["S"] = keybinds["down"];
    keys["D"] = keybinds["right"];
    keys["E"] = keybinds["pick_up"];
    keys["ESC"] = sf::Keyboard::Escape;
    keys["Space"] = keybinds["attack"];
}

void Game::updateSFMLEvents()
{
    
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
    //window->clear();
    //window->display();
}

void Game::run()
{
    while (window->isOpen())
    {
        if (music.getStatus() != sf::SoundSource::Playing) music.play();
        updateDTime();
        update();    
        render();
    }

}

void Game::update()
{
    updateSFMLEvents();
    if (!states.empty()) {
        states.top()->update(dTime);

        if (states.top()->getQuit()) {
            states.top()->endState();
            delete states.top();
            states.pop();
        }
    }
    else {
        window->close();
    }
}

void Game::render()
{
    window->clear();
    if (!states.empty()) 
        states.top()->render(window);
    window->display();


}
