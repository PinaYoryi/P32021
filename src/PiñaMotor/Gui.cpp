#include "Gui.h"
#include "OgreMotor.h"

Gui::Gui() {
	_mRenderer = &CEGUI::OgreRenderer::bootstrapSystem(*OgreMotor::GetInstance()->getRoot()->getRenderTarget(""));
	_mRoot = OgreMotor::GetInstance()->getRoot();
	_mWindow = OgreMotor::GetInstance()->getRenderWindow();
	_mContext = &CEGUI::System::getSingleton().getDefaultGUIContext();

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("NombreCarpetaImagenes");
	CEGUI::Font::setDefaultResourceGroup("NombreCarpetaFuentes");
	CEGUI::Scheme::setDefaultResourceGroup("NombreCarpetaEsquemas");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("NombreCarpetaWidget");
	CEGUI::WindowManager::setDefaultResourceGroup("NombreCarpetaLayouts");

	_mWindowManager = &CEGUI::WindowManager::getSingleton();
	_sheet = _mWindowManager->createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_sheet);

	createFrameListener();
}

bool Gui::Init() {
	if (_guiInstance != nullptr) return false;
	_guiInstance = new Gui();
}

void Gui::createFrameListener(){
	auto windowHnd = 0;
	std::ostringstream windowHndStr;

	_mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;

	// Set initial mouse clipping size
	windowResized(_mWindow);

	_mRoot->addFrameListener(this);
}

void Gui::windowResized(Ogre::RenderWindow* w){

	unsigned int width = 0, height = 0, depth = 0;
	int left = 0, top = 0;
	w->getMetrics(width, height, depth, left, top);
	CEGUI::Sizef newSize(width, height);
	// mRenderer_->setDisplaySize(newSize);
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(newSize);
}
