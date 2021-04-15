#include "OgreInstance.h"

OgreInstance* OgreInstance::_singleton = nullptr;

OgreInstance* OgreInstance::getInstance() {
	if (_singleton == nullptr) 
		_singleton = new OgreInstance();

	return _singleton;
}
