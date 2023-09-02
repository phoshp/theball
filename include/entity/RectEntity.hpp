//
// Created by emrey on 23.04.2022.
//

#ifndef THEBALL_RECTENTITY_HPP
#define THEBALL_RECTENTITY_HPP

#include "Entity.hpp"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>

namespace ph {

class RectEntity : public Entity {
	float m_height;
	float m_width;
public:
	RectEntity(b2World* world, b2Vec2 pos, float height, float width, bool constraint = false);

	void initBody() override;
};

} // ph

#endif //THEBALL_RECTENTITY_HPP