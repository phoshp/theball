//
// Created by emrey on 26.04.2022.
//

#ifndef THEBALL_SIZEBOX_HPP
#define THEBALL_SIZEBOX_HPP

#include <ui/UIElement.hpp>

namespace ph {

class SizeBox : public UIElement {
public:

	explicit SizeBox(UIPosition pos, UISize size, const std::string& base_tex = "");

	explicit SizeBox(UIPosition pos, UISize size, std::initializer_list<UIElement*> children, const std::string& base_tex = "");

	~SizeBox();

	void listenEvent(sf::RenderWindow& window, sf::Event& event) override;

	void render(sf::RenderWindow& window) override;

	void addChild(UIElement* child);

	void addChild(std::initializer_list<UIElement*> children);

	void updateAnimations(float dt);

	void reset();

private:
	std::list<UIElement*> m_children;
};

} // ph

#endif //THEBALL_SIZEBOX_HPP
