#pragma once

#include "base_requiredFunc.h"
#include "base_objectBase.h"
#include "interface_getCrossPosition.h"
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

	int getChipKindIndex() { return this->chip_index; }
};

class Map : public RequiredFunc, public IGetCrossPosition{
private:
	Size map_size;
	Point start_pos;
	std::vector<std::vector<std::shared_ptr<MapChip>>> map_chip;//[y][x]

	Size loadMapSize(std::string filename);
	Point loadMapStartPoint(std::string filename);
	void loadMapChipData(std::string filename);
	
	std::vector<Point> getCrossPointsInMapChip(int chip_x, int chip_y, double a, double b);

public:
	Map(std::string filename);
	void update() override;

	Point getStartPosition() { return this->start_pos * 64 + Point(32, 32); }
	Size getStageSize() { return this->map_size * 64; }

	bool isMapChipVisible(int x_index, int y_index);
	Point getCrossPosition(Point line_p1, Point line_p2) override;
};