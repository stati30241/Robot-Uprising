#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"


class Enemy : public Entity {
private:
	sf::Vector2u m_tileSize;
	sf::FloatRect m_textureRect;

private:
	// Initializes the vertecies of the enemy
	virtual void initialize();
	// Checks for collision with the level and player
	virtual void resolveCollisions(sf::Vector2f& futurePos, const Level& level, const Collisions& collision);

public:
	// Constructor
	Enemy(const sf::Vector2f& position, const sf::Vector2u& tileSize);

	// Updates the enemy's texture
	virtual void update(const Level& level, float deltaTime);
};


#endif // !ENEMY_H