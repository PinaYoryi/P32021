#pragma once
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#include <iostream>

#include "Entity.h"
#include <map>
#include <string>
#include "SceneManager.h"

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

void readFile(std::string file = "myscript.lua") {
	lua_State* l;
	l = luaL_newstate();
	openlualibs(l);

	printf("now calling lua\n\n");
	luaL_loadfile(l, file.c_str());
	if (lua_pcall(l, 0, 0, 0)) std::cout << "Lua was not able to be loaded\n";
	lua_getglobal(l, "GetMapa");
	int err = lua_pcall(l, 0, 1, 0); // GetMapa()

	lua_pushnil(l);
	while (lua_next(l, 1) != 0) {
		// Entity is here
		// Name
		lua_getfield(l, -1, "name");
		char* name = (char*)lua_tostring(l, -1);
		lua_pop(l, 1);

		// ID
		lua_getfield(l, -1, "id");
		int id = lua_tonumber(l, -1);
		lua_pop(l, 1);

		Entity* ent = new Entity(name, id);
		SceneManager::GetInstance()->addEntity(ent);

		// Components
		// Calls a similar while loop, creating a set<string, string> with each pair
		// Knows which component is by key name and a translator function
		lua_getfield(l, -1, "components");
		lua_pushnil(l);
		while (lua_next(l, 4) != 0) { // stack: mapa-indEntity-Entity-compTabla

			char* compName = (char*)lua_tostring(l, -2);

			std::map<std::string, std::string> compMap;
			lua_pushnil(l);
			while (lua_next(l, 6) != 0) { // stack: mapa-indEntity-Entity-compTabla-indComp-Component
				char* attrName = (char*)lua_tostring(l, -2);
				std::string s1(attrName);
				char* attrValue = (char*)lua_tostring(l, -1);
				std::string s2(attrValue);
				compMap.insert((std::pair<std::string, std::string>(s1, s2)));
				lua_pop(l, 1);
			}

			// Función de traducción
			ent->addComponent(compName, compMap);
			lua_pop(l, 1);
		}
		lua_pop(l, 1);
		// Entity is no longer here, only key to be removed by lua_next
		lua_pop(l, 1);
	}

	printf("\ndo something else\n\n");

	lua_close(l);
}

