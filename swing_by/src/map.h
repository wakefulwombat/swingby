#pragma once

#include "mapchip.h"
#include "base_requiredFunc.h"
#include <vector>
#include <memory>

class Map : public RequiredFunc{
private:
	std::vector<std::vector<std::unique_ptr<MapChip>>> map_chip;

public:

};