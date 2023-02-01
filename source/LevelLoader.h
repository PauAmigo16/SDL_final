#pragma once

#include "../dep/inc/XML/rapidxml.hpp"
#include "../dep/inc/XML/rapidxml_utils.hpp"
#include "../dep/inc/XML/rapidxml_iterators.hpp"
#include "../dep/inc/XML/rapidxml_print.hpp"
#include "Gameplay.h"
#include "Tile.h"
#include "Spawner.h"

#include <vector>
#include <string>
#include <sstream>

class Gameplay;

class LevelLoader {


public:
	LevelLoader();
	static void LoadLevel(std::string path, Gameplay* gamelay);




};
