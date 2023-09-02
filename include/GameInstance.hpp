//
// Created by emrey on 26.04.2022.
//

#ifndef THEBALL_GAMEINSTANCE_HPP
#define THEBALL_GAMEINSTANCE_HPP

#include <SFML/Graphics.hpp>
#include <ui/SizeBox.hpp>
#include <world/World.hpp>
#include <SFML/Audio.hpp>
#include <entity/RectEntity.hpp>
#include <ui/Button.hpp>
#include <AssetManager.hpp>
#include <ui/TextBox.hpp>
#include <animation/Animation.hpp>
#include <animation/UIFrame.hpp>

namespace ph {

class GameInstance {
public:

	explicit GameInstance(sf::RenderWindow& window);

	void loadMainMenu();

	void loadGameWorld();

	void tick(sf::RenderWindow& window);

	void render(sf::RenderWindow& window);

	void processEvents(sf::RenderWindow& window);


private:
	SizeBox m_ui;
	World m_world;
	sf::Music* m_music;
	bool m_shutdown = false;
};

} // ph

#endif //THEBALL_GAMEINSTANCE_HPP
