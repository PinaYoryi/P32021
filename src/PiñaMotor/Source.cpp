/*
#include <OgreRoot.h>
#include "Entity.h"
#include "Transform.h"
#include "ComponentFactoryRegistration.h"
#include <btBulletDynamicsCommon.h>
#include "MotorLoop.h"


#if (defined _DEBUG) || !(defined _WIN32) //<-- Ya no lo tenemos en teor�a
int main() {
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	Ogre::Root* root;
	root = new Ogre::Root();
	//TODO: carne de ca�on de macro
 //   ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
 //   Entity* ent = new Entity();
	return 0;
}
/*/

#include <stdlib.h>
#include <stdio.h>
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

static const luaL_Reg lualibs[] = {
		{ "base",       luaopen_base },
		{ NULL,         NULL }
};

void openlualibs(lua_State* l) {
	const luaL_Reg* lib;

	for (lib = lualibs; lib->func != NULL; lib++) {
		lib->func(l);
		lua_settop(l, 0);
	}
}

int main(void) {

	lua_State* l;
	l = luaL_newstate();
	openlualibs(l);

	printf("now calling lua\n\n");
	luaL_dofile(l, "myscript.lua");
	printf("\ndo something else\n\n");

	lua_close(l);
	return 0;
}

//*/