//
// Created by Fatih on 28.04.2022.
//

#ifndef THEBALL_TEXTBOX_HPP
#define THEBALL_TEXTBOX_HPP

#include <ui/UIElement.hpp>

namespace ph {

class TextBox : public UIElement {
public:

	explicit TextBox(UIPosition pos, UISize size, sf::Text&& text, sf::Color color = sf::Color::White, const std::string& base_tex = "");

	void render(sf::RenderWindow &window) override;

private:

	std::string m_textStr;
	sf::Text m_text;
};

} // ph

#endif //THEBALL_TEXTBOX_HPP
