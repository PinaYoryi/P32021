#include "OgreInstance.h"

OgreInstance* OgreInstance::_singleton = nullptr;

OgreInstance* OgreInstance::GetInstance() {
	return _singleton;
}

bool OgreInstance::Init() {
	if (_singleton != nullptr) return false;
	_singleton = new OgreInstance(); return true;
}