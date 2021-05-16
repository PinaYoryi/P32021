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

CEGUI::Window* Gui::createButton(const std::string& text,
	const glm::vec2 position,
	const glm::vec2 size,
	const std::string& name) {
	CEGUI::Window* button = CEGUI::WindowManager::getSingleton().createWindow(_scheme + "/Button", name);

	setWidgetDestRect(button, position, size);
	button->setText(text);
	_sheet->addChild(button);

	return button;
}

CEGUI::Window* Gui::createSlider(glm::vec2 position, glm::vec2 size,
	const std::string& name) {
	CEGUI::Window* slider = CEGUI::WindowManager::getSingleton().createWindow(_scheme + "/Slider");
	setWidgetDestRect(slider, position, size);
	slider->setRotation(CEGUI::Quaternion(1, 0, 0, 0.71));
	slider->setName(name);
	_sheet->addChild(slider);

	return slider;
}

CEGUI::Window* Gui::createLabel(const std::string& text,
	const glm::vec2 position,
	const glm::vec2 size,
	const std::string& name) {
	CEGUI::Window* label = CEGUI::WindowManager::getSingleton().createWindow(_scheme + "/StaticText", name);
	setWidgetDestRect(label, position, size);

	label->setText(text);
	label->setProperty("FrameEnabled", "false");
	label->setProperty("BackgroundEnabled", "false");

	_sheet->addChild(label);

	return label;
}

CEGUI::Window* Gui::createImage(const std::string& image,
	glm::vec2 position, glm::vec2 size,
	const std::string& name) {
	CEGUI::Window* staticImage = CEGUI::WindowManager::getSingleton().createWindow(_scheme + "/StaticImage", name);
	setWidgetDestRect(staticImage, position, size);

	staticImage->setProperty("FrameEnabled", "false");
	staticImage->setProperty("BackgroundEnabled", "false");
	staticImage->setProperty("Image", image);

	_sheet->addChild(staticImage);

	return staticImage;
}


void Gui::createFrameListener() {
	auto windowHnd = 0;
	std::ostringstream windowHndStr;
	_mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	windowResized(_mWindow);
	_mRoot->addFrameListener(this);
}

void Gui::windowResized(Ogre::RenderWindow* w) {
	unsigned int width = 0, height = 0, depth = 0;
	int left = 0, top = 0;
	w->getMetrics(width, height, depth, left, top);
	CEGUI::Sizef newSize(width, height);
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(newSize);
}


void Gui::loadScheme(const std::string& schemeName, const std::string& schemeFile) {
	_scheme = schemeName;
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void Gui::setWidgetDestRect(CEGUI::Window* widget, const glm::vec2 position, const glm::vec2 size) {
	widget->setPosition(CEGUI::UVector2(CEGUI::UDim(position.x, 0),
		CEGUI::UDim(position.y, 0)));
	widget->setSize(
		CEGUI::USize(CEGUI::UDim(0, size.x), CEGUI::UDim(0, size.y)));
}