#ifndef LEVEL_H
#define LEVEL_H

#include "TextureManager.h"


// Simple class to load and manage the level
class Level : public sf::Drawable, public sf::Transformable {
private:
	sf::VertexArray m_vertecies;
	sf::Vector2u m_levelSize;
	sf::Vector2u m_tileSize;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	// Loads the level and initilizes the vertecies
	bool loadLevel(const std::string& levelFile);

	// Getters
	sf::Vector2u getLevelSize() const { return m_levelSize; }
	sf::Vector2u getTileSize() const { return m_tileSize; }

	// Returns true if the tile is solid
	bool isTileSolid(const sf::Vector2i& tilePos) const;
};


#endif // !LEVEL_H