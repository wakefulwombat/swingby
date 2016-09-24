#pragma once

#include "base_requiredFunc.h"
#include "base_objectBase.h"
#include <vector>
#include <memory>
#include <string>

class MapChip : public ObjectBase {
private:
	int chip_index;
public:
	MapChip(Point pos, Size size, int chip_index);
	void update() override;
	void draw() const override;
};

class Map : public RequiredFunc{
private:
	Size map_size;
	Point start_pos;
	std::vector<std::vector<std::unique_ptr<MapChip>>> map_chip;//[y][x]

public:
	Map(std::string filename);
	void update() override;
};