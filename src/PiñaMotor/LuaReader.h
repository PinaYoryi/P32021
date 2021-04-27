#pragma once
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#include <iostream>

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
	bool b = lua_istable(l, 1); // La tabla

	lua_pushnil(l);
	while (lua_next(l, 1) != 0) {
		// Entity is here
		// Name
		lua_getfield(l, -1, "name");
		std::cout << lua_tostring(l, -1) << " ";
		lua_pop(l, 1);

		// ID
		lua_getfield(l, -1, "id");
		std::cout << lua_tonumber(l, -1) << "\n";
		lua_pop(l, 1);

		// Components
		// Calls a similar while loop, creating a map<string, string> with each pair
		// Knows which component is by key name and a traductor function

		// Entity is no longer here, only key to be removed by lua_next
		lua_pop(l, 1);
	}

	printf("\ndo something else\n\n");

	lua_close(l);
}

