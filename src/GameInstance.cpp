//
// Created by emrey on 26.04.2022.
//

#include "GameInstance.hpp"
#include <iostream>

namespace ph {

GameInstance::GameInstance(sf::RenderWindow& window) : m_world(World(window)), m_ui(SizeBox({0, 0, false}, {100, 100}, "bg")) {
	m_music = AssetManager::getMusic("dungeon");
}

void GameInstance::loadMainMenu() {
	m_music->play();
	m_music->setLoop(true);

	auto* buttons = new SizeBox({50, 40}, {50, 50}, "black_panel");

	auto* btn = new Button({0, -10}, {20, 30}, [&](Button& btn) {
		btn.m_closed = true;
		//btn.animate(new Animation<UIElement>({(new UIFrame(1))->move(new UIPosition{0, -50})}));
		}, "button_base", "", "button_pressed", "button_hover");
	//uto* title = new TextBox({0, 0}, {50, 50}, sf::Text("Merhaba", *AssetManager::getFont("roboto_mono")), sf::Color::White);
	/*auto* anim = new Animation<UIElement>({
		(new UIFrame(0.5))->rotate(15),
		(new UIFrame(0.5))->rotate(-15),
		(new UIFrame(0.5))->rotate(-15),
		(new UIFrame(0.5))->rotate(15),
	}, true);
	//anim.addFrame((new UIFrame())->scale(new UISize{10, 10}));
	//anim->addFrame((new UIFrame(0.5))->scale(new UISize{-15, -15})->rotate(60));
	//anim->addFrame((new UIFrame(0.5))->scale(new UISize{15, 15})->rotate(60));
	btn->animate(anim);*/

	buttons->addChild(btn);
	m_ui.addChild(buttons);

	loadGameWorld();
}

void GameInstance::loadGameWorld() {
	b2Vec2 pos = {400, -100};
	//b2Vec2 pos2 = {0, -10};
	b2Vec2 pos3 = {300, -800};

	/*auto entity = std::make_shared<RectEntity>(m_world.dynamics_world, pos, 50.f, 50.f);
	m_world.addEntity(entity);
	auto entity2 = std::make_shared<RectEntity>(m_world.dynamics_world, pos, 50.f, 50.f);
	m_world.addEntity(entity2);
	auto entity3 = std::make_shared<RectEntity>(m_world.dynamics_world, pos, 50.f, 50.f);
	m_world.addEntity(entity3);*/
	auto entity4 = std::make_shared<RectEntity>(m_world.dynamics_world, pos, 50.f, 50.f);
	m_world.addEntity(entity4);
	//entity->applyForce(60, 0);

	auto entity5 = std::make_shared<ph::RectEntity>(m_world.dynamics_world, pos3, 20.f, 1000.f, true);
	entity5->m_body->SetGravityScale(0.001);
	m_world.addEntity(entity5);
}

void GameInstance::tick(sf::RenderWindow& window) {
	processEvents(window);
	if (m_shutdown) {
		window.close();
		return;
	}
	m_world.update(1.f / 60);
}

void GameInstance::render(sf::RenderWindow& window) {
	m_ui.render(window);
	m_ui.updateAnimations(1.f / 60);
	m_world.render(window);
	// todo
}

void GameInstance::processEvents(sf::RenderWindow& window) {
	sf::Event event{};
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_shutdown = true;
		} else if (event.type == sf::Event::Resized) {
			sf::Vector2f size{(float) event.size.width, (float) event.size.height};
			sf::View view(size * 0.5f, size);
			window.setView(view);
		} else if (event.type == sf::Event::MouseWheelScrolled) {
			sf::View view = window.getView();
			view.zoom(1.f + event.mouseWheelScroll.delta * -0.2);
			window.setView(view);
		} else if (event.type == sf::Event::MouseButtonPressed) {
			auto& entities = m_world.entities;
			std::for_each(entities.begin(), entities.end(), [&](std::shared_ptr<Entity>& entity) {
				if (entity->m_mouseInteraction == nullptr && entity->isMouseIntersects(window)) {
					entity->m_mouseInteraction = new sf::Vector2f{float(event.mouseButton.x), float(event.mouseButton.y)};
				}
			});
		} else if (event.type == sf::Event::MouseButtonReleased) {
			auto& entities = m_world.entities;
			std::for_each(entities.begin(), entities.end(), [&](std::shared_ptr<Entity>& entity) {
				if (entity->m_mouseInteraction != nullptr) {
					auto* pos = entity->m_mouseInteraction;
					float fx = float(event.mouseButton.x) - entity->m_shape->getPosition().x;
					float fy = float(event.mouseButton.y) - entity->m_shape->getPosition().y;
					std::cout << "FORCE: " << fx << ":" << fy << std::endl;
					entity->m_body->ApplyForceToCenter({fx / 2, -fy / 2}, true);
					entity->m_mouseInteraction = nullptr;
					delete pos;
				}
			});
		}

		m_ui.listenEvent(window, event);
	}
}

} // ph