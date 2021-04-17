
//#include <OgreRoot.h>
//#include "Entity.h"
//#include "Transform.h"
//#include "ComponentFactoryRegistration.h"
#include <btBulletDynamicsCommon.h>
//#include "MotorLoop.h"

#include <stdlib.h>
#include <stdio.h>
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#include <string>
#include <iostream>
using namespace std;

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

#if (defined _DEBUG) || !(defined _WIN32) //<-- Ya no lo tenemos en teor�a
int main() {
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
		//Ogre::Root* root;
		//root = new Ogre::Root();
		////TODO: carne de ca�on de macro
	 ////   ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
	 ////   Entity* ent = new Entity();
		//return 0;


	lua_State* l;
	l = luaL_newstate();
	openlualibs(l);

	printf("now calling lua\n\n");
	luaL_loadfile(l, "myscript.lua");
	if (lua_pcall(l, 0, 0, 0)) cout << "No va\n";
	lua_getglobal(l, "GetMapa");
	int err = lua_pcall(l, 0, 1, 0); // GetMapa()
	bool b = lua_istable(l, 1); // La tabla

	lua_pushnil(l);
	while (lua_next(l, 1) != 0) {
		// Entity is here
		// Name
		lua_getfield(l, -1, "name");
		cout << lua_tostring(l, -1) << " ";
		lua_pop(l, 1);

		// ID
		lua_getfield(l, -1, "id");
		cout << lua_tonumber(l, -1) << "\n";
		lua_pop(l, 1);

		// Components
		// Calls a similar while loop, creating a map<string, string> with each pair
		// Knows which component is by key name and a traductor function

		// Entity is no longer here, only key to be removed by lua_next
		lua_pop(l, 1);
	}

	printf("\ndo something else\n\n");

	lua_close(l);
	return 0;
}

