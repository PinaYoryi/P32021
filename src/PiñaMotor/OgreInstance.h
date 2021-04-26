#pragma once
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "OgreRoot.h"
#include <iostream>

class OgreInstance {
public:

	/// <summary>
	/// Devuelve una instancia de la clase. Devuelve nullptr por defecto si no se ha inicializado.
	/// Para inicializarla se usa OgreInstance().
	/// </summary>
	static OgreInstance* GetInstance();

	static bool Init();

	/// <summary>
	/// Devuelve un puntero a la ventana creada
	/// </summary>
	/// <returns></returns>
	Ogre::RenderWindow* getRenderWindow() {
		return _renderWindow;
	}

	/// <summary>
	/// devuelve un puntero de mSM que es el sceneManager
	/// </summary>
	Ogre::SceneManager* getmSM() {
		return _mSM;
	}

	/// <summary>
	/// guarda una referencia al sceneManager
	/// </summary>
	void setmSM(Ogre::SceneManager* mSM) {
		_mSM = mSM;
	}
	~OgreInstance() {  }

protected:
	static OgreInstance* _singleton;
	Ogre::SceneManager* _mSM = nullptr;
	Ogre::RenderWindow* _renderWindow = nullptr;
};