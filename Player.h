#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"


// Class to manage the player
class Player : public Entity {
private:
	sf::Vector2u m_tileSize;
	std::array<sf::FloatRect, 4> m_textureRects;

public:
	int lives = 3;

private:
	// Initializes the player's vertecies
	virtual void initialize();
	// Checks for collisions between the player and level and enemies
	virtual void resolveCollisions(sf::Vector2f& futurePos, const Level& level, const Collisions& collision);

public:
	// Constructors
	Player() { };
	Player(const sf::Vector2f& position, const sf::Vector2u& tileSize);

	// Updates the player's position
	virtual void update(const Level& level, float deltaTime);
};


#endif // !PLAYER_H