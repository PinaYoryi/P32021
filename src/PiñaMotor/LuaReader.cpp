#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#include <iostream>
#include <map>
#include <string>
#include "LuaReader.h"
#include "SceneManager.h"
#include "Entity.h"
#include "OgreMotor.h"
#include "BulletInstance.h"
#include "Gui.h"

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

Entity* readPrefab(std::string file) {
	lua_State* l;
	l = luaL_newstate();
	openlualibs(l);
#if _DEBUG
	std::printf("now calling lua\n\n");
#endif
	if (!luaL_loadfile(l, file.c_str()) && lua_pcall(l, 0, 0, 0)) {
		throw std::exception("Lua file was not able to be loaded");
	}
	try {
		lua_getglobal(l, "GetPrefab");
		int err = lua_pcall(l, 0, 1, 0); // GetPrefab()

		// Entity is here
		// Name
		lua_getfield(l, -1, "name");
		char* name = (char*)lua_tostring(l, -1);
		lua_pop(l, 1);

		// ID
		lua_getfield(l, -1, "id");
		int id = lua_tonumber(l, -1);
		lua_pop(l, 1);

		// showCursor
		lua_getfield(l, -1, "cursor");
		int cursor = lua_tonumber(l, -1);
		lua_pop(l, 1);
		Gui::GetInstance()->setMouseVisibility(cursor);

		Entity* ent = new Entity(name, id);
		SceneManager::GetInstance()->addEntity(ent);

		// Components
		// Calls a similar while loop, creating a set<string, string> with each pair
		// Knows which component is by key name and a translator function
		lua_getfield(l, -1, "components");
		lua_pushnil(l);
		while (lua_next(l, 2) != 0) { // stack: Entity-compTabla

			char* compName = (char*)lua_tostring(l, -2);

			std::map<std::string, std::string> compMap;
			lua_pushnil(l);
			while (lua_next(l, 4) != 0) { // stack: Entity-compTabla-indComp-Component
				char* attrName = (char*)lua_tostring(l, -2);
				std::string s1(attrName);
				char* attrValue = (char*)lua_tostring(l, -1);
				std::string s2(attrValue);
				compMap.insert((std::pair<std::string, std::string>(s1, s2)));
				lua_pop(l, 1);
			}

			// Funcion de traduccion
			ent->addComponent(compName, compMap);
			lua_pop(l, 1);
		}

		ent->init();

		lua_pop(l, 1);
		// Entity is no longer here, only key to be removed by lua_next
		return ent;
	}
	catch (...) {
		throw std::exception("Prefab file has incorrect formatting");
	}
}

void readFile(std::string file) {

	std::vector<Entity*> ents;
	std::vector<bool> entInits;

	lua_State* l;
	l = luaL_newstate();
	openlualibs(l);
#if _DEBUG
	std::printf("now calling lua\n\n");
#endif
	if (!luaL_loadfile(l, file.c_str()) && lua_pcall(l, 0, 0, 0)) {
		throw std::exception("Lua file was not able to be loaded");
	}

	try {
		lua_getglobal(l, "GetMapa");
		int err = lua_pcall(l, 0, 1, 0); // GetMapa()

		lua_getfield(l, -1, "ambient");
		std::string s = lua_tostring(l, -1);
		std::string::size_type sz = 0, sa = 0;
		float a = std::stof(s, &sz), b = std::stof(s.substr(sz + 1), &sa), c = std::stof(s.substr(sz + sa + 2));
		OgreMotor::GetInstance()->getSceneManager()->setAmbientLight(Ogre::ColourValue(a, b, c));
		lua_pop(l, 1);

		lua_getfield(l, -1, "gravity");
		s = lua_tostring(l, -1);
		BulletInstance::GetInstance()->getWorld()->setGravity({ std::stof(s, &sz), std::stof(s.substr(sz + 1), &sa), std::stof(s.substr(sz + sa + 2)) });
		lua_pop(l, 1);

		lua_getfield(l, -1, "entities");
		lua_pushnil(l);
		while (lua_next(l, 2) != 0) {
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
			ents.push_back(ent);
			entInits.push_back(false);
			SceneManager::GetInstance()->addEntity(ent);

			// Components
			// Calls a similar while loop, creating a set<string, string> with each pair
			// Knows which component is by key name and a translator function
			lua_getfield(l, -1, "components");
			lua_pushnil(l);
			while (lua_next(l, 5) != 0) { // stack: mapa-entities-indEntity-Entity-compTabla

				char* compName = (char*)lua_tostring(l, -2);

				std::map<std::string, std::string> compMap;
				lua_pushnil(l);
				while (lua_next(l, 7) != 0) { // stack: mapa-entities-indEntity-Entity-compTabla-indComp-Component
					char* attrName = (char*)lua_tostring(l, -2);
					std::string s1(attrName);
					char* attrValue = (char*)lua_tostring(l, -1);
					std::string s2(attrValue);
					compMap.insert((std::pair<std::string, std::string>(s1, s2)));
					lua_pop(l, 1);
				}

				// Funcion de traduccion
				ent->addComponent(compName, compMap);
				lua_pop(l, 1);
			}

			lua_pop(l, 1);
			// Entity is no longer here, only key to be removed by lua_next
			lua_pop(l, 1);
		}

		lua_pop(l, 2);
#if _DEBUG
		std::printf("\ndo something else\n\n");
#endif
		lua_close(l);

		int i = 0;
		int numEnts = ents.size();
		int initedEnts = 0;
		while (initedEnts != numEnts) {
			if (!entInits[i] && ents[i]->init()) {
				++initedEnts;
				entInits[i] = true;
				SceneManager::GetInstance()->addEntity(ents[i]);
			}
			++i;
			i %= numEnts;
		}
	}
	catch (...) {
		throw std::exception("Lua file has incorrect formatting");
	}
}

std::vector<std::string> readScheme(std::string file) {
	lua_State* l;
	l = luaL_newstate();
	openlualibs(l);
	
	if (!luaL_loadfile(l, file.c_str()) && lua_pcall(l, 0, 0, 0)) {
		throw std::exception("Lua file was not able to be loaded");
	}

	std::vector<std::string> values;
	lua_getglobal(l, "loadScheme");
	lua_pcall(l, 0, 1, 0);
	lua_getfield(l, -1, "scheme");
	values.push_back(lua_tostring(l, -1));
	lua_pop(l, 1);
	lua_getfield(l, -1, "showMouse");
	values.push_back(lua_tostring(l, -1));
	lua_pop(l, 1);
	lua_getfield(l, -1, "mouse");
	values.push_back(lua_tostring(l, -1));
	lua_pop(l, 1);
	lua_getfield(l, -1, "text");
	values.push_back(lua_tostring(l, -1));
	lua_pop(l, 1);
	lua_getfield(l, -1, "image");
	values.push_back(lua_tostring(l, -1));
	lua_pop(l, 1);
	lua_getfield(l, -1, "button");
	values.push_back(lua_tostring(l, -1));
	lua_pop(l, 2);

	return values;
}