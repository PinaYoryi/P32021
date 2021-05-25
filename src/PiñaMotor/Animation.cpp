#include "Animation.h"
#include "Entity.h"
#include "Renderer.h"
#include "OgreEntity.h"
#include "OgreMotor.h"

Animation::~Animation()
{
	OgreMotor::GetInstance()->removeInputListener(this);
}

bool Animation::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("animations") == mapa.end() || mapa.find("playing") == mapa.end() || mapa.find("loop") == mapa.end()) return false;

	//el try es necesario para que no explote la aplicacion si da algun error ogre
	if (_myEntity->hasComponent<Renderer>() && _myEntity->getComponent<Renderer>()->isInitialized()) {
		_ogreEnt = _myEntity->getComponent<Renderer>()->getOgreEntity();
		try {
			OgreMotor::GetInstance()->addInputListener(this);
			std::string an = mapa.at("animations");
			int iterator = 0;
			std::string na = "";
			while ((na = an.substr(0, an.find(","))) != "") {
				iterator = na.length() + 1;
				if (iterator != an.length() + 1)
				{
					an = an.substr(iterator);
					_myAnimations.push_back(_ogreEnt->getAnimationState(na));
				}
				else {
					_myAnimations.push_back(_ogreEnt->getAnimationState(na));
					break;
				}
			};

			if (mapa.at("playing") == "true") _playing = true;
			else if (mapa.at("playing") == "false") _playing = false;
			else return false;

			if (mapa.at("loop") == "true") _loop = true;
			else if (mapa.at("loop") == "false") _loop = false;
			else return false;

			for (Ogre::AnimationState* anim : _myAnimations) {
				if (_playing) play();
				else stop();
				setLoop(_loop);
			}
			return true;
		}
		catch (Ogre::Exception& e) {
#if (defined _DEBUG)
			std::cout << "Fallo al iniciar el componente animation" << "\n";
#endif
			return false;
		}
	}
	_initialized = true;
	return false;
}

void Animation::setLoop(bool loop) {
	_loop = loop;
	for (auto an : _myAnimations)
		an->setLoop(_loop);
}

void Animation::play() {
	_playing = true;
	for (auto an : _myAnimations)
		an->setEnabled(_playing);
}

void Animation::stop() {
	_playing = false;
	for (auto an : _myAnimations)
		an->setEnabled(_playing);
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

		_myAnimations[0]->setEnabled(_playing);
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
			_myAnimations[i]->setEnabled(_playing);
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
			_myAnimations[j]->setEnabled(_playing);
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
				_myAnimations[i]->setEnabled(_playing);
			}
			return false;
		}
		j++;
	}
	return true;
}

void Animation::frameRendered(const Ogre::FrameEvent& evt) {
	if (!_active) return;
	for (auto i : _myAnimations)
		i->addTime(evt.timeSinceLastFrame);
}
