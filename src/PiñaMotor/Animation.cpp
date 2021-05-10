#include "Animation.h"
#include "Entity.h"
#include "Renderer.h"
#include "OgreEntity.h"

bool Animation::init(const std::map<std::string, std::string>& mapa) {
	//TODO: rellenar init con los valores del mapa
	//el try es necesario para que no explote la aplicacion si da algun error ogre
	if (_myEntity->hasComponent<Renderer>()) {
		_ogreEnt=_myEntity->getComponent<Renderer>()->getOgreEntity();
		try {
			_myAnimations.push_back(_ogreEnt->getAnimationState("Dance"));
			_myAnimations[0]->setEnabled(true);
			_loop = true;
			_myAnimations[0]->setLoop(_loop);
		}
		catch (Ogre::Exception& e) {
#if (defined _DEBUG)
			std::cout << "Fallo al iniciar el componente animation" << "\n";
#endif
			return false;
		}
	}
	return true;
}

void Animation::setLoop(bool loop) {
	_loop = loop;
	for (auto an : _myAnimations)
		an->setLoop(_loop);
}

void Animation::play() {
	_active = true;
	for (auto an : _myAnimations)
		an->setEnabled(_active);
}

void Animation::stop() {
	_active = false;
	for (auto an : _myAnimations)
		an->setEnabled(_active);
}

bool Animation::changeAnimation(std::string animationName) {
	//desactivamos las animaciones y las guardamos por si hay que volver a ponerlas en caso de error
	std::vector<Ogre::AnimationState*> aux;
	for (int i = 0; i < _myAnimations.size(); ++i)
	{		

		_myAnimations[i]->setEnabled(false);
		aux.push_back(_myAnimations[i]);
	}
	_myAnimations.clear();

	//el try es necesario para que no explote la aplicacion si da algun error ogre
	//ponemos las nuevas animaciones	
	try {
		_myAnimations.push_back(_ogreEnt->getAnimationState(animationName));
		_myAnimations[0]->setTimePosition(0);//que empiece desde el principio la animacion

		_myAnimations[0]->setEnabled(_active);
		_myAnimations[0]->setLoop(_loop);
	}
	catch (Ogre::Exception& e) {
#if (defined _DEBUG)
		std::cout << "Fallo al cambiar a la animacion " << animationName << "\n";
#endif
		//si ocurre un fallo hay que volver a poner las animaciones que habia antes
		for (int i = 0; i < _myAnimations.size(); ++i)
		{
			_myAnimations[i]->setEnabled(false);
		}
		_myAnimations.clear();


		for (int i = 0; i < aux.size(); ++i)
		{
			_myAnimations.push_back(aux[i]);
			_myAnimations[i]->setEnabled(_active);
		}
		return false;
	}
	return true;
}

bool Animation::changeAnimation(std::vector<std::string> animationsNames) {
	//desactivamos las animaciones y las guardamos por si hay que volver a ponerlas en caso de error
	std::vector<Ogre::AnimationState*> aux;
	for (int i = 0; i < _myAnimations.size(); ++i)
	{
		_myAnimations[i]->setEnabled(false);
		aux.push_back(_myAnimations[i]);
	}
	_myAnimations.clear();

	int j = 0;
	//pongemos las nuevas animaciones
	for (auto name : animationsNames) {
		try {
			Ogre::AnimationState* anim = _ogreEnt->getAnimationState(name);
			_myAnimations.push_back(anim);
			_myAnimations[j]->setTimePosition(0);//que empiece desde el principio la animacion
			_myAnimations[j]->setEnabled(_active);
			_myAnimations[j]->setLoop(_loop);
		}
		catch (Ogre::Exception& e) {
#if (defined _DEBUG)
			std::cout << "Fallo al cambiar a la animacion " << name << "\n";
#endif
			//si ocurre un fallo hay que volver a poner las animaciones que habia antes
			for (int i = 0; i < _myAnimations.size(); ++i)
			{
				_myAnimations[i]->setEnabled(false);				
			}
			_myAnimations.clear();

			for (int i = 0; i < aux.size(); ++i)
			{
				_myAnimations.push_back(aux[i]);
				_myAnimations[i]->setEnabled(_active);
			}
			return false;
		}
		j++;
	}
	return true;
}

void Animation::frameRendered(const Ogre::FrameEvent& evt) {
	if (!_active) return;
	for(auto i:_myAnimations)
		i->addTime(evt.timeSinceLastFrame);
}
