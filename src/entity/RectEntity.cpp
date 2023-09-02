//
// Created by emrey on 23.04.2022.
//

#include "entity/RectEntity.hpp"

namespace ph {

bool is_con = false;

RectEntity::RectEntity(b2World* world, b2Vec2 pos, float height, float width, bool constraint) : m_height(height),
																								 m_width(width),
																								 Entity(world, pos,
																										constraint) {
	is_con = constraint;
}

void RectEntity::initBody() {
	if (!is_con) {
		b2CircleShape shape;
		shape.m_radius = ((m_width + m_height) / 2) / 100;

		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;
		fixture.friction = 0.05f;

		m_body->CreateFixture(&fixture);
	} else {
		b2PolygonShape shape;
		shape.SetAsBox(m_width / 100, m_height / 100);

		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0f;
		fixture.friction = 0.05f;

		m_body->CreateFixture(&fixture);
		/*int points = 20;
		float rad = 2 * 3.14f / points;
		float w = m_width / 192;
		float h = m_height / 108;
		std::vector<b2Vec2> vertices;
		vertices.reserve(points);
		for (int i = 0; i < points; ++i) {
			vertices.emplace_back(cos((float) i * rad) * w, sin((float) i * rad) * h);
		}
		createFixtures(vertices, [&](b2FixtureDef& def) {
			def.density = 1.0f;
			def.friction = 0.05f;
			def.restitution = 0.25f;
		});*/
	}
}

} // ph