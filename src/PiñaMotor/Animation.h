#pragma once
#include "Component.h"
#include <vector>
#include <OgreAnimation.h>

class Animation :   public Component {
public:
	Animation() { }
	/// <summary>
	/// inicializa el componente con los valores pasados por parametro
	/// </summary>
	bool init(const std::map<std::string, std::string>& mapa) override;

	/// <summary>
	/// activa el flag de animar en bucle
	/// </summary>
	void setLoop(bool loop) {
		_loop = loop;
	}

	/// <summary>
	/// empieza a animar
	/// </summary>
	void play() {
		_active = true;
	}

	/// <summary>
	/// para de animar
	/// </summary>
	void stop() {
		_active = false;
	}

	/// <summary>
	/// devuelve true si esta en bucle la animacion
	/// </summary>
	bool isLoop() {
		return _loop;
	}

	/// <summary>
	/// cambia la animacion que va a usar, si no existe esa animacion devuelve false y no cambia de animacion
	/// </summary>
	bool setAnimation(std::string animationName);

private:
	bool _loop;
	bool _active;//si queremos que no se anime
	//std::vector<Ogre::AnimationState*> animations;//todas las animacion que tiene 
	std::string _animationName;
	Ogre::Entity* _ogreEnt;
	Ogre::AnimationState* _myAnimation;//la animacion que estas usando

};

