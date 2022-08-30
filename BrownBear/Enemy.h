#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
protected:
    bool isAttacking;
    bool madeHit;
    float attackTimer;
    //TEMp
    sf::RectangleShape tempRect1;
    sf::RectangleShape tempRect2;
    sf::RectangleShape tempRect3;

    sf::Vector2i destination;
    
    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;

    void setOrigin();
    void setHP(unsigned toSet);

    void generateDestination(Entity* player);
    void updateBoxes();

    void initVariables(unsigned hp_, unsigned cd_, unsigned str_);
    virtual void soundInit();
    virtual void initAnimations();
    void initBoxes();
    
    void setSpeed(float speed);
    virtual void move(const float& dTime, sf::Vector2u windowSize, Entity* player);
public:
    Enemy(unsigned hp, unsigned cd_, unsigned str, float speed, sf::Texture* texture_, sf::Vector2u windowSize, Entity* player);

    virtual unsigned attack(Entity* player, const float& dTime);
    virtual void update(const float& dTime, sf::Vector2u windowSize, Entity* player);
    void render(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter);
};

