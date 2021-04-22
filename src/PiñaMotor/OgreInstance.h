#pragma once
#include "OgreSceneManager.h"
#include "OgreRoot.h"
#include <iostream>

class OgreInstance {
public:

	/// <summary>
	/// Devuelve una instancia de la clase. Devuelve nullptr por defecto si no se ha inicializado.
	/// Para inicializarla se usa OgreInstance().
	/// </summary>
	static OgreInstance* GetInstance();

	/// <summary>
	/// Inicializa la clase OgreInstance con los parametros dados si no se ha inicializado antes.
	/// Devuelve true si se inicializa por primera vez y false si ya hab�a sido inicializada.
	/// Todo: Implementar los parametros a inicializar.
	/// </summary>
	static bool Init();



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

};