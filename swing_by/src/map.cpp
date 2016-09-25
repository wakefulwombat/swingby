#include "map.h"
#include "screen.h"
#include "image.h"
#include <fstream>
#include <sstream>

MapChip::MapChip(Point pos, Size size, int chip_index) {
	this->position = pos;
	this->size = size;
	this->chip_index = chip_index;
	this->z_sort = 1000;
	this->expansion = 2.0;
}

void MapChip::update() {
	Screen::addDrawObject(this);
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
	std::vector<std::unique_ptr<MapChip>> tmp;

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
			tmp.push_back(std::unique_ptr<MapChip>(new MapChip(Point(x * 64 + 32, y * 64 + 32), Size(64, 64), std::stoi(cell))));
		}
		this->map_chip.push_back(std::move(tmp));
	}
}