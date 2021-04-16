#pragma once
#include "Component.h"
#include <OgreCamera.h>
class Camera :
    public Component
{
public:
    Camera();
    bool init(const std::map<std::string, std::string>& mapa) override {}
protected:
    void Render() override;

    Ogre::Camera* _cam;
    Ogre::Node* _camNode;
};

