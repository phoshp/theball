//
// Created by emrey on 21.04.2022.
//

#include "entity/Entity.hpp"
#include <iostream>

#define PIXELS_RATIO_W 192.f
#define PIXELS_RATIO 100.f

namespace ph {

Entity::Entity(b2World* world, b2Vec2 pos, bool constraint) {
	b2BodyDef def;
	def.position = {pos.x / PIXELS_RATIO, pos.y / PIXELS_RATIO};
	def.type = constraint ? b2BodyType::b2_staticBody : b2BodyType::b2_dynamicBody;
	m_body = world->CreateBody(&def);

	m_nametag.setFont(*AssetManager::getFont("oswald"));
	m_nametag.setFillColor(sf::Color::Black);
	m_nametag.setCharacterSize(12);
}

Entity::~Entity() {
	m_body = nullptr;
}

void Entity::createFixtures(std::vector<b2Vec2> vertices, std::function<void(b2FixtureDef&)>&& callback) const {
	for (int i = 0; i < vertices.size(); i++) {
		b2EdgeShape shape;
		shape.SetTwoSided(vertices[i], vertices[(i + 1) % vertices.size()]);

		b2FixtureDef fixture;
		fixture.shape = &shape;
		callback(fixture);

		std::cout << "WOW";

		m_body->CreateFixture(&fixture);
	}
	/*for (int i = 0; i < vertices.size(); i += 5) {
		b2EdgeShape poly;

		int remain = std::min(5, (int) vertices.size() - i);
		bool merged = false;
		if (vertices.size() - i < 3) {
			remain += (int) vertices.size() - i;
			merged = true;
		}
		std::vector<b2Vec2> vex;
		std::cout << "i: " << i << ", remain: " << remain << std::endl;
		for (int j = 0; j < remain; ++j) {
			vex.push_back(vertices[i + j]);
		}
		poly.Set(vex.data(), remain);

		b2FixtureDef fixture;
		fixture.shape = &poly;
		callback(fixture);

		m_body->CreateFixture(&fixture);

		if (merged) break;
	}*/
}

void Entity::update(float dt) {
	// todo
}

void Entity::syncPolygon() {
	std::vector<sf::Vector2f> vertices;
	int count = 0;
	for (auto* f = m_body->GetFixtureList(); f != nullptr; f = f->GetNext()) {
		switch (f->GetType()) {
			case b2Shape::Type::e_edge: {
				auto* s2 = (b2EdgeShape*) f->GetShape();
				count++;
				vertices.emplace_back(s2->m_vertex1.x, s2->m_vertex1.y);
				break;
			}
			case b2Shape::Type::e_polygon: {
				auto* s = (b2PolygonShape*) f->GetShape();
				auto convex = new sf::ConvexShape(s->m_count);
				//count += s->m_count;
				for (int i = 0; i < s->m_count; ++i) {
					auto& v = s->m_vertices[i];
					//auto v2 = b2Mul(body->GetTransform(), v);
					convex->setPoint(i, {v.x * PIXELS_RATIO, v.y * PIXELS_RATIO});
				}
				m_shape = convex;
				break;
			}
			case b2Shape::Type::e_circle: {
				auto* s3 = (b2CircleShape*) f->GetShape();
				m_shape = new sf::CircleShape(s3->m_radius * PIXELS_RATIO);
				m_shape->setFillColor(sf::Color::White);
				break;
			}
		}
	}

	/*m_shape.setPointCount(count);
	for (int i = 0; i < count; ++i) {
		m_shape.setPoint(i, vertices[i]);
	}*/
}

void Entity::render(sf::RenderWindow& window) {
	//auto& size = window.getView().getSize();
	//const float middleX = size.x / 2;
	/*const auto& local = shape.getLocalBounds();
	float spriteY = (local.height - local.top) / 2;
	float spriteX = (local.width - local.left) / 2;*/

	m_shape->setOrigin(m_body->GetLocalCenter().x * PIXELS_RATIO, m_body->GetLocalCenter().y * PIXELS_RATIO);
	//m_shape.setRotation(m_body->GetAngle());
	m_shape->setPosition(m_body->GetPosition().x * PIXELS_RATIO, -m_body->GetPosition().y * PIXELS_RATIO);

	m_nametag.setString("x:" + std::to_string(m_shape->getPosition().x) + " | y:" + std::to_string(m_shape->getPosition().y));
	m_nametag.setOrigin(m_nametag.getLocalBounds().width / 2, m_nametag.getLocalBounds().height / 2);
	m_nametag.setPosition(m_shape->getPosition().x, m_shape->getPosition().y - 100);

	window.draw(*m_shape);
	window.draw(m_nametag);
}

void Entity::stopMovement() {
	// todo
}

void Entity::close() {
	m_closed = true;
}

void Entity::applyForce(float fx, float fy) const {
	b2Vec2 vec{fx, fy};
	m_body->ApplyForceToCenter(vec, true);
}

bool Entity::isMouseIntersects(sf::RenderWindow& window) const {
	auto mp = sf::Vector2f(sf::Mouse::getPosition(window));
	return m_shape->getGlobalBounds().contains(mp);
}

} // ph