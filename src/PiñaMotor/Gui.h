#pragma once
#include <Ogre.h>
#include <glm/glm.hpp>

class SDL_events;

namespace CEGUI {
	class GUIContext;
	class Window;
	class WindowManager;
	class OgreRenderer;
	class System;
}

class Gui : public Ogre::FrameListener {
public:
	Gui();
	~Gui();

	/// <summary>
	/// Devuelve instancia de la clase 
	/// </summary>
	static Gui* GetInstance() { return _guiInstance; };

	/// <summary>
	/// Clase inicializadora
	/// </summary>
	static bool Init();

	void captureInput(const SDL_Event& event);

	CEGUI::Window* createButton(const std::string& text, glm::vec2 position, glm::vec2 size, const std::string& name);

	CEGUI::Window* createSlider(glm::vec2 position, glm::vec2 size, const std::string& name);

	CEGUI::Window* createLabel(const std::string& text, glm::vec2 position, glm::vec2 size, const std::string& name = "");

	CEGUI::Window* createImage(const std::string& image, glm::vec2 position, glm::vec2 size, const std::string& name = "");

	void loadScheme(const std::string& schemeName, const std::string& schemeFile);

	void setWidgetDestRect(CEGUI::Window* widget, const glm::vec2 position, const glm::vec2 size);

	void setFont(const std::string& fontFile);

	void setMouseImage(const std::string& imageFile);

	void setMouseVisibility(bool b);

private:
	/// <summary>
	/// Crea el Frame Listener para que pinte
	/// </summary>
	void createFrameListener();

	/// <summary>
	/// Reescalado de la ventana de Cegui
	/// </summary>
	void windowResized(Ogre::RenderWindow* w);

	// Instancia de la clase
	static Gui* _guiInstance;

	std::string _scheme;

	// Render de la ventana
	Ogre::RenderWindow* _mWindow = nullptr;

	// Raiz del nodo de la escena
	Ogre::Root* _mRoot = nullptr;

	// Render de ogre para Cegui
	CEGUI::OgreRenderer* _mRenderer = nullptr;

	// Propio de Cegui: alberga RenderingSurface, InjectedInputReceiver
	CEGUI::GUIContext* _mContext = nullptr;

	// Ventana de la aplicacion usada por Cegui
	CEGUI::Window* _ceguiWindow = nullptr;

	// Gestor de la ventana
	CEGUI::WindowManager* _mWindowManager = nullptr;
};