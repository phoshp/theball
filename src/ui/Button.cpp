//
// Created by emrey on 26.04.2022.
//

#include "ui/Button.hpp"
#include <utility>

namespace ph {

Button::Button(UIPosition pos, UISize size, std::function<void(Button& btn)> on_click, const std::string& base,
			   std::string text, const std::string& pressed,
			   const std::string& hover) : m_onClick(std::move(on_click)), m_text(std::move(text)),
										   UIElement(pos, size, base) {
	m_pressed = AssetManager::getTexture(pressed);
	m_hover = AssetManager::getTexture(hover);
}

void Button::listenEvent(sf::RenderWindow& window, sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (isMouseIntersects(window)) {
			m_isPressed = true;
			m_sprite.setTexture(*m_pressed);
		}
	} else if (event.type == sf::Event::MouseButtonReleased) {
		if (m_isPressed && isMouseIntersects(window)) {
			AssetManager::getSound("button_click")->play();
			m_sprite.setTexture(*m_hover, true);
			m_onClick(*this);
		} else if (m_isPressed) {
			m_sprite.setTexture(*m_base, true);
		}
		m_isPressed = false;

	} else if (event.type == sf::Event::MouseMoved) {
		if (isMouseIntersects(window) && !m_isPressed) {
			m_sprite.setTexture(*m_hover, true);
			AssetManager::getSound("button_hover")->play();
		} else if (!m_isPressed) {
			m_sprite.setTexture(*m_base, true);
			AssetManager::getSound("button_hover")->play();
		}
	}
}

void Button::render(sf::RenderWindow& window) {
	UIElement::render(window);

	static sf::Text text;
	if (m_text.length() > 0) {
		text.setString(m_text);
		text.setFont(*AssetManager::getFont("oswald"));
		text.setScale(m_sprite.getScale());
		text.setPosition(m_sprite.getPosition());

		window.draw(text);
	}
}

} // ph