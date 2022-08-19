#include "Entity.h"


// Checks for collisions and if the entity is out of bounds
void Entity::checkCollisions(sf::Vector2f& futurePos, const Level& level) {
	// Checks if the entity is out of bounds
	if (futurePos.x < 0.0f) {
		resolveCollisions(futurePos, level, Collisions::OUT_LEFT);
	} else if (futurePos.x + level.getTileSize().x > level.getLevelSize().x * level.getTileSize().x) {
		resolveCollisions(futurePos, level, Collisions::OUT_RIGHT);
	}

	// Checks if the entity has fallen out of the level
	if (futurePos.y + level.getTileSize().y >= level.getLevelSize().y * level.getTileSize().y) {
		resolveCollisions(futurePos, level, Collisions::OUT_BOTTOM);
		return;
	}

	// Checks for collisions on the left
	if (m_velocity.x < 0.0f) {
		const sf::Vector2i topLeft = { static_cast<int>(futurePos.x), static_cast<int>(getPosition().y) };
		const sf::Vector2i bottomLeft = { static_cast<int>(futurePos.x), static_cast<int>(getPosition().y + level.getTileSize().y * 0.99f) };
		if (level.isTileSolid(topLeft) || level.isTileSolid(bottomLeft)) {
			resolveCollisions(futurePos, level, Collisions::LEVEL_LEFT);
		}
	}

	// Checks for collsions on the right
	else {
		const sf::Vector2i topRight = { static_cast<int>(futurePos.x + level.getTileSize().x), static_cast<int>(getPosition().y) };
		const sf::Vector2i bottomRight = { static_cast<int>(futurePos.x + level.getTileSize().x), static_cast<int>(getPosition().y + level.getTileSize().y * 0.99f) };
		if (level.isTileSolid(topRight) || level.isTileSolid(bottomRight)) {
			resolveCollisions(futurePos, level, Collisions::LEVEL_RIGHT);
		}
	}

	// Checks for collisions on the top
	if (m_velocity.y < 0.0f) {
		const sf::Vector2i topLeft = { static_cast<int>(futurePos.x), static_cast<int>(futurePos.y) };
		const sf::Vector2i topRight = { static_cast<int>(futurePos.x + level.getTileSize().x * 0.99f), static_cast<int>(futurePos.y) };
		if (level.isTileSolid(topLeft) || level.isTileSolid(topRight)) {
			resolveCollisions(futurePos, level, Collisions::LEVEL_TOP);
		}
	}

	// Checks for collisions on the bottom
	else {
		const sf::Vector2i bottomLeft = { static_cast<int>(futurePos.x), static_cast<int>(futurePos.y + level.getTileSize().y) };
		const sf::Vector2i bottomRight = { static_cast<int>(futurePos.x + level.getTileSize().x * 0.99f), static_cast<int>(futurePos.y + level.getTileSize().y) };
		if (level.isTileSolid(bottomLeft) || level.isTileSolid(bottomRight)) {
			resolveCollisions(futurePos, level, Collisions::LEVEL_BOTTOM);
		}
	}
}


// Renders the entity onto the target
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// Applies the transformation and the texture
	states.transform *= getTransform();
	states.texture = &TextureManager::getTexture().texture;

	// Renders the vertecies onto the target
	target.draw(m_vertecies, states);
}


// Updates the position of the entity and checks for collisions with the level
void Entity::update(const Level& level, float deltaTime) {
	// Implements gravity
	m_velocity.y += 1000.0f * deltaTime;

	// Calculates the position of the entity in the next frame
	sf::Vector2f futurePos = getPosition() + m_velocity * deltaTime;

	// Checks for collisions between the entity and the level and resolves them
	checkCollisions(futurePos, level);

	// Updates the postition of the entity
	setPosition(futurePos);
}
