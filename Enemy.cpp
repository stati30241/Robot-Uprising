#include "Enemy.h"


// Constructor
Enemy::Enemy(const sf::Vector2f& position, const sf::Vector2u& tileSize) 
	: m_tileSize{ tileSize } {
	m_velocity.x = -100.0f;
	setPosition(position);
	initialize();
}


// Initializes the vertecies of the enemy
void Enemy::initialize() {
	// Resizes the vertecies
	m_vertecies.setPrimitiveType(sf::Quads);
	m_vertecies.resize(4);

	// Calculates the position of the enemy
	m_vertecies[0].position = { 0.0f,                             0.0f };
	m_vertecies[1].position = { static_cast<float>(m_tileSize.x),                             0.0f };
	m_vertecies[2].position = { static_cast<float>(m_tileSize.x), static_cast<float>(m_tileSize.y) };
	m_vertecies[3].position = { 0.0f,                             static_cast<float>(m_tileSize.y) };

	// Initializes the texture coords for the enemy
	m_textureRect = { { 32.0f, 64.0f }, sf::Vector2f{ m_tileSize } };
}


void Enemy::resolveCollisions(sf::Vector2f& futurePos, const Level& level, const Collisions& collision) {
	switch (collision) {
	// If the enemy is out of bounds on the left side
	case Collisions::OUT_LEFT:
		futurePos.x = static_cast<int>(futurePos.x) / level.getTileSize().x * level.getTileSize().x;
		m_velocity.x *= -1.0f;
		break;

	// If the enemy is out of bounds on the right side
	case Collisions::OUT_RIGHT:
		futurePos.x = static_cast<int>(futurePos.x) / level.getTileSize().x * level.getTileSize().x;
		m_velocity.x *= -1.0f;
		break;

	// If the enemy has fallen out of the level
	case Collisions::OUT_BOTTOM:
		setPosition(0.0f, 400.0f);
		futurePos = { 0.0f, 400.0f };
		m_velocity.x = 0.0f;
		break;

	// If the enemy is colliding with the level on the left
	case Collisions::LEVEL_LEFT:
		futurePos.x = static_cast<int>(futurePos.x) / level.getTileSize().x * level.getTileSize().x + level.getTileSize().x;
		m_velocity.x *= -1.0f;
		break;

	// If the enemy is colliding with the level on the right
	case Collisions::LEVEL_RIGHT:
		futurePos.x = static_cast<int>(futurePos.x) / level.getTileSize().x * level.getTileSize().x;
		m_velocity.x *= -1.0f;
		break;

	// If the enemy is colliding with the level on the top
	case Collisions::LEVEL_TOP:
		futurePos.y = static_cast<int>(futurePos.y) / level.getTileSize().y * level.getTileSize().y + level.getTileSize().y;
		m_velocity.y = 0.0f;
		break;

	// If the enemy is colliding with the level on the bottom
	case Collisions::LEVEL_BOTTOM:
		futurePos.y = static_cast<int>(futurePos.y) / level.getTileSize().y * level.getTileSize().y;
		m_velocity.y = 0.0f;
		break;
	}
}


// Updates the enemy's texture
void Enemy::update(const Level& level, float deltaTime) {
	// Applies the texture to the vertecies
	if (m_velocity.x >= 0.0f) {
		m_vertecies[0].texCoords = { m_textureRect.left,                        m_textureRect.top                        };
		m_vertecies[1].texCoords = { m_textureRect.left + m_textureRect.width,  m_textureRect.top                        };
		m_vertecies[2].texCoords = { m_textureRect.left + m_textureRect.width,  m_textureRect.top + m_textureRect.height };
		m_vertecies[3].texCoords = { m_textureRect.left,                        m_textureRect.top + m_textureRect.height };
	} else {
		m_vertecies[1].texCoords = { m_textureRect.left,                        m_textureRect.top                        };
		m_vertecies[0].texCoords = { m_textureRect.left + m_textureRect.width,  m_textureRect.top                        };
		m_vertecies[3].texCoords = { m_textureRect.left + m_textureRect.width,  m_textureRect.top + m_textureRect.height };
		m_vertecies[2].texCoords = { m_textureRect.left,                        m_textureRect.top + m_textureRect.height };
	}

	// Updates the entity
	Entity::update(level, deltaTime);
}
