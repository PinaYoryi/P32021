#include "PlayerController.h"
#include "Entity.h"
#include "Input.h"
#include "OgreMotor.h"
#include <OgreRenderWindow.h>

PlayerController::PlayerController() : _trans(nullptr) {
}

bool PlayerController::init(const std::map<std::string, std::string>& mapa) {
	//TODO: rellenar init con los valores del mapa
	//El try es necesario para que no explote la aplicacion si no hay camara que usar
	if (_myEntity->hasComponent<Transform>()) {
		_trans = _myEntity->getComponent<Transform>();
		return true;
	}
#if (defined _DEBUG)
	std::cout << "Fallo al iniciar el componente PlayerController\n";
#endif
	return false;
}

void PlayerController::update() {
	if (Input::GetInstance()->keyDown(SDL_SCANCODE_ESCAPE)) _active = !_active;
	if (!_active) return;
	Ogre::RenderWindow* win = OgreMotor::GetInstance()->getRenderWindow();
	Vector2<int> center(win->getWidth() / 2, win->getHeight() / 2);
	Vector2<int> dir = Input::GetInstance()->getMousePos() - center; dir /= 2;
	_trans->rotate(-dir.y, -dir.x, 0.0f);
	//_trans->setRotation(_trans->rotation());
	Input::GetInstance()->setMousePos(center);
}