//
// Created by emrey on 21.04.2022.
//

#include "world/World.hpp"

namespace ph {

World::World(sf::RenderWindow& window) {
	auto gravity = b2Vec2(0, -10);
	dynamics_world = new b2World(gravity);

	//init borders
	/*auto size = window.getSize();
	auto pos1 = b2Vec2(0, 0);
	auto pos2 = b2Vec2(size.x / 192, 0);
	auto pos3 = b2Vec2(size.x / 192, -size.y / 108);
	auto pos4 = b2Vec2(0, -size.y / 108);

	b2BodyDef def;
	b2EdgeShape shape;
	border = dynamics_world->CreateBody(&def);

	shape.SetTwoSided(pos1, pos2);
	border->CreateFixture(&shape, 0);
	shape.SetTwoSided(pos2, pos3);
	border->CreateFixture(&shape, 0);
	shape.SetTwoSided(pos3, pos4);
	border->CreateFixture(&shape, 0);
	shape.SetTwoSided(pos4, pos1);
	border->CreateFixture(&shape, 0);*/
}

World::~World() {
	delete dynamics_world;
}

void World::update(float dt) const {
	dynamics_world->Step(dt, 8, 3);
}

void World::render(sf::RenderWindow& window) {
	std::for_each(entities.begin(), entities.end(), [&window](std::shared_ptr<Entity>& entity) {
		entity->render(window);
	});
}

void World::addEntity(const std::shared_ptr<Entity>& entity) {
	entities.push_back(entity);
	entity->initBody();
	entity->syncPolygon();
}

void World::removeEntity(const std::shared_ptr<Entity>& entity) {
	entities.remove(entity);
}

void World::removeEntities() {
	entities.clear();
}

}
// ph