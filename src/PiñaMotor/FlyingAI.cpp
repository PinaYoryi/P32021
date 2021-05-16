#include "FlyingAI.h"
#include "SceneManager.h"
#include "BasicAI.h"

bool FlyingAI::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("strength") == mapa.end() || mapa.find("objective") == mapa.end()) return false;

	std::string s = mapa.at("strength");
	_strength = std::stof(s);
	s = mapa.at("objective");
	_objective = SceneManager::GetInstance()->getEntityByID(std::stoi(s), true);
	if (_objective == nullptr) return false;
}

void FlyingAI::update() {
	//_myEntity->getComponent<BasicAI>()->MoveTo({ 0, -60, 0 });
	//_myEntity->getComponent<BasicAI>()->setStep(_strength);
	//_myEntity->getComponent<BasicAI>()->RotateTo(_objective->getComponent<Transform>()->rotation().toEuler());
	//_myEntity->getComponent<BasicAI>()->setStepRot()
}

void FlyingAI::onCollisionStart(Entity* other)
{ 
	/*if (other->hasComponent<Bullet>()) {
		std::cout << "Destruirme, me ha dado una bala\n";
		SceneManager::GetInstance()->addEntityToRemove(_myEntity);
	}*/
}
