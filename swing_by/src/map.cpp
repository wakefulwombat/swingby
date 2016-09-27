#include "map.h"
#include "screen.h"
#include "image.h"
#include <fstream>
#include <sstream>
#include <vector>

MapChip::MapChip(Point pos, Size size, int chip_index) {
	this->position = pos;
	this->size = size;
	this->chip_index = chip_index;
	this->z_sort = 1000;
	this->expansion = 2.0;
}

void MapChip::update() {
	Screen::addDrawObjectMutable(this);
}

void MapChip::draw() const {
	Screen::drawMutable(this->position, this->size, Image::getMapChip(this->chip_index), this->expansion, this->img_rotation, false, this->img_opacity);
}


Map::Map(std::string filename) {
	this->map_size = this->loadMapSize(filename);
	this->start_pos = this->loadMapStartPoint(filename);
	this->loadMapChipData(filename);
}

void Map::update() {
	for (auto row = this->map_chip.begin(); row != this->map_chip.end();++row) {
		for (auto chip = (*row).begin(); chip != (*row).end(); ++chip) {
			(*chip)->update();
		}
	}
}

Size Map::loadMapSize(std::string filename) {
	Size size;

	std::ifstream ifs(filename);
	if (!ifs) return Size(0, 0);

	std::string str;
	std::getline(ifs, str);

	std::string tmp;
	std::istringstream stream(str);
	getline(stream, tmp, ',');
	getline(stream, tmp, ',');
	size.width = std::stoi(tmp);
	getline(stream, tmp, ',');
	size.height = std::stoi(tmp);

	return size;
}

Point Map::loadMapStartPoint(std::string filename) {
	Point pos;

	std::ifstream ifs(filename);
	if (!ifs) return Point(0, 0);

	std::string str;
	std::getline(ifs, str);//1çsñ⁄ÇÕì«Ç›îÚÇŒÇ∑
	std::getline(ifs, str);

	std::string tmp;
	std::istringstream stream(str);
	getline(stream, tmp, ',');
	getline(stream, tmp, ',');
	pos.x = std::stod(tmp);
	getline(stream, tmp, ',');
	pos.y = std::stoi(tmp);

	return pos;
}

void Map::loadMapChipData(std::string filename) {
	this->map_chip.clear();
	std::vector<std::shared_ptr<MapChip>> tmp;

	std::ifstream ifs(filename);
	if (!ifs)return;

	std::string str;
	std::getline(ifs, str);
	std::getline(ifs, str);//2çsì«Ç›îÚÇŒÇ∑
	for (int y = 0; y < this->map_size.height;++y){
		tmp.clear();
		std::getline(ifs, str);
		std::string cell;
		std::istringstream stream(str);
		for (int x = 0; x < this->map_size.width; ++x) {
			getline(stream, cell, ',');
			tmp.push_back(std::shared_ptr<MapChip>(new MapChip(Point(x * 64 + 32, y * 64 + 32), Size(64, 64), std::stoi(cell))));
		}
		this->map_chip.push_back(std::move(tmp));
	}
}

bool Map::isMapChipVisible(int x_index, int y_index) {
	return Screen::isVisible(this->map_chip[y_index][x_index].get());
}

Point Map::getCrossPosition(Point p1, Point p2) {
	double a, b, ang;//y=ax+b
	int map_x, map_y;
	int map_x_inc = (int)((p2.x - p1.x) / abs(p2.x - p1.x)), map_y_inc = (int)((p2.y - p1.y) / abs(p2.y - p1.y));

	for (int i = 0;; ++i) {
		if (p1.x < 64 * (i + 1)) {
			map_x = i;
			break;
		}
	}
	for (int i = 0;; ++i) {
		if (p1.y < 64 * (i + 1)) {
			map_y = i;
			break;
		}
	}

	if (p1.x == p2.x) a = 0.0;
	else a = (p2.y - p1.y) / (p2.x - p1.x);
	b = p1.y - a*p1.x;
	ang = atan2(p2.y - p1.y, p2.x - p1.x);


	std::vector<Point> candidate;
	candidate.clear();
	candidate.push_back(Point(map_x, map_y));
	while (this->isMapChipVisible(map_x, map_y)) {
		while (this->isMapChipVisible(map_x, map_y)) {
			map_x += map_x_inc;
			if (abs(-a*(64.0*map_x+32.0) + (64.0*map_y+32.0) - b) / sqrt(a*a + b*b) < 64.0*sqrt(2.0)) {
				candidate.push_back(Point(map_x, map_y));
			}
			else {
				map_x -= map_x_inc;
				break;
			}
		}
		while (this->isMapChipVisible(map_x, map_y)) {
			map_y += map_y_inc;
			if (abs(-a*(64.0*map_x + 32.0) + (64.0*map_y + 32.0) - b) / sqrt(a*a + b*b) < 64.0*sqrt(2.0)) {
				candidate.push_back(Point(map_x, map_y));
			}
			else {
				map_y -= map_y_inc;
				break;
			}
		}
	}


}