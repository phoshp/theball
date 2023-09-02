//
// Created by emrey on 27.04.2022.
//

#ifndef THEBALL_ASSETMANAGER_HPP
#define THEBALL_ASSETMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <filesystem>

namespace ph {

class AssetManager {
public:

	static void initialize() {
		std::filesystem::path folder("../resources/");
		if (!std::filesystem::is_directory(folder)) {
			throw std::runtime_error(folder.string() + " is not a folder");
		}

		for (const auto& entry: std::filesystem::recursive_directory_iterator(folder)) {
			if (entry.is_regular_file()) {
				const auto path = entry.path().string();
				const auto base_name = entry.path().filename().string();
				const auto ext = entry.path().extension();
				const auto stem = entry.path().stem().string();

				if (entry.path().parent_path().filename().string() == "music") {
					auto* music = new sf::Music();
					music->openFromFile(path);
					m_musics[stem] = music;
				} else if (ext == ".wav" || ext == ".ogg") {
					auto* buf = new sf::SoundBuffer();
					buf->loadFromFile(path);
					m_soundBuffers[stem] = buf;
				} else if (ext == ".png") {
					auto* tex = new sf::Texture();
					tex->loadFromFile(path);
					m_textures[stem] = tex;
				} else if (ext == ".ttf") {
					auto* font = new sf::Font();
					font->loadFromFile(path);
					m_fonts[stem] = font;
				}
			}
		}

		for (auto& pair: m_soundBuffers) {
			m_sounds[pair.first] = new sf::Sound(*pair.second);
		}
	}

	static void clear();

	static sf::Texture* getTexture(const std::string& id);

	static sf::Sound* getSound(const std::string& id);

	static sf::Music* getMusic(const std::string& id);

	static sf::Font* getFont(const std::string& id);

private:

	AssetManager() = default;

	inline static std::map<std::string, sf::Texture*> m_textures = {};
	inline static std::map<std::string, sf::Sound*> m_sounds = {};
	inline static std::map<std::string, sf::SoundBuffer*> m_soundBuffers = {};
	inline static std::map<std::string, sf::Music*> m_musics = {};
	inline static std::map<std::string, sf::Font*> m_fonts = {};
};

} // ph

#endif //THEBALL_ASSETMANAGER_HPP
