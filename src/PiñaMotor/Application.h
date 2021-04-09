#pragma once

#include "ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreRoot.h>

class Application : public  ApplicationContext
{
public:
    explicit Application() : ApplicationContext("Application") { };  // new -> setup()  
    virtual ~Application() { };   // delete -> shutdown()  

protected:
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();

    //virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // tendrá que estar nuestro input

    Ogre::SceneManager* mSM = nullptr;
    Ogre::Camera* mCam = nullptr;

    Ogre::SceneNode* mCamNode = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;

    Ogre::Viewport* vp = nullptr;
    bool lEnabled = false;
    bool kEnabled = false;
};