#include "Animation.h"
#include "Entity.h"
#include "Renderer.h"
#include "OgreEntity.h"

bool Animation::init(const std::map<std::string, std::string>& mapa)
{
	/*if (_myEntity->hasComponent<Renderer>()) {
		_ogreEnt=_myEntity->getComponent<Renderer>()->getOgreEntity();
		//animations.push_back()
	}*/
	return true;
}

bool Animation::setAnimation(std::string animationName)
{
	for (int i = 0; i < animations.size(); ++i) {
		if (animations[i]->getAnimationName() == animationName) {
			if (_myAnimation != animations[i]) {
				_animationName = animationName;
				_myAnimation->setEnabled(false);
				_myAnimation = animations[i];
				_myAnimation->setEnabled(_active);
				_myAnimation->setLoop(_loop);
			}
			return true;
		}

	}
	return false;
}
