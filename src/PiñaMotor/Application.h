#pragma once

#include "ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreRoot.h>

/// <summary>
/// Aplicación que hereda de ApplicationContext
/// Inicializa datos específicos de la aplicación con base en ApplicationContext
/// </summary>
class Application : public  ApplicationContext
{
public:
    explicit Application() : ApplicationContext("Application") { };  
    virtual ~Application() { };

protected:
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();

    Ogre::SceneManager* _mSM = nullptr;
    Ogre::Camera* _mCam = nullptr;

    Ogre::SceneNode* _mCamNode = nullptr;
    Ogre::SceneNode* _mLightNode = nullptr;

    Ogre::Viewport* _vp = nullptr;
    bool _lEnabled = false;
    bool _kEnabled = false;
};