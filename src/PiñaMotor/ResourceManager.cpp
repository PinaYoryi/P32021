#include "ResourceManager.h"
#include <iostream>


ResourceManager* ResourceManager::_singleton = nullptr;

ResourceManager* ResourceManager::GetInstance() {
	return _singleton;
}

ResourceManager* ResourceManager::Init() {
	if (_singleton == nullptr) _singleton = new ResourceManager();
	_singleton->searchDir(RESOURCES_PATH);
	std::cout << "Audio\n";
	for (auto i : _singleton->_audio)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
	std::cout << "Textures\n";
	for (auto i : _singleton->_textures)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
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
	std::cout << "Init Search in: " << path << "\n";
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		std::cout << entry.path() << "\n";
		size_t lastindex = entry.path().string().find_last_of(".");
		if (lastindex == 1)
			searchDir(entry.path());
		else
			loadAsset(entry.path(), lastindex, path.string().length());
	}
	std::cout << "End Search in: " << path << "\n";
}

void ResourceManager::loadAsset(std::filesystem::path path, size_t end, size_t pathLenght) {
	std::string extension = path.string().substr(end);
	std::cout << extension << "\n";
	std::string name = path.string().substr(pathLenght + 1);
	if (extension == ".wav" || extension == ".ogg" || extension == ".mp3")
		_audio.insert(std::pair<std::string, std::string>(name, path.string()));
	else if (extension == ".png" || extension == ".jpg" || extension == ".bmp")
		_textures.insert(std::pair<std::string, std::string>(name, path.string()));

	std::cout << name << "\n";
}
