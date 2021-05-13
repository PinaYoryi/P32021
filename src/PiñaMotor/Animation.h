#pragma once
#include "Component.h"
#include "OgreMotor.h"

class Animation : public Component, public InputListener {
public:
	Animation() { }

	/// <summary>
	/// Inicializa el componente con los valores pasados por parametro
	/// </summary>
	bool init(const std::map<std::string, std::string>& mapa) override;

	/// <summary>
	/// Activa el flag de animar en bucle
	/// </summary>
	void setLoop(bool loop);

	/// <summary>
	/// Empezar a animar
	/// </summary>
	void play();

	/// <summary>
	/// Parar de animar
	/// </summary>
	void stop();

	/// <summary>
	/// Devuelve true si esta en bucle la animacion
	/// </summary>
	bool isLoop() {
		return _loop;
	}

	/// <summary>
	/// Cambia la animacion que va a usar, si no existe esa animacion devuelve false y no cambia de animacion
	/// </summary>
	bool changeAnimation(std::string animationName);

	/// <summary>
	/// Cambia las animaciones que va a usar, si no existe alguna animacion devuelve false y no cambia ninguna animacion
	/// </summary>
	bool changeAnimation(std::vector<std::string> animationsNames);

	/// <summary>
	/// Mdifica el tiempo que lleva en un frame para cambiar al siguiente
	/// </summary>
	virtual void frameRendered(const Ogre::FrameEvent& evt);

private:
	bool _loop = true;
	bool _playing = true;//si queremos que no se anime
	Ogre::Entity* _ogreEnt = nullptr;
	std::vector< Ogre::AnimationState*> _myAnimations;//las animaciones que tienes activas
};

