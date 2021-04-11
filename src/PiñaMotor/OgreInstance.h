#pragma once
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"


class OgreInstance {
public:
	/// <summary>
	/// Devuelve una instancia de la clase. La crea si no existe.
	/// </summary>
	static OgreInstance* getInstance();
	Ogre::SceneManager* getmSM() {
		return mSM;
	}
	
	Ogre::SceneManager* createmSM(Ogre::Root* mRoot) {
		//mSM->mRoot->createSceneManager();
	}

protected:
	static OgreInstance* _singleton;
	Ogre::SceneManager* mSM = nullptr;
};