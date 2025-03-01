#include "OgreMotor.h"

#include <OgreRoot.h>
#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreDataStream.h>
#include <OgreMaterialManager.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#include <OgreSTBICodec.h>

OgreMotor* OgreMotor::_instance = nullptr;

OgreMotor::OgreMotor(const Ogre::String& appName) {
	_mAppName = appName;
	_mRoot = nullptr;
	_mFirstRun = true;

	_mShaderGenerator = nullptr;
	_mMaterialMgrListener = nullptr;
}

OgreMotor::~OgreMotor() {
	delete _mFSLayer;
	if (_ogreWasInit) Close();
}

OgreMotor* OgreMotor::GetInstance() {
	return _instance;
}

bool OgreMotor::Init(const Ogre::String& appName) {
	if (_instance != nullptr) 
		return false;

	_instance = new OgreMotor(appName); 
	_instance->initApp();
	return true;
}

void OgreMotor::initApp() {
	_mFSLayer = new Ogre::FileSystemLayer(_mAppName);
	createRoot();

	if (oneTimeConfig())
		setup();
	

	_ogreWasInit = true;
}

bool OgreMotor::Close() {
	if (_instance)
		_instance->closeApp();
	else
		return false;
	delete _instance;
	return true;
}

void OgreMotor::closeApp() {
	try {
		if (_mRoot != nullptr)
		{
			_mRoot->saveConfig();
		}
		shutdown();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	Ogre::STBIImageCodec::shutdown();
	delete _mRoot;
	_mRoot = nullptr;
	_ogreWasInit = false;
}

void OgreMotor::createRoot() {
	Ogre::String pluginsPath;
	pluginsPath = _mFSLayer->getConfigFilePath("plugins.cfg");

	if (!Ogre::FileSystemLayer::fileExists(pluginsPath))
	{	
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "createRoot");
	}

	_mSolutionPath = pluginsPath;    
	_mSolutionPath.erase(_mSolutionPath.find_last_of("\\") + 1, _mSolutionPath.size() - 1);
	_mFSLayer->setHomePath(_mSolutionPath); 
	_mSolutionPath.erase(_mSolutionPath.find_last_of("\\") + 1, _mSolutionPath.size() - 1);

	_mRoot = new Ogre::Root(pluginsPath, _mFSLayer->getWritablePath("ogre.cfg"), _mFSLayer->getWritablePath("ogre.log"));
	_mRoot->setRenderSystem(_mRoot->getRenderSystemByName("OpenGL Rendering Subsystem"));
}

void OgreMotor::shutdown() {
	destroyRTShaderSystem();
	_mRoot->destroySceneManager(_mSM);

	if (_mWindow._render != nullptr)
	{
		_mRoot->destroyRenderTarget(_mWindow._render);
		_mWindow._render = nullptr;
	}

	if (_mWindow._native != nullptr)
	{
		SDL_DestroyWindow(_mWindow._native);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		_mWindow._native = nullptr;
	}
}

void OgreMotor::setup() {
	_mRoot->initialise(false);
	createWindow(_mAppName);
	setWindowGrab(false);

	locateResources();
	initialiseRTShaderSystem();
	loadResources();

	_mRoot->addFrameListener(this);
	_mRoot->showConfigDialog(NULL);

	_mSM = _mRoot->createSceneManager();
	_mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	_mShaderGenerator->addSceneManager(_mSM);
}

bool OgreMotor::oneTimeConfig() {
	if (!_mRoot->restoreConfig())
	{
		return _mRoot->showConfigDialog(NULL);
	}
	else return true;
}

NativeWindowPair OgreMotor::createWindow(const Ogre::String& name) {
	uint32_t w, h;
	Ogre::NameValuePairList miscParams;

	Ogre::ConfigOptionMap ropts = _mRoot->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
	mode >> w; 
	mode >> token; 
	mode >> h; 

	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_RESIZABLE;

	if (ropts["Full Screen"].currentValue == "Yes")  flags = SDL_WINDOW_FULLSCREEN;

	_mWindow._native = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_mWindow._native, &wmInfo);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	_mWindow._render = _mRoot->createRenderWindow(name, w, h, false, &miscParams);
	return _mWindow;
}

void OgreMotor::setWindowGrab(bool _grab) {
	SDL_bool grab = SDL_bool(_grab);
	SDL_SetWindowGrab(_mWindow._native, grab);
	SDL_ShowCursor(grab);
}

Ogre::RenderTarget* OgreMotor::getRenderTarget() { return _mRoot->getRenderTarget(_mWindow._render->getName()); }

bool OgreMotor::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	for (std::set<InputListener*>::iterator it = mInputListeners.begin(); it != mInputListeners.end(); ++it)
	{
		(*it)->frameRendered(evt);
	}
	return true;
}

void OgreMotor::pollEvents() {
	if (_mWindow._native == nullptr)
		return;  

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_mRoot->queueEndRendering();
			break;
		case SDL_WINDOWEVENT:
			if (event.window.windowID == SDL_GetWindowID(_mWindow._native)) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					Ogre::RenderWindow* win = _mWindow._render;
					win->windowMovedOrResized();
					windowResized(win);
				}
			}
			break;
		default:				
			break;
		}
	}
}

void OgreMotor::loadResources() {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void OgreMotor::locateResources() {
	Ogre::ConfigFile cf;

	Ogre::String resourcesPath = _mFSLayer->getConfigFilePath("resources.cfg");
	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
	{
		cf.load(resourcesPath);
	}
	else
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath(_mSolutionPath + "\\media"),
			"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

	Ogre::String sec, type, arch;
		
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	arch = genLocs.front().archive->getName();
	type = genLocs.front().archive->getType();

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
	}
	mRTShaderLibPath = arch + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/HLSL", type, sec);
	}
}

void OgreMotor::createNewScene() {
	_mSM->getRootSceneNode()->removeAndDestroyAllChildren();
	_mRoot->destroySceneManager(_mSM);
	_mRoot->initialise(false);
	_mRoot->addFrameListener(this);
	_mSM = _mRoot->createSceneManager();

	_mShaderGenerator->addSceneManager(_mSM);
}

void OgreMotor::addInputListener(InputListener* lis) { mInputListeners.insert(lis); }

void OgreMotor::removeInputListener(InputListener* lis) { mInputListeners.erase(lis); };

#pragma region metodos de RTShader para poder renderizar
bool OgreMotor::initialiseRTShaderSystem()
{
	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		_mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

		// Core shader libs not found -> shader generating will fail.
		if (mRTShaderLibPath.empty())
			return false;
		// Create and register the material manager listener if it doesn't exist yet.
		if (!_mMaterialMgrListener) {
			_mMaterialMgrListener = new SGTechniqueResolverListener(_mShaderGenerator);
			Ogre::MaterialManager::getSingleton().addListener(_mMaterialMgrListener);
		}
	}

	return true;
}
void OgreMotor::destroyRTShaderSystem()
{
	// Restore default scheme.
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// Unregister the material manager listener.
	if (_mMaterialMgrListener != nullptr)
	{
		Ogre::MaterialManager::getSingleton().removeListener(_mMaterialMgrListener);
		delete _mMaterialMgrListener;
		_mMaterialMgrListener = nullptr;
	}

	// Destroy RTShader system.
	if (_mShaderGenerator != nullptr)
	{
		Ogre::RTShader::ShaderGenerator::destroy();
		_mShaderGenerator = nullptr;
	}
}

#pragma endregion