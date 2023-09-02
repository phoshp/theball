#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <GameInstance.hpp>
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "TheBall");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	window.setSize({800, 600});

	sf::Font font;
	std::cout << "AA : " + std::to_string(sqrt(0)) << std::endl;
	if (!font.loadFromFile("../resources/mcfont.ttf")) {
		exit(1);
	}

	sf::Text text("FPS: 0", font);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(18);
	text.setPosition(10, 10);

	int fps = 0;
	auto lastTime = std::chrono::steady_clock::now();
	ph::AssetManager::initialize();
	ph::GameInstance game(window);
	game.loadMainMenu();

	int lastFPS = 0;
	while (window.isOpen()) {
		fps++;
		if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - lastTime) >=
			std::chrono::seconds{1}) {
			lastTime = std::chrono::steady_clock::now();
			lastFPS = fps;
			fps = 0;
		}
		text.setString("FPS: " + std::to_string(lastFPS) + "\nSize: " + std::to_string(window.getSize().x) + "x" +
							   std::to_string(window.getSize().y));

		game.tick(window);

		window.clear(sf::Color::Black);
		game.render(window);
		window.draw(text);

		window.display();
	}

	ph::AssetManager::clear();
	return 0;
}