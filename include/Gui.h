#pragma once
#include <Ogre.h>
#include <glm/glm.hpp>
#include <OgreRenderWindow.h>
#include <SDL.h>
#undef main
//
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

	/// <summary>
	/// Lee y gestiona la entrada de input
	/// </summary>
	void captureInput(const SDL_Event& event);

	// Ajusta las propiedades para crear, respectivamente, un boton, una barra, un rotulo y una imagen
	CEGUI::Window* createButton(const std::string& text, glm::vec2 position, glm::vec2 size, const std::string& name, std::vector<std::string> properties);
	CEGUI::Window* createText(const std::string& text, glm::vec2 position, glm::vec2 size, const std::string& name, std::vector<std::string> properties);
	CEGUI::Window* createImage(const std::string& image, glm::vec2 position, glm::vec2 size, const std::string& name, std::vector<std::string> properties);

	/// <summary>
	/// Carga un tema para la estetica del GUI
	/// </summary>
	void loadScheme(const std::string& schemeName, const std::string& schemeFile);

	// Setea, respectivamente, un widget, la fuente de los textos, la imagen del puntero y su visibilidad y las propiedades de imagen
	void setWidgetDestRect(CEGUI::Window* widget, const glm::vec2 position, const glm::vec2 size);
	void setFont(const std::string& fontFile);
	void setMouseImage(const std::string& imageFile);
	void setMouseVisibility(bool b);

	/// <summary>
	/// Carga los recursos de los botones, puntero... de cegui
	/// </summary>
	void initResources(std::string schemeName, std::string mouseName, bool visible);
	
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