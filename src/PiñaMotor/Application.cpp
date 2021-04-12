#include "Application.h"

#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreCompositorManager.h>
#include <OgreRenderWindow.h>

using namespace Ogre;

// Destruye el SceneManager y llama a la base
void Application::shutdown(){
	_mRoot->destroySceneManager(_mSM);

	ApplicationContext::shutdown();
}

// Llama a la base, crea el config y el SceneManager e incia la escena
void Application::setup(void){
	ApplicationContext::setup();

	_mRoot->showConfigDialog(NULL);

	_mSM = _mRoot->createSceneManager();

	setupScene();
}

// Genera los componentes de una escena básica
void Application::setupScene(void){
	// Genera cámara
	_mCam = _mSM->createCamera("Cam");
	_mCam->setNearClipDistance(1);
	_mCam->setFarClipDistance(10000);
	_mCam->setAutoAspectRatio(true);

	// La añade a su nodo y lo posiciona
	_mCamNode = _mSM->getRootSceneNode()->createChildSceneNode("nCam");
	_mCamNode->attachObject(_mCam);

	_mCamNode->setPosition(0, 0, 1000);
	_mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	// Crea el viewport de la cámara
	_vp = getRenderWindow()->addViewport(_mCam);
	_vp->setBackgroundColour(Ogre::ColourValue(153.0/250.0, 50.0/255.0, 204/255.0));

	// Crea una luz en la escena
	Light* luz = _mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1.0, 1.0, 1.0);

	// Une la luz a un nodo y lo posiciona
	_mLightNode = _mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	_mLightNode->attachObject(luz);

	_mLightNode->setDirection(Ogre::Vector3(0, -1, -1)); 

	// Pone la luz ambiente de la escena
	_mSM->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2, 1.0));
}