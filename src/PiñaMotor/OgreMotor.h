#pragma once

#include <string>
#include <iostream>

#include <OgreBuildSettings.h>
#include <OgreLogManager.h>
#include <OgrePlugin.h>
#include <OgreFileSystemLayer.h>
#include <OgreFrameListener.h>
#include <SDL.h>  

typedef SDL_Window NativeWindowType;

// Enlace entre una RenderWindow y una ventana específica de plataforma
struct NativeWindowPair
{
	Ogre::RenderWindow* _render = nullptr;
	NativeWindowType* _native = nullptr;
};

/// <summary>
/// Clase base con contexto específico para
/// Subclase para implementar eventos específicos de callback
/// </summary>
class OgreMotor : public Ogre::FrameListener {
public:
	explicit OgreMotor(const Ogre::String& appName = OGRE_VERSION_NAME);

	virtual ~OgreMotor();

	// Obtiene la RenderWindow
	Ogre::RenderWindow* getRenderWindow() const { return _mWindow._render; }

	Ogre::Root* getRoot() const { return _mRoot; }

	// Inicializa el render system y recursos
	void initApp();

	// Cierra la aplicación, guarda la configuración y hace shutdowm
	void closeApp();

	// Interfaz de callbacks basada en ApplicationContext
	virtual bool frameStarted(const Ogre::FrameEvent& evt) { pollEvents(); return true; }

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; }

	virtual void windowMoved(Ogre::RenderWindow* rw) {}

	virtual void windowResized(Ogre::RenderWindow* rw) {}

	virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; }

	virtual void windowClosed(Ogre::RenderWindow* rw) {}

	virtual void windowFocusChange(Ogre::RenderWindow* rw) {}

	// Inicia el context tras la configuración
	virtual void setup();

	// Crea el root de OGRE
	virtual void createRoot();

	//  I use the config dialog here,
	//but you can also restore from a config file. Note that this only happens
	//when you start the context, and not when you reset it.
	
	/// <summary>
	/// Configura los settins de incio de OGRE
	/// Sólo ocurre al inciar el context, no al resetearlo
	/// </summary>
	/// <returns>Si ha podido inicializar la configuración</returns>
	virtual bool oneTimeConfig();

	// Confina el ratón a la ventana al detectar input
	void setWindowGrab(bool grab);

	// Usa configs para cargar recursos en el context
	virtual void locateResources();

	// Carga los grupos de recursos del context
	virtual void loadResources();

	// Limpia y cierra el context
	virtual void shutdown();

	// Procesa lso eventos de ventana desde la última llamada
	void pollEvents();

	//Create a new render window
	//You must use SDL and not an auto-created window as SDL does not get the events otherwise.
	//By default the values from ogre.cfg are used for w, h and miscParams.

	/// <summary>
	/// Usa una nueva ventana de renderizado de SDL
	/// Usa valores de ogre.cfg
	/// </summary>
	/// <param name="name">Nombre de la ventana</param>
	/// <returns>La ventana creada</returns>
	virtual NativeWindowPair createWindow(const Ogre::String& name);

	Ogre::SceneManager* getSceneManager() { return _mSM; }
	
	// Borra todos los nodos de la escena, re-inicializa el root y el sceneManager
	void createNewScene();

protected:
	// OGRE root
	Ogre::Root* _mRoot;   
	// Ventana
	NativeWindowPair _mWindow; 

	// Capa de abstracción del sistema de archivos
	Ogre::FileSystemLayer* _mFSLayer; 

	// Variable para identificar primera ejecución
	bool _mFirstRun;
	// Nombre de la aplicación
	Ogre::String _mAppName;
	// Variable para hacer las rutas relativas al directorio de la solución
	Ogre::String _mSolutionPath;    
	
	Ogre::SceneManager* _mSM = nullptr;
};