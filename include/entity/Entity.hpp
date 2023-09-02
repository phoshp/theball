//
// Created by emrey on 21.04.2022.
//

#ifndef THEBALL_ENTITY_HPP
#define THEBALL_ENTITY_HPP

#include <box2d/b2_math.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_world.h>
#include "world/Vec2.hpp"
#include <AssetManager.hpp>
#include <memory>
#include <functional>

namespace ph {

class Entity {
public:

	explicit Entity(b2World* world, b2Vec2 pos, bool constraint = false);

	~Entity();

	virtual void initBody() = 0;

	void update(float dt);

	void syncPolygon();

	bool isMouseIntersects(sf::RenderWindow& window) const;

	void render(sf::RenderWindow& window);

	void applyForce(float fx, float fy) const;

	void stopMovement();

	void close();

	b2Body* m_body;
	bool m_closed = false;
	sf::Vector2f* m_mouseInteraction = nullptr;
	sf::Shape* m_shape = nullptr;
	sf::Text m_nametag;

protected:

	void createFixtures(std::vector<b2Vec2> vertices, std::function<void(b2FixtureDef& def)>&& callback) const;
};

} // ph

#endif //THEBALL_ENTITY_HPP