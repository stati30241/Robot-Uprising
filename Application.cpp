#include "Application.h"


// Constructor
Application::Application() {
	initialize();
}


// Destructor
Application::~Application() {
	delete m_window;
}


// Initializes the application
void Application::initialize() {
	// Initializes the window
	sf::VideoMode windowVideoMode = { 1600u, 960u };
	sf::String windowTitle = "Robot Uprising";
	size_t windowStyle = 4;
	m_window = new sf::RenderWindow{ windowVideoMode, windowTitle, windowStyle };
	m_window->setVerticalSyncEnabled(true);

	// Loads the texture
	TextureManager::getTexture("texture.png");

	// Initializes the level
	m_level.loadLevel("level.txt");

	// Initlializes the player
	m_player = { { 0.0f, 400.0f }, m_level.getTileSize() };

	// Initializes the enemies
	m_enemies.clear();
	m_enemies.push_back({ { 1216.0f, 400.0f }, m_level.getTileSize() });
	m_enemies.push_back({ { 1376.0f, 400.0f }, m_level.getTileSize() });
	m_enemies.push_back({ { 3008.0f, 400.0f }, m_level.getTileSize() });
	m_enemies.push_back({ { 3104.0f, 400.0f }, m_level.getTileSize() });
	m_enemies.push_back({ { 3232.0f, 400.0f }, m_level.getTileSize() });
	m_enemies.push_back({ { 4600.0f, 600.0f }, m_level.getTileSize() });
	m_enemies.push_back({ { 4768.0f, 600.0f }, m_level.getTileSize() });
	m_enemies.push_back({ { 4928.0f, 400.0f }, m_level.getTileSize() });
	m_enemies.push_back({ { 5216.0f, 600.0f }, m_level.getTileSize() });

	// Intializes the font and text
	m_font.loadFromFile("cour.ttf");
	m_text.setFont(m_font);
	m_text.setPosition(10.0f, 10.0f);
	m_gameOverText.setFont(m_font);
	m_gameOverText.setCharacterSize(200);
	m_gameOverText.setOrigin(500.0f, 100.0f);
	m_gameOverText.setString("GAME OVER");
	m_gameOverText.setPosition(m_window->getSize().x / 2.0f, m_window->getSize().y / 2.0f);
}


// Handles the input from the user
void Application::handleInputs() {
	sf::Event sfmlEvent;

	// Event loop
	while (m_window->pollEvent(sfmlEvent)) {
		switch (sfmlEvent.type) {
		// If the user clicked the exit button
		case sf::Event::Closed:
			m_window->close();
			break;

		// If the user pressed a key
		case sf::Event::KeyPressed:
			// If the user pressed the W key, make the player jump
			if (sfmlEvent.key.code == sf::Keyboard::W && !m_player.getVelocity().y) {
				m_player.setVelocity(m_player.getVelocity().x, -500.0f);
			}
			break;
		}
	}
}


// Updates the entities
void Application::update() {
	// Calculates the elapsed time between current and last frame
	float deltaTime = m_clock.restart().asSeconds();
	m_timeRemaining -= deltaTime;

	// Moves the player according to player input
	if (m_player.lives > 0 && m_timeRemaining > 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			m_player.setVelocity(-150.0f, m_player.getVelocity().y);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			m_player.setVelocity(150.0f, m_player.getVelocity().y);
		}
	}

	// Checks for collisions between the player and the enemies
	for (const Enemy& enemy : m_enemies) {
		sf::FloatRect playerRect = { m_player.getPosition(), sf::Vector2f{ m_level.getTileSize() } };
		sf::FloatRect enemyRect = { enemy.getPosition(), sf::Vector2f{ m_level.getTileSize() } };

		if (playerRect.intersects(enemyRect)) {
			m_player.setPosition(0.0f, 400.0f);
			m_player.setVelocity(0.0f, 0.0f);
			m_player.lives--;
		}
	}
	if (m_player.getPosition().x > 6300) {
		m_player.lives = 0;
		m_player.setPosition(0, 400);
		m_gameOverText.setString(" YOU WON ");
	}

	// Updates the player
	m_player.update(m_level, deltaTime);

	// Updates the enemies
	for (Enemy& enemy : m_enemies) {
		enemy.update(m_level, deltaTime);
	}

	// Updates the text
	std::string text = "Lives: " + std::to_string(m_player.lives) + "\t\t\t\tScore: " + std::to_string(m_score) + "\t\t\t\tTime Remaining: " 
		+ std::to_string(static_cast<int>(m_timeRemaining)) +"\t\t\tFPS: " + std::to_string(static_cast<int>(1.0f / deltaTime));
	m_text.setString(text);
	m_text.setPosition(m_window->mapPixelToCoords({ 10, 10 }));

	// Moves the view so that the player is always in the middle
	sf::View view = m_window->getView();
	float levelPos = static_cast<float>(m_window->mapCoordsToPixel(m_level.getPosition()).x);
	float rightBoundary = -static_cast<float>(m_level.getLevelSize().x * m_level.getTileSize().x - m_window->getSize().x);
	if (levelPos <= 0.0f && levelPos >= rightBoundary) {
		float offset = m_window->mapCoordsToPixel(m_player.getPosition()).x - m_window->getSize().x / 2.0f;
		if ((levelPos == 0.0f && offset < 0.0f) || (levelPos == rightBoundary && offset > 0.0f)) {
			return;
		}
		view.move(offset, 0.0f);
	} else {
		view.move(levelPos, 0.0f);
	}
	m_window->setView(view);
}


// Renders the entities onto the window
void Application::render() {
	// Clears the window
	m_window->clear();

	// Renders the level
	if (m_player.lives > 0 && m_timeRemaining > 0) {
		m_window->draw(m_level);
		m_window->draw(m_player);
		for (const Enemy& enemy : m_enemies) {
			m_window->draw(enemy);
		}
		m_window->draw(m_text);
	} else {
		m_window->draw(m_gameOverText);
	}

	// Displays the current frame
	m_window->display();
}


// Starts the application
void Application::run() {
	while (m_window->isOpen()) {
		handleInputs();
		update();
		render();
	}
}
