#include "Level.h"


// Loads the level and initializes the textures
bool Level::loadLevel(const std::string& levelFile) {
	// Opens the level file
	std::ifstream ifs{ levelFile };
	if (!ifs.is_open()) return false;

	// Reads the level and tile size from the file
	ifs >> m_tileSize.x >> m_tileSize.y;
	ifs >> m_levelSize.x >> m_levelSize.y;

	// Resizes the vertecies based on the size of the level
	m_vertecies.setPrimitiveType(sf::Quads);
	m_vertecies.resize(4 * m_levelSize.x * m_levelSize.y);

	// Reads the level data and initializes the vertecies
	for (size_t j = 0; j < m_levelSize.y; ++j) {
		for (size_t i = 0; i < m_levelSize.x; ++i) {
			// Gets the value of the current tile
			int tileValue = 0;
			ifs >> tileValue;

			// Calculates the tile's texture coordinates and rect
			sf::Vector2f tileTextureCoords;
			tileTextureCoords.x = (tileValue % (TextureManager::getTexture().texture.getSize().x / m_tileSize.x)) * m_tileSize.x;
			tileTextureCoords.y = (tileValue / (TextureManager::getTexture().texture.getSize().y / m_tileSize.y)) * m_tileSize.y;
			sf::FloatRect tileTextureRect{ tileTextureCoords, sf::Vector2f{ m_tileSize } };

			// Gets a pointer to the current tile quad
			sf::Vertex* tileQuad = &m_vertecies[(i + j * m_levelSize.x) * 4];

			// Calculates the tile's position
			tileQuad[0].position = sf::Vector2f{ (i + 0.0f) * m_tileSize.x, (j + 0.0f) * m_tileSize.y };
			tileQuad[1].position = sf::Vector2f{ (i + 1.0f) * m_tileSize.x, (j + 0.0f) * m_tileSize.y };
			tileQuad[2].position = sf::Vector2f{ (i + 1.0f) * m_tileSize.x, (j + 1.0f) * m_tileSize.y };
			tileQuad[3].position = sf::Vector2f{ (i + 0.0f) * m_tileSize.x, (j + 1.0f) * m_tileSize.y };

			// Assigns the tile's texture coordinates
			tileQuad[0].texCoords = { tileTextureRect.left,                         tileTextureRect.top                          };
			tileQuad[1].texCoords = { tileTextureRect.left + tileTextureRect.width, tileTextureRect.top                          };
			tileQuad[2].texCoords = { tileTextureRect.left + tileTextureRect.width, tileTextureRect.top + tileTextureRect.height };
			tileQuad[3].texCoords = { tileTextureRect.left,                         tileTextureRect.top + tileTextureRect.height };
		}
	}

	return true;
}

// Returns true if the tile is solid
bool Level::isTileSolid(const sf::Vector2i& tilePos) const {
	size_t tileIndex = (tilePos.x / 32 + tilePos.y / 32 * m_levelSize.x) * 4;
	if (m_vertecies[tileIndex].texCoords == sf::Vector2f{ 0.0f, 0.0f }) {
		return false;
	} else {
		return true;
	}
}


// Renders the level onto the target
void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// Applies the transformation and the texture
	states.transform *= getTransform();
	states.texture = &TextureManager::getTexture().texture;

	// Renders the vertecies onto the target
	target.draw(m_vertecies, states);
}
