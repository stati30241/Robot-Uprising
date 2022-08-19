#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


// Simple singleton class to manage the texture atlas
class TextureManager {
public:
	sf::Texture texture;

private:
	// Constructor
	TextureManager(const std::string& filename) {
		texture.loadFromFile(filename);
	}

	// Prevents the compiler from generating copies
	TextureManager(const TextureManager& copy);
	TextureManager& operator=(const TextureManager& copy);

public:
	// The only method to access the texture
	static TextureManager& getTexture(const std::string& filename = "") {
		static TextureManager instance{ filename };
		return instance;
	}

};


#endif // !TEXTURE_MANAGER_H