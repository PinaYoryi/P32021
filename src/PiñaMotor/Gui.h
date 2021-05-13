#pragma once
#include <CEGUI/CEGUI.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Ogre.h>
#include <iostream>

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

	// Render de la ventana
	Ogre::RenderWindow* _mWindow = nullptr;

	// Raiz del nodo de la escena
	Ogre::Root* _mRoot = nullptr;

	// Render de ogre para Cegui
	CEGUI::OgreRenderer* _mRenderer = nullptr;

	// Propio de Cegui: alberga RenderingSurface, InjectedInputReceiver
	CEGUI::GUIContext* _mContext = nullptr;

	// Ventana de la aplicacion usada por Cegui
	CEGUI::Window* _sheet = nullptr;

	// Gestor de la ventana
	CEGUI::WindowManager* _mWindowManager = nullptr;
};