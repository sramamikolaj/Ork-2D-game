#pragma once
#include<list>
#include "Entity.h"
#include "Enemy.h"
#include "Item.h"
#include "EnemyRanged.h"
class Player :
    public Entity
{
private:
    //ITEMS
    Item* itemAS; //1
    Item* itemMS; //2
    //TEMP
    sf::RectangleShape tempRect1;
    sf::RectangleShape tempRect2;
    sf::RectangleShape tempRect3;

    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;
    sf::SoundBuffer swoshBuffer;
    sf::Sound swoshSound;

    sf::Vector2f asItemCords;
    sf::Vector2f msItemCords;
    
    void initComponents();
    void variablesInit();
    void initBoxes();

    float attackTime;
    bool madeHit;



public:
    Player(float x, float y, sf::Texture& texture_);
    ~Player();

    bool makeAttack;
    bool isAttacking;

    float getMS();
    int getAS();
    
    void setFacing(int x);
    int getFacing();
    Item* getItemAS();
    Item* getItemMS();

    void makeHit(std::list<Enemy*>* enemies, std::list<EnemyRanged*>* rangedEnemies);
    void initAnimations();
    void soundInit();
    sf::Vector2f getCenter();

    void setItemCords(sf::Vector2f asItemCords_, sf::Vector2f msItemCords_);

    void move(const float& dTime, const float dirX, const float dirY, char dir, sf::Vector2u windowSize);
    void attack(std::list<Enemy*>* enemies,  std::list<EnemyRanged*>* rangedEnemies, const float& dTime);
    void addItem(Item toAdd);

    void updateCooldown(const float& dTime);
    void updateBoxes();

    void update(const float& dTime, std::list<Enemy*>* enemies, std::list<EnemyRanged*>* rangedEnemies);
    void renderItems(sf::RenderTarget* target);
    void render(sf::RenderTarget* target, sf::Shader* shader);
};

