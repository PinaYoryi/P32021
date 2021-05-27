#include "ResourceManager.h"

ResourceManager* ResourceManager::_singleton = nullptr;

ResourceManager* ResourceManager::GetInstance() {
	return _singleton;
}

ResourceManager* ResourceManager::Init() {
	if (_singleton == nullptr) _singleton = new ResourceManager();
	if (std::filesystem::exists(RESOURCES_PATH)) _singleton->searchDir(RESOURCES_PATH);
	return _singleton;
}

std::string ResourceManager::texture(std::string name) {
	auto it = _textures.find(name);
	if (it != _textures.end()) return it->second;
	it = _textures.find("Default.png");
	if (it != _textures.end()) return it->second;
	throw std::exception("Could not find texture requested or the default one");
}

std::string ResourceManager::audio(std::string name) {
	auto it = _audio.find(name);
	if (it != _audio.end()) return it->second;
	it = _audio.find("Default.ogg");
	if (it != _audio.end()) return it->second;
	throw std::exception("Could not find audio requested or the default one");
}

std::string ResourceManager::scene(std::string name) {
	auto it = _scenes.find(name);
	if (it == _scenes.end()) throw std::exception("Non-existant scene has been called");
	return it->second;
}

std::string ResourceManager::prefab(std::string name)
{
	auto it = _prefabs.find(name);
	if (it == _prefabs.end()) throw std::exception("Non-existant prefab has been called");
	return it->second;
}

void ResourceManager::searchDir(std::filesystem::path path) {
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		size_t lastindex = entry.path().string().find_last_of(".");
		if (lastindex == 0)
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
	else if (extension == ".lua")
		_scenes.insert(std::pair<std::string, std::string>(name, path.string()));
	else if (extension == ".prefab")
		_prefabs.insert(std::pair<std::string, std::string>(name, path.string()));
}
