#include "Gui.h"
#include "OgreMotor.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <iostream>

Gui* Gui::_guiInstance = nullptr;

Gui::Gui() {
	_mRenderer = &CEGUI::OgreRenderer::bootstrapSystem(*OgreMotor::GetInstance()->getRenderTarget());
	_mRoot = OgreMotor::GetInstance()->getRoot();
	_mWindow = OgreMotor::GetInstance()->getRenderWindow();
	_mContext = &CEGUI::System::getSingleton().getDefaultGUIContext();
	
	Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
	
	_mRenderer->setUsingShaders(true);
	
	// Esto es como ponerlo en el resources.cfg
	// rgm.createResourceGroup("imagesets");
	// rgm.createResourceGroup("fonts");
	// rgm.createResourceGroup("layouts");
	// rgm.createResourceGroup("schemes");
	// rgm.createResourceGroup("looknfeels");
	// rgm.createResourceGroup("lua_scripts");
	// 
	// rgm.addResourceLocation("../../assets/resources/gui/schemes/", "FileSystem", "schemes");
	// rgm.addResourceLocation("../../assets/resources/gui/imagesets/", "FileSystem", "imagesets");
	// rgm.addResourceLocation("../../assets/resources/gui/fonts/", "FileSystem", "fonts");
	// rgm.addResourceLocation("../../assets/resources/gui/layouts/", "FileSystem", "layouts");
	// rgm.addResourceLocation("../../assets/resources/gui/looknfeels/", "FileSystem", "looknfeels");
	// rgm.addResourceLocation("../../assets/resources/gui/lua_scripts/", "FileSystem", "lua_scripts");
	
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::AnimationManager::setDefaultResourceGroup("animations");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	
	_mWindowManager = &CEGUI::WindowManager::getSingleton();
	_ceguiWindow = _mWindowManager->createWindow("DefaultWindow", "PinaYoryiGUI");
	_mContext->setRootWindow(_ceguiWindow);
	
	createFrameListener();
}

Gui::~Gui() {
	CEGUI::OgreRenderer::destroySystem();
}

bool Gui::Init() {
	if (_guiInstance != nullptr) return false;
	_guiInstance = new Gui();
	_guiInstance->initResources("TaharezLook", "TaharezLook/MouseArrow", false);
	return true;
}


void Gui::captureInput(const SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT)
			_mContext->injectMouseButtonDown(CEGUI::LeftButton);
		else if (event.button.button == SDL_BUTTON_RIGHT)
			_mContext->injectMouseButtonDown(CEGUI::RightButton);

	}
	else if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT)
			_mContext->injectMouseButtonUp(CEGUI::LeftButton);
		else if (event.button.button == SDL_BUTTON_RIGHT)
			_mContext->injectMouseButtonUp(CEGUI::RightButton);

	}
	else if (event.type == SDL_MOUSEMOTION) {
		_mContext->injectMousePosition((event.motion.x), (event.motion.y));

	}
	else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED ||
		event.window.event == SDL_WINDOWEVENT_RESIZED ||
		event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		windowResized(_mWindow);
}

CEGUI::Window* Gui::createButton(const std::string& text, const glm::vec2 position, const glm::vec2 size, const std::string& name) {
	CEGUI::Window* button = CEGUI::WindowManager::getSingleton().createWindow(_scheme + "/Button", name);

	setWidgetDestRect(button, position, size);
	button->setText(text);
	_ceguiWindow->addChild(button);

	return button;
}

CEGUI::Window* Gui::createText(const std::string& text, glm::vec2 position, glm::vec2 size, const std::string& name)
{
	CEGUI::Window* textG = CEGUI::WindowManager::getSingleton().createWindow(_scheme + "/Text", name);

	setWidgetDestRect(textG, position, size);
	textG->setText(text);
	_ceguiWindow->addChild(textG);

	return textG;
}

CEGUI::Window* Gui::createSlider(glm::vec2 position, glm::vec2 size, const std::string& name) {
	CEGUI::Window* slider = CEGUI::WindowManager::getSingleton().createWindow(_scheme + "/Slider");
	setWidgetDestRect(slider, position, size);
	slider->setRotation(CEGUI::Quaternion(1, 0, 0, 0.71));
	slider->setName(name);
	_ceguiWindow->addChild(slider);

	return slider;
}

CEGUI::Window* Gui::createLabel(const std::string& text, const glm::vec2 position, const glm::vec2 size, const std::string& name) {
	CEGUI::Window* label = CEGUI::WindowManager::getSingleton().createWindow(_scheme + "/StaticText", name);
	setWidgetDestRect(label, position, size);

	label->setText(text);
	label->setProperty("FrameEnabled", "false");
	label->setProperty("BackgroundEnabled", "false");

	_ceguiWindow->addChild(label);

	return label;
}

CEGUI::Window* Gui::createImage(const std::string& image, glm::vec2 position, glm::vec2 size, const std::string& name) {
	CEGUI::Window* staticImage = CEGUI::WindowManager::getSingleton().createWindow(_scheme + "/StaticImage", name);
	setWidgetDestRect(staticImage, position, size);

	staticImage->setProperty("FrameEnabled", "false");
	staticImage->setProperty("BackgroundEnabled", "false");
	staticImage->setProperty("Image", image);

	_ceguiWindow->addChild(staticImage);

	return staticImage;
}

void Gui::createFrameListener() {
	size_t windowHnd = 0;
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
	widget->setPosition(CEGUI::UVector2(CEGUI::UDim(position.x, 0), CEGUI::UDim(position.y, 0)));
	widget->setSize(CEGUI::USize(CEGUI::UDim(0, size.x), CEGUI::UDim(0, size.y)));
}

void Gui::setFont(const std::string& fontFile) {
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");

	_mContext->setDefaultFont(fontFile);
	_mContext->getDefaultFont()->setAutoScaled(CEGUI::AutoScaledMode::ASM_Disabled);
}

void Gui::setMouseImage(const std::string& imageFile) {
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(imageFile);
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(imageFile);
}

void Gui::setMouseVisibility(bool b) {
	if (b)
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
	else {
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
		_ceguiWindow->setUsingAutoRenderingSurface(true);
	}
}

void Gui::initResources(std::string schemeName, std::string mouseName, bool visible)
{
	Gui::GetInstance()->loadScheme(schemeName, schemeName + ".scheme");
	Gui::GetInstance()->setMouseImage(mouseName);
	Gui::GetInstance()->setMouseVisibility(visible);
}

void Gui::mouseVisible(bool visible)
{
	Gui::GetInstance()->setMouseVisibility(visible);
}