//
// Created by emrey on 26.04.2022.
//

#include "ui/UIElement.hpp"

#include <iostream>

namespace ph {

UIElement::UIElement(UIPosition position, UISize size, const std::string& base_tex)
		: m_position(position), m_size(size) {
	if (base_tex.length() > 0) {
		m_base = AssetManager::getTexture(base_tex);
		m_sprite.setTexture(*m_base);
	}
}

UIElement::~UIElement() {
	animations.clear();
	m_child = nullptr;
	m_parent = nullptr;
}

void UIElement::render(sf::RenderWindow& window) {
	float rsx = getRealSizeX(window);
	float rsy = getRealSizeY(window);

	if (m_sprite.getTexture() != nullptr) {
		const auto& rect = m_sprite.getTextureRect();
        if (m_position.centered) {
			m_sprite.setOrigin(float(rect.width) / 2, float(rect.height) / 2);
		}
		m_sprite.setScale(rsx / (float) (rect.width - rect.left),
						  rsy / (float) (rect.height - rect.top));
		m_sprite.setPosition(getRealX(window), getRealY(window));
	}
	m_sprite.setRotation((m_parent != nullptr ? m_parent->m_rotation : 0) + m_rotation);
	window.draw(m_sprite);

	if (m_child != nullptr) {
		m_child->render(window);
	}
}

void UIElement::move(int x, int y) {
	m_position.left += x;
	m_position.top += y;
}

void UIElement::scale(int x, int y) {
	m_size.width += x;
	m_size.height += y;
}

void UIElement::rotate(float value) {
	m_rotation += value;
}

void UIElement::animate(Animation<UIElement>* animation) {
	animations.push_back(animation);
}

void UIElement::updateAnimations(float dt) {
	for (auto& anim: animations) {
		anim->update(*this, dt);
	}

	if (m_child != nullptr) m_child->updateAnimations(dt);
}

float UIElement::getRealX(sf::RenderWindow& window) const {
	return (m_parent != nullptr ? m_parent->getRealX(window) : 0) +
		   (float) ((m_parent != nullptr ? m_parent->getRealSizeX(window) : (float) window.getSize().x) *
					(float) m_position.left) /
		   100;
}

float UIElement::getRealY(sf::RenderWindow& window) const {
	return (m_parent != nullptr ? m_parent->getRealY(window) : 0) +
		   (float) ((m_parent != nullptr ? m_parent->getRealSizeY(window) : (float) window.getSize().y) *
					(float) m_position.top) /
		   100;
}

float UIElement::getRealSizeX(sf::RenderWindow& window) const {
	return (float) ((m_parent != nullptr ? m_parent->getRealSizeX(window) : (float) window.getSize().x) *
					(float) m_size.width) / 100;
}

float UIElement::getRealSizeY(sf::RenderWindow& window) const {
	return (float) ((m_parent != nullptr ? m_parent->getRealSizeY(window) : (float) window.getSize().y) *
					(float) m_size.height) / 100;
}

bool UIElement::isMouseIntersects(sf::RenderWindow& window) const {
	float sx = getRealSizeX(window);
	float sy = getRealSizeY(window);
	float minX = getRealX(window) - (m_position.centered ? sx / 2 : 0);
	float minY = getRealY(window) - (m_position.centered ? sy / 2 : 0);
	auto mp = sf::Mouse::getPosition(window);
	return (float) mp.x > (float) minX && (float) mp.y > minY && (float) mp.x < minX + sx && (float) mp.y < minY + sy;
}

sf::FloatRect UIElement::getBoundingBox(sf::RenderWindow& window) const {
	float sx = getRealSizeX(window);
	float sy = getRealSizeY(window);
	float minX = getRealX(window) - (m_position.centered ? sx / 2 : 0);
	float minY = getRealY(window) - (m_position.centered ? sy / 2 : 0);

	return {minX, minY, sx, sy};
}

}
