#ifndef ENTITY_H
#define ENTITY_H

#include "Level.h"


// Abstarct base class for game entities to inherit from
class Entity : public sf::Drawable, public sf::Transformable {
protected:
	enum class Collisions {
		OUT_LEFT,
		OUT_RIGHT,
		OUT_BOTTOM,
		LEVEL_LEFT,
		LEVEL_RIGHT,
		LEVEL_TOP,
		LEVEL_BOTTOM,
	};

protected:
	sf::VertexArray m_vertecies;
	sf::Vector2f m_velocity;

protected:
	// Initializes the vertecies of the entity
	virtual void initialize() = 0;
	// Checks for collisions and if the entity is out of bounds
	void checkCollisions(sf::Vector2f& futurePos, const Level& level);
	// Resolves the collisions
	virtual void resolveCollisions(sf::Vector2f& futurePos, const Level& level, const Collisions& collision) = 0;
	// Renders the entity onto the target
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	// Constructor
	Entity() { }

	// Getters and setters
	sf::Vector2f getVelocity() const { return m_velocity; }
	void setVelocity(const sf::Vector2f& velocity) { m_velocity = velocity; }
	void setVelocity(float velocityX, float velocityY) { m_velocity = { velocityX, velocityY }; }

	// Updates the position of the entity and checks for collisions with the level
	virtual void update(const Level& level, float deltaTime);
};


#endif // !ENTITY_H