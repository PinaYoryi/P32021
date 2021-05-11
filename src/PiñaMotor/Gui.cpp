#include "Gui.h"
#include "OgreMotor.h"

Gui::Gui() {
	//_mRenderer = &CEGUI::OgreRenderer::bootstrapSystem(*OgreSDLContext::getInstance()->getRenderTarget());
	_mRoot = OgreMotor::GetInstance()->getRoot();
	_mWindow = OgreMotor::GetInstance()->getRenderWindow();
	//mContext_ = &CEGUI::System::getSingleton().getDefaultGUIContext();

	//CEGUI::ImageManager::setImagesetDefaultResourceGroup("NombreCarpetaImagenes");
	//CEGUI::Font::setDefaultResourceGroup("NombreCarpetaFuentes");
	//CEGUI::Scheme::setDefaultResourceGroup("NombreCarpetaEsquemas");
	//CEGUI::WidgetLookManager::setDefaultResourceGroup("NombreCarpetaWidget");
	//CEGUI::WindowManager::setDefaultResourceGroup("NombreCarpetaLayouts");

	//_mWindowManager = &CEGUI::WindowManager::getSingleton();
	//_sheet = _mWindowManager->createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	//CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet_);

	//createFrameListener();
}

bool Gui::Init() {
	if (_guiInstance != nullptr) return false;
	_guiInstance = new Gui();
}