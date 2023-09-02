//
// Created by Fatih on 28.04.2022.
//

#include "animation/SpriteFrame.hpp"

namespace ph {

void SpriteFrame::start(sf::Sprite& target) {
	m_startPos = target.getPosition();
	m_startScale = target.getScale();
	m_startTextureRect = target.getTextureRect();
	m_startRotation = target.getRotation();
}

void SpriteFrame::update(sf::Sprite& target, float mul) {
	if (m_position != nullptr) {
		target.setPosition(m_startPos + (*m_position * mul));
	}

	if (m_scale != nullptr) {
		target.setScale(m_startScale + (*m_scale * mul));
	}

	if (m_textureRect != nullptr) {
		sf::IntRect next;
		next.left = m_startTextureRect.left + (int)((float)m_textureRect->left * mul);
		next.top = m_startTextureRect.top + (int)((float)m_textureRect->top * mul);
		next.height = m_startTextureRect.height + (int)((float)m_textureRect->height * mul);
		next.width = m_startTextureRect.width + (int)((float)m_textureRect->width * mul);
		target.setTextureRect(next);
	}

	target.setRotation(m_startRotation + m_rotation * mul);
}

void SpriteFrame::finish(sf::Sprite& target) {
	if (m_position != nullptr) {
		target.setPosition(m_startPos + *m_position);
	}

	if (m_scale != nullptr) {
		target.setScale(m_startScale + *m_scale);
	}

	if (m_textureRect != nullptr) {
		sf::IntRect next;
		next.left = m_startTextureRect.left + m_textureRect->left;
		next.top = m_startTextureRect.top + m_textureRect->top;
		next.height = m_startTextureRect.height + m_textureRect->height;
		next.width = m_startTextureRect.width + m_textureRect->width;
		target.setTextureRect(next);
	}

	target.setRotation(m_startRotation + m_rotation);
}

SpriteFrame::~SpriteFrame() {
	delete m_position;
	delete m_scale;
	delete m_textureRect;
}

} // ph