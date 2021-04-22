#pragma once

#include <string>
#include <iostream>

#include <OgreBuildSettings.h>
#include <OgreLogManager.h>
#include <OgrePlugin.h>
#include <OgreFileSystemLayer.h>
#include <OgreFrameListener.h>
#include <SDL.h> 
#undef main

#pragma region clase de ogre Bites para poder renderizar

#include <OgreRTShaderSystem.h>
#include <OgreMaterialManager.h>
#include "OgreTechnique.h"

class SGTechniqueResolverListener : public Ogre::MaterialManager::Listener {
public:
	 SGTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator) {
		 mShaderGenerator = pShaderGenerator;
	 }

	/** This is the hook point where shader based technique will be created.
		It will be called whenever the material manager won't find appropriate technique
		that satisfy the target scheme name. If the scheme name is out target RT Shader System
		scheme name we will try to create shader generated technique for it.
	*/
	Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex,
		const Ogre::String& schemeName,
		Ogre::Material* originalMaterial, unsigned short lodIndex,
		const Ogre::Renderable* rend) {
		if (!mShaderGenerator->hasRenderState(schemeName))
		{
			return NULL;
		}
		// Case this is the default shader generator scheme.

		// Create shader generated technique for this material.
		bool techniqueCreated = mShaderGenerator->createShaderBasedTechnique(
			*originalMaterial,
			Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
			schemeName);

		if (!techniqueCreated)
		{
			return NULL;
		}
		// Case technique registration succeeded.

		// Force creating the shaders for the generated technique.
		mShaderGenerator->validateMaterial(schemeName, *originalMaterial);

		// Grab the generated technique.
		Ogre::Material::Techniques::const_iterator it;
		for (it = originalMaterial->getTechniques().begin(); it != originalMaterial->getTechniques().end(); ++it)
		{
			Ogre::Technique* curTech = *it;

			if (curTech->getSchemeName() == schemeName)
			{
				return curTech;
			}
		}

		return NULL;
	}

	bool afterIlluminationPassesCreated(Ogre::Technique* tech) {
		if (mShaderGenerator->hasRenderState(tech->getSchemeName()))
		{
			Ogre::Material* mat = tech->getParent();
			mShaderGenerator->validateMaterialIlluminationPasses(tech->getSchemeName(),
				mat->getName(), mat->getGroup());
			return true;
		}
		return false;
	}

	bool beforeIlluminationPassesCleared(Ogre::Technique* tech) {
		if (mShaderGenerator->hasRenderState(tech->getSchemeName()))
		{
			Ogre::Material* mat = tech->getParent();
			mShaderGenerator->invalidateMaterialIlluminationPasses(tech->getSchemeName(),
				mat->getName(), mat->getGroup());
			return true;
		}
		return false;
	}

protected:
	Ogre::RTShader::ShaderGenerator* mShaderGenerator; // The shader generator instance.
};
#pragma endregion

#pragma region clase de ogre Bites para poder animar
//no esta toda la clase, solo lo que vamos a usar
struct InputListener {
	virtual ~InputListener() {}
	virtual void frameRendered(const Ogre::FrameEvent& evt) { }	
};

#pragma endregion

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

	
	//Initialize the RT Shader system.	
	bool initialiseRTShaderSystem();

	
	//Destroy the RT Shader system.	
	void destroyRTShaderSystem();

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





	virtual void frameRendered(const Ogre::FrameEvent& evt) { }


	void addInputListener(InputListener* lis) {mInputListeners.insert(lis); }
	void removeInputListener(InputListener* lis) { mInputListeners.erase(lis); };

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


#pragma region atributos de la clase de ogreBites para poder renderizar
	Ogre::String mRTShaderLibPath;
	Ogre::RTShader::ShaderGenerator* _mShaderGenerator; // The Shader generator instance.
	SGTechniqueResolverListener* _mMaterialMgrListener; // Shader generator material manager listener.
	
#pragma endregion



#pragma region atributo para poder animar
	//vector donde se guardan los componentes Animation para poder actualizarlos
	std::set<InputListener*> mInputListeners;
#pragma endregion

};

