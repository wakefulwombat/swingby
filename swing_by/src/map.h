#pragma once

#include "base_requiredFunc.h"
#include "base_objectBase.h"
#include "interface_getMapCrossPosition.h"
#include "screen.h"
#include <vector>
#include <memory>
#include <string>

class MapChip : public ObjectBase, public std::enable_shared_from_this<MapChip> {
private:
	int chip_index;
public:
	MapChip(Point pos, Size size, int chip_index);
	void update() override;
	void draw() const override;
	void addDraw() override { Screen::addDrawObjectMutable(this->shared_from_this()); }

	int getChipKindIndex() { return this->chip_index; }
};

class Map : public RequiredFunc, public IGetMapCrossPosition{
private:
	Size map_size;
	Point start_pos;
	Point goal_leftup_pos, goal_rightdown_pos;
	std::vector<std::vector<std::shared_ptr<MapChip>>> map_chip;//[y][x]

	void loadMapSize(std::string filename);
	void loadMapStartPoint(std::string filename);
	void loadMapGoalArea(std::string filename);
	void loadMapChipData(std::string filename);
	
	std::string transformStageToFilename(int stage);

	std::vector<Point> getCrossPointsInMapChip(int chip_x, int chip_y, double a, double b);

public:
	Map(int stage);
	void update() override;

	Point getStartPosition() { return this->start_pos * 64 + Point(32, 32); }
	Size getStageSize() { return this->map_size * 64; }

	bool isMapChipVisible(int x_index, int y_index);
	Point getMapCrossPosition(Point line_p1, Point line_p2) override;

	bool isHitWithWall(const std::shared_ptr<ObjectBase> &obj, double r);
	bool isInGoalArea(const std::shared_ptr<ObjectBase> &obj);

	void addDraw();
};