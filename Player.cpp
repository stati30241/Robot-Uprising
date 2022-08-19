#include "Player.h"


// Constructor
Player::Player(const sf::Vector2f& position, const sf::Vector2u& tileSize)
	: m_tileSize{ tileSize } {
	setPosition(position);
	initialize();
}


// Initializes the player's vertecies
void Player::initialize() {
	// Resizes the vertecies
	m_vertecies.setPrimitiveType(sf::Quads);
	m_vertecies.resize(4);

	// Calculates the position of the player
	m_vertecies[0].position = {                             0.0f,                             0.0f };
	m_vertecies[1].position = { static_cast<float>(m_tileSize.x),                             0.0f };
	m_vertecies[2].position = { static_cast<float>(m_tileSize.x), static_cast<float>(m_tileSize.y) };
	m_vertecies[3].position = {                             0.0f, static_cast<float>(m_tileSize.y) };

	// Initializes the textures for the player
	m_textureRects.at(0) = { { 64.0f,  32.0f }, sf::Vector2f{ m_tileSize } };
	m_textureRects.at(1) = { { 96.0f,  32.0f }, sf::Vector2f{ m_tileSize } };
	m_textureRects.at(2) = { { 128.0f, 32.0f }, sf::Vector2f{ m_tileSize } };
	m_textureRects.at(3) = { { 0.0f,   64.0f }, sf::Vector2f{ m_tileSize } };
}


// Checks for collisions between the player and level and enemies
void Player::resolveCollisions(sf::Vector2f& futurePos, const Level& level, const Collisions& collision) {
	switch (collision) {
	// If the player is out of bounds on the left side
	case Collisions::OUT_LEFT:
		futurePos.x = 0.0f;
		m_velocity.x = 0.0f;
		break;

	// If the player is out of bounds on the right side
	case Collisions::OUT_RIGHT:
		futurePos.x = level.getLevelSize().x * level.getTileSize().x - level.getTileSize().x;
		m_velocity.x = 0.0f;
		break;

	// If the player has fallen out of the level
	case Collisions::OUT_BOTTOM:
		setPosition(0.0f, 400.0f);
		futurePos = { 0.0f, 400.0f };
		m_velocity.x = 0.0f;
		lives--;
		break;

	// If the player is colliding with the level on the left
	case Collisions::LEVEL_LEFT:
		futurePos.x = static_cast<int>(futurePos.x) / level.getTileSize().x * level.getTileSize().x + level.getTileSize().x;
		m_velocity.x = 0.0f;
		break;

	// If the player is colliding with the level on the right
	case Collisions::LEVEL_RIGHT:
		futurePos.x = static_cast<int>(futurePos.x) / level.getTileSize().x * level.getTileSize().x;
		m_velocity.x = 0.0f;
		break;

	// If the player is colliding with the level on the top
	case Collisions::LEVEL_TOP:
		futurePos.y = static_cast<int>(futurePos.y) / level.getTileSize().y * level.getTileSize().y + level.getTileSize().y;
		m_velocity.y = 0.0f;
		break;

	// If the player is colliding with the level on the bottom
	case Collisions::LEVEL_BOTTOM:
		futurePos.y = static_cast<int>(futurePos.y) / level.getTileSize().y * level.getTileSize().y;
		m_velocity.y = 0.0f;
		break;
	}
}


// Updates the player's position
void Player::update(const Level& level, float deltaTime) {
	// Implements drag so that the player doesn't slide forever
	m_velocity.x += -2.0f * m_velocity.x * deltaTime;
	if (std::fabs(m_velocity.x) <= 10.0f) {
		m_velocity.x = 0.0f;
	}

	// Finds the current texture for the player
	static float timer = 0.0f;
	sf::FloatRect currentTexture;
	if (m_velocity.y) {
		currentTexture = m_textureRects.at(1);
	} else if (!m_velocity.x) {
		currentTexture = m_textureRects.at(0);
	} else {
		if (std::sinf(timer * 30.0f) > 0.0f) {
			currentTexture = m_textureRects.at(2);
		} else {
			currentTexture = m_textureRects.at(3);
		}
		timer += deltaTime;
	}

	// Applies the texture to the vertecies
	if (m_velocity.x >= 0.0f) {
		m_vertecies[0].texCoords = { currentTexture.left,                         currentTexture.top };
		m_vertecies[1].texCoords = { currentTexture.left + currentTexture.width,  currentTexture.top };
		m_vertecies[2].texCoords = { currentTexture.left + currentTexture.width,  currentTexture.top + currentTexture.height };
		m_vertecies[3].texCoords = { currentTexture.left,                         currentTexture.top + currentTexture.height };
	} else {
		m_vertecies[1].texCoords = { currentTexture.left,                         currentTexture.top };
		m_vertecies[0].texCoords = { currentTexture.left + currentTexture.width,  currentTexture.top };
		m_vertecies[3].texCoords = { currentTexture.left + currentTexture.width,  currentTexture.top + currentTexture.height };
		m_vertecies[2].texCoords = { currentTexture.left,                         currentTexture.top + currentTexture.height };
	}

	// Updates the entity
	Entity::update(level, deltaTime);
}
