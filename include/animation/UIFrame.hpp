//
// Created by Fatih on 28.04.2022.
//

#ifndef THEBALL_UIFRAME_HPP
#define THEBALL_UIFRAME_HPP

#include <SFML/Graphics.hpp>
#include "ui/UIElement.hpp"
#include "Frame.hpp"

namespace ph {

class UIFrame : public Frame<UIElement> {
public:

	explicit UIFrame(float duration);

	~UIFrame();

	void start(UIElement& target) override;

	void update(UIElement& target, float mul) override;

	void finish(UIElement& target) override;

	UIFrame* move(UIPosition* velo);

	UIFrame* scale(UISize* size);

	UIFrame* rotate(float value);

	UIPosition* m_position = nullptr;
	UISize* m_size = nullptr;
	float m_rotation = 0.0;

private:

	UIPosition m_startPos;
	UISize m_startSize;
	float m_startRotation = 0.0;
};

} // ph

#endif //THEBALL_UIFRAME_HPP
