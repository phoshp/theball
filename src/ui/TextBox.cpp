//
// Created by Fatih on 28.04.2022.
//

#include "ui/TextBox.hpp"

#include <utility>

namespace ph {

TextBox::TextBox(UIPosition pos, UISize size, sf::Text&& text, const sf::Color color,
				 const std::string& base_tex) : m_text(std::move(text)), m_textStr(text.getString()), UIElement(pos, size, base_tex) {
	m_text.setFillColor(color);
}

void TextBox::render(sf::RenderWindow& window) {
	UIElement::render(window);

	auto bb = getBoundingBox(window);
	/*for (int i = 0; i < m_text.getString().getSize(); ++i) {
		auto pos = m_text.findCharacterPos(i);
		auto charRect = sf::FloatRect(pos.x, pos.y, m_text.getFont()->getKerning(),1);
		//
	}*/
	sf::View view({0, 0, 100, 100});
	//view.setViewport({0, 0, 1, 1});
	//window.setView(view);
	window.draw(m_text);
	//window.setView(window.getDefaultView());
}

} // ph