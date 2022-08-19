#ifndef APPLICATION_H
#define APPLICATION_H

#include "Level.h"
#include "Player.h"
#include "Enemy.h"


// Main class to start and manage the game
class Application {
private:
	sf::RenderWindow* m_window;                               // The window that everything is rendered onto
	sf::Clock m_clock;                                        // The clock to calculate the time between frames

	Level m_level;                                            // The level that the player will play in
	Player m_player;                                          // The player that the user will control
	std::vector<Enemy> m_enemies;                             // The enemies that will make the level harder for user

	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_gameOverText;

	size_t m_score = 0;
	double m_timeRemaining = 100;

private:
	// Initializes the application
	void initialize();

	// Handles the inputs from the user
	void handleInputs();
	// Updates the entities 
	void update();
	// Renders the entities onto the window
	void render();

public:
	// Constructor
	Application();
	// Destructor
	~Application();

	// Starts the application
	void run();
};


#endif // !APPLICATION_H