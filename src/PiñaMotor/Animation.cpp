#include "Animation.h"
#include "Entity.h"
#include "Renderer.h"
#include "OgreEntity.h"



bool Animation::init(const std::map<std::string, std::string>& mapa)
{
	if (_myEntity->hasComponent<Renderer>()) {
		_ogreEnt=_myEntity->getComponent<Renderer>()->getOgreEntity();
		_myAnimation = _ogreEnt->getAnimationState("Dance");
		_myAnimation->setEnabled(true);
		_loop = true;
		_myAnimation->setLoop(_loop);
	}
	return true;
}

bool Animation::setAnimation(std::string animationName)
{
	Ogre::AnimationState* anim=_ogreEnt->getAnimationState(animationName);
	if (anim!=nullptr) {
		if (_myAnimation != anim) {
			_myAnimation->setEnabled(false);
			_myAnimation = anim;
			_myAnimation->setEnabled(_active);
			_myAnimation->setLoop(_loop);
		}
		return true;
	}
	return false;
}

void Animation::frameRendered(const Ogre::FrameEvent& evt)
{
	_myAnimation->addTime(evt.timeSinceLastFrame);
}
