#pragma once
#include "OgreSceneManager.h"
#include "OgreRoot.h"

class OgreInstance {
public:
	/// <summary>
	/// Devuelve una instancia de la clase. La crea si no existe.
	/// </summary>
	static OgreInstance* getInstance();

	/// <summary>
	/// devuelve un puntero de mSM que es el sceneManager
	/// </summary>
	Ogre::SceneManager* getmSM() {
		return _mSM;
	}

	/// <summary>
	/// guarda una referencia al sceneManager
	/// </summary>
	void createmSM(Ogre::SceneManager* mSM) {
		_mSM = mSM;
	}

protected:
	static OgreInstance* _singleton;
	Ogre::SceneManager* _mSM = nullptr;
};