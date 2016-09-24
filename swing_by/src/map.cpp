#include "map.h"
#include "screen.h"

MapChip::MapChip(Point pos, Size size, int chip_index) {
	this->position = pos;
	this->size = size;
	this->chip_index = chip_index;
	this->z_sort = 1000;
}

void MapChip::draw() const {
	//Screen::drawMutable(this->position,this->size,)
}


Map::Map(std::string filename) {

}

void Map::update() {
	for (auto row = this->map_chip.begin(); row != this->map_chip.end();++row) {
		for (auto chip = (*row).begin(); chip != (*row).end(); ++chip) {
			Screen::addDrawObject(&*(*chip));
		}
	}
}