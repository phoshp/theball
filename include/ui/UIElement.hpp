//
// Created by emrey on 26.04.2022.
//

#ifndef THEBALL_UIELEMENT_HPP
#define THEBALL_UIELEMENT_HPP

class Animation;

#include <SFML/Graphics.hpp>
#include <AssetManager.hpp>
#include "animation/Animation.hpp"

namespace ph {

struct UIPosition {
	int left = 0;
	int top = 0;
	bool centered = true;
};

struct UISize {
	int height = 0;
	int width = 0;
};

class UIElement {
public:

	UIElement(UIPosition position, UISize size, const std::string& base_tex = "");

	~UIElement();

	virtual void listenEvent(sf::RenderWindow& window, sf::Event& event) {}

	virtual void render(sf::RenderWindow& window);

	void move(int x, int y);

	void scale(int x, int y);

	void rotate(float value);

	void animate(Animation<UIElement>* animation);

	virtual void updateAnimations(float dt);

	float getRealX(sf::RenderWindow& window) const;

	float getRealY(sf::RenderWindow& window) const;

	float getRealSizeX(sf::RenderWindow& window) const;

	float getRealSizeY(sf::RenderWindow& window) const;

	bool isMouseIntersects(sf::RenderWindow& window) const;

	sf::FloatRect getBoundingBox(sf::RenderWindow& window) const;

	UIPosition m_position;
	UISize m_size;
	float m_rotation = 0;
	UIElement* m_parent = nullptr;
	UIElement* m_child = nullptr;
	sf::Texture* m_base;
	bool m_closed = false;

protected:
	sf::Sprite m_sprite;
	std::vector<Animation<UIElement>*> animations;
};

}

#endif //THEBALL_UIELEMENT_HPP
