#include "OgreInstance.h"

OgreInstance* OgreInstance::_singleton = nullptr;

OgreInstance* OgreInstance::getInstance() {
	if (_singleton == nullptr) {
		_singleton = new OgreInstance();
#if (defined _DEBUG) || !(defined _WIN32) //<-- Ya no lo tenemos en teor�a
		std::cout << "Nueva instancia del bucle\n";
#endif

	}
#if (defined _DEBUG) || !(defined _WIN32) //<-- Ya no lo tenemos en teor�a

	else std::cout << "Misma instancia del bucle\n";
#endif

	return _singleton;
}
