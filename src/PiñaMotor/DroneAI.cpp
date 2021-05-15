#include "DroneAI.h"
#include "SceneManager.h"
#include "BasicAI.h"

bool DroneAI::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("strength") == mapa.end() || mapa.find("objective") == mapa.end()) return false;

	std::string s = mapa.at("strength");
	_strength = std::stof(s);

	s = mapa.at("objective");
	_objective = SceneManager::GetInstance()->getEntityByID(std::stoi(s), true);
	if (_objective == nullptr) return false;
}

void DroneAI::update() {
	_myEntity->getComponent<BasicAI>()->MoveTo({ 0, -60, 0 });
	_myEntity->getComponent<BasicAI>()->RotateTo(_objective->getComponent<Transform>()->rotation().toEuler());
}    