#pragma once
#include "Enemy.h"
#include <list>
#include "Orb.h"
class EnemyRanged :
    public Entity
{
protected:
    bool isAttacking;
    bool madeHit;
    float attackTimer;

    sf::Vector2i destination;

    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;

    void setOrigin();
    void setHP(unsigned toSet);

    void generateDestination(sf::Vector2u windowSize);

    void initVariables(unsigned hp_, unsigned cd_, unsigned str_);
    virtual void soundInit();
    virtual void initAnimations();
    void setSpeed(float speed);
    void updateBoxes();
    virtual void move(const float& dTime, sf::Vector2u windowSize, Entity* player);
    void initBoxes();
    
public:
    EnemyRanged(unsigned hp, unsigned cd_, unsigned str, float speed, sf::Texture* texture_, sf::Vector2u windowSize, Entity* player);

    void attack(Entity* player, const float& dTime, std::list<Orb*>* orbs, sf::Vector2u windowSize);
    virtual void update(const float& dTime, sf::Vector2u windowSize, Entity* player);
    void render(sf::RenderTarget* target, sf::Shader* shader, sf::Vector2f playerCenter);    
};

