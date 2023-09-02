//
// Created by emrey on 27.04.2022.
//

#include "AssetManager.hpp"

namespace ph {

void AssetManager::clear() {
	for (auto& p: m_textures) {
		delete p.second;
	}

	for (auto& p: m_soundBuffers) {
		delete p.second;
	}

	for (auto& p: m_sounds) {
		delete p.second;
	}

	for (auto& p: m_musics) {
		delete p.second;
	}

	for (auto& p: m_fonts) {
		delete p.second;
	}

	m_soundBuffers.clear();
	m_sounds.clear();
	m_textures.clear();
	m_musics.clear();
	m_fonts.clear();
}

sf::Music* AssetManager::getMusic(const std::string& id) {
	return m_musics.at(id);
}

sf::Texture* AssetManager::getTexture(const std::string& id) {
	return m_textures.at(id);
}

sf::Sound* AssetManager::getSound(const std::string& id) {
	return m_sounds.at(id);
}

sf::Font* AssetManager::getFont(const std::string& id) {
	return m_fonts[id];
}

} // ph