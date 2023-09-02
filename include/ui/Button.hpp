//
// Created by emrey on 26.04.2022.
//

#ifndef THEBALL_BUTTON_HPP
#define THEBALL_BUTTON_HPP

#include <ui/UIElement.hpp>
#include <functional>
#include <SFML/Audio.hpp>

namespace ph {

class Button : public UIElement {
public:

	Button(UIPosition pos, UISize size, std::function<void(Button& btn)> on_click, const std::string& base_tex,
		   std::string text = "", const std::string& pressed_tex = "", const std::string& hover_tex = "");

	void listenEvent(sf::RenderWindow& window, sf::Event& event) override;

	void render(sf::RenderWindow& window) override;

private:
	std::string m_text;
	std::function<void(Button& btn)> m_onClick;
	sf::Texture* m_pressed;
	sf::Texture* m_hover;

	bool m_isPressed = false;
};

} // ph

#endif //THEBALL_BUTTON_HPP
