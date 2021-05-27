#pragma once
#include <vector>
#include <string>

class Entity;

Entity* readPrefab(std::string file = "myprefab.prefab");

void readFile(std::string file = "myscript.lua");

std::vector<std::string> readScheme(std::string file = "scheme.cfg");