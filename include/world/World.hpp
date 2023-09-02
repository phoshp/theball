//
// Created by emrey on 21.04.2022.
//

#ifndef THEBALL_WORLD_HPP
#define THEBALL_WORLD_HPP

#include "Vec2.hpp"
#include "entity/Entity.hpp"
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_edge_shape.h>
#include <memory>
#include <list>

namespace ph {

class World {
public:
	std::list<std::shared_ptr<Entity>> entities;
	b2World* dynamics_world;
	b2Body* border;

	World(sf::RenderWindow& window);

	~World();

	void update(float dt) const;

	void render(sf::RenderWindow& window);

	void addEntity(const std::shared_ptr<Entity>& entity);

	void removeEntity(const std::shared_ptr<Entity>& entity);

	void removeEntities();
};

} // ph

#endif //THEBALL_WORLD_HPP