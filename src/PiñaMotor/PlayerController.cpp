#include "PlayerController.h"
#include "Entity.h"
#include "Input.h"
#include "OgreMotor.h"
#include <OgreRenderWindow.h>

PlayerController::PlayerController() : _trans(nullptr), _sensibility(0), _pitch(0), _yaw(0) {
}

bool PlayerController::init(const std::map<std::string, std::string>& mapa) {
	//TODO: rellenar init con los valores del mapa
	//El try es necesario para que no explote la aplicacion si no hay camara que usar
	if (!_myEntity->hasComponent<Transform>()) {
#if (defined _DEBUG)
		std::cout << "Fallo al iniciar el componente PlayerController\n";
#endif
		return false;
	}
	_trans = _myEntity->getComponent<Transform>();
	_pitch = _yaw = 0;
	_sensibility = 1.0f;

	return true;
}

void PlayerController::update() {
	if (Input::GetInstance()->keyDown(SDL_SCANCODE_ESCAPE)) _active = !_active;
	if (!_active) return;
	Ogre::RenderWindow* win = OgreMotor::GetInstance()->getRenderWindow();
	Vector2<int> center(win->getWidth() / 2, win->getHeight() / 2);
	Vector2<int> dir = Input::GetInstance()->getMousePos() - center;

	_pitch -= dir.y * _sensibility;
	if (_pitch > 90) _pitch = 90;
	else if (_pitch < -90) _pitch = -90;

	_yaw -= dir.x * _sensibility;
	if (_yaw >= 180) _yaw -= 360;
	else if (_yaw < -180) _yaw += 360;

#if (defined _DEBUG)
	std::cout << _yaw << " " << _pitch << "\n";
#endif

	_trans->setLocalRotation(Quaternion::Euler({ _pitch, _yaw, 0 }));
	Input::GetInstance()->setMousePos(center);
}