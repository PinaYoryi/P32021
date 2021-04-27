#include "ResourceManager.h"
#include <iostream>
#include <filesystem>

ResourceManager* ResourceManager::_singleton = nullptr;

ResourceManager* ResourceManager::GetInstance() {
	return _singleton;
}

ResourceManager* ResourceManager::Init() {
	if (_singleton == nullptr) _singleton = new ResourceManager();
	_singleton->loadTextures();
	return _singleton;
}

std::string ResourceManager::texture(std::string name) {
	auto it = _textures.find(name);
	if (it == _textures.end()) throw "No se ha encontrado la textura" + name;
	return it->second;
}

std::string ResourceManager::audio(std::string name) {
	auto it = _audio.find(name);
	if (it == _audio.end()) throw "No se ha encontrado el audio" + name;
	return it->second;
}

void ResourceManager::loadTextures() {
	for (const auto& entry : std::filesystem::directory_iterator(texturesPath)) {
		std::string name = entry.path().string().substr(texturesPath.length());
		_textures.insert(std::pair<std::string, std::string>(name, entry.path().string()));
	}
}

void ResourceManager::loadAudio() {
	for (const auto& entry : std::filesystem::directory_iterator(audioPath)) {
		std::string name = entry.path().string().substr(audioPath.length());
		_textures.insert(std::pair<std::string, std::string>(name, entry.path().string()));
	}
}

std::string truncate(std::string str, size_t width) {
	if (str.length() > width)
		return str.substr(0, width);
	return str;
}