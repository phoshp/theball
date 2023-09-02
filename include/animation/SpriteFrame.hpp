//
// Created by Fatih on 28.04.2022.
//

#ifndef THEBALL_SPRITEFRAME_HPP
#define THEBALL_SPRITEFRAME_HPP

#include <SFML/Graphics.hpp>
#include <animation/Frame.hpp>

namespace ph {

class SpriteFrame : public Frame<sf::Sprite> {
public:

	~SpriteFrame();

	void start(sf::Sprite& target) override;

	void update(sf::Sprite& target, float mul) override;

	void finish(sf::Sprite& target) override;

	sf::Vector2f* m_position = nullptr;
	sf::Vector2f* m_scale = nullptr;
	sf::IntRect* m_textureRect = nullptr;
	float m_rotation = 0.0;

private:

	sf::Vector2f m_startPos;
	sf::Vector2f m_startScale;
	sf::IntRect m_startTextureRect;
	float m_startRotation = 0.0;
};

} // ph

#endif //THEBALL_SPRITEFRAME_HPP
