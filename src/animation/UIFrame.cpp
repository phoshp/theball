//
// Created by Fatih on 28.04.2022.
//

#include "animation/UIFrame.hpp"

namespace ph {

void UIFrame::start(UIElement& target) {
	m_startPos = target.m_position;
	m_startSize = target.m_size;
	m_startRotation = target.m_rotation;
}

void UIFrame::update(UIElement& target, float mul) {
	if (m_position != nullptr) {
		target.m_position.left = m_startPos.left + (int)((float)m_position->left * mul);
		target.m_position.top = m_startPos.top + (int)((float)m_position->top * mul);
	}

	if (m_size != nullptr) {
		target.m_size.width = m_startSize.width + (int)((float)m_size->width * mul);
		target.m_size.height = m_startSize.height + (int)((float)m_size->height * mul);
	}

	target.m_rotation = m_startRotation + m_rotation * mul;
}

void UIFrame::finish(UIElement& target) {
	if (m_position != nullptr) {
		target.m_position.left = m_startPos.left + m_position->left;
		target.m_position.top = m_startPos.top + m_position->top;
	}
	if (m_size != nullptr) {
		target.m_size.width = m_startSize.width + m_size->width;
		target.m_size.height = m_startSize.height + m_size->height;
	}
	target.m_rotation = m_startRotation + m_rotation;
}

UIFrame::~UIFrame() {
	delete m_position;
	delete m_size;
}

UIFrame* UIFrame::move(UIPosition* velo) {
	m_position = velo;
	return this;
}

UIFrame* UIFrame::scale(UISize* size) {
	m_size = size;
	return this;
}

UIFrame* UIFrame::rotate(float value) {
	m_rotation = value;
	return this;
}

UIFrame::UIFrame(float duration) {
	m_duration = duration;
}

} // ph