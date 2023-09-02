//
// Created by emrey on 26.04.2022.
//

#include "ui/SizeBox.hpp"

#include <iostream>

namespace ph {

SizeBox::SizeBox(UIPosition pos, UISize size, const std::string& base_tex)
		: UIElement(pos, size, base_tex) {}

SizeBox::SizeBox(UIPosition pos, UISize size, std::initializer_list<UIElement*> children,
				 const std::string& base_tex) : UIElement(pos, size, base_tex) {
	addChild(children);
}

void SizeBox::listenEvent(sf::RenderWindow& window, sf::Event& event) {
	for (auto& child: m_children) {
		child->listenEvent(window, event);
	}
}

void SizeBox::render(sf::RenderWindow& window) {
	UIElement::render(window);
	for (auto& child: m_children) {
		child->render(window);
	}
}

void SizeBox::addChild(UIElement* child) {
	child->m_parent = this;
	m_children.push_back(child);
}

void SizeBox::addChild(std::initializer_list<UIElement*> children) {
	for (auto& child: children) {
		addChild(child);
	}
}

void SizeBox::reset() {
	for (auto i: m_children) {
		delete i;
	}
	m_children.clear();
}

SizeBox::~SizeBox() {
	reset();
	delete m_child;
}

void SizeBox::updateAnimations(float dt) {
	UIElement::updateAnimations(dt);

	if (m_children.empty()) return;
	for (auto& child : m_children) {
		child->updateAnimations(dt);

		if (child->m_closed) {
			child->m_parent = nullptr;
			m_children.remove(child);
		}
	}
}

} // ph