#include "Application.h"

#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreCompositorManager.h>
#include <OgreRenderWindow.h>

using namespace Ogre;

void Application::shutdown()
{
	mRoot->destroySceneManager(mSM);
	delete mCam;

	// do not forget to call the base 
	ApplicationContext::shutdown();
}

void Application::setup(void)
{
	// do not forget to call the base first
	ApplicationContext::setup();

	mRoot->showConfigDialog(NULL);

	mSM = mRoot->createSceneManager();

	setupScene();
}

void Application::setupScene(void)
{
	// create the camera
	mCam = mSM->createCamera("Cam");
	mCam->setNearClipDistance(1);
	mCam->setFarClipDistance(10000);
	mCam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(mCam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	vp = getRenderWindow()->addViewport(mCam);
	vp->setBackgroundColour(Ogre::ColourValue(153.0/250.0, 50.0/255.0, 204/255.0));
	CompositorManager::getSingleton().addCompositor(vp, "Luminance");
	CompositorManager::getSingleton().addCompositor(vp, "IG2/EdgeEmboss");


	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1.0, 1.0, 1.0);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();*/
	//lightNode->setPosition(0, 0, 1000);

	mSM->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2, 1.0));

	//------------------------------------------------------------------------

	//mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -50), "IG2/spaceGLSL", 1, 1, true, 1.0, 10, 10);	//true, Plane(Vector3::UNIT_Z, -200), "IG2/space", 1, 1, true, 0, 10, 10
}