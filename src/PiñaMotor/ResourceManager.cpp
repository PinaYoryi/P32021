#include "ResourceManager.h"
#include <iostream>


ResourceManager* ResourceManager::_singleton = nullptr;

ResourceManager* ResourceManager::GetInstance() {
	return _singleton;
}

ResourceManager* ResourceManager::Init() {
	if (_singleton == nullptr) _singleton = new ResourceManager();
	_singleton->searchDir(RESOURCES_PATH);
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

void ResourceManager::searchDir(std::filesystem::path path) {
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		std::cout << entry.path() << "\n";
		size_t lastindex = entry.path().string().find_last_of(".");
		if (lastindex == 1)
			searchDir(entry.path());
		else
			loadAsset(entry.path(), lastindex, path.string().length());
	}
}

void ResourceManager::loadAsset(std::filesystem::path path, size_t end, size_t pathLength) {
	std::string extension = path.string().substr(end);
	std::string name = path.string().substr(pathLength + 1);
	if (extension == ".wav" || extension == ".ogg" || extension == ".mp3")
		_audio.insert(std::pair<std::string, std::string>(name, path.string()));
	else if (extension == ".png" || extension == ".jpg" || extension == ".bmp")
		_textures.insert(std::pair<std::string, std::string>(name, path.string()));
}
