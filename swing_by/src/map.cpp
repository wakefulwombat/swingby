#include "map.h"
#include "screen.h"
#include "image.h"
#include "debug.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

MapChip::MapChip(Point pos, Size size, int chip_index) {
	this->position = pos;
	this->size = size;
	this->chip_index = chip_index;
	this->z_sort = 1000;
	this->expansion = 2.0;
}

void MapChip::update() {
	Screen::addDrawObjectMutable(this->shared_from_this());
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
			tmp.push_back(std::make_shared<MapChip>(Point(x * 64 + 32, y * 64 + 32), Size(32, 32), std::stoi(cell)));
		}
		this->map_chip.push_back(std::move(tmp));
	}
}

bool Map::isMapChipVisible(int x_index, int y_index) {
	if (x_index < 0) return false;
	if (y_index < 0) return false;
	if (x_index >= this->map_size.width) return false;
	if (y_index >= this->map_size.height) return false;

	return Screen::isVisible(this->map_chip[y_index][x_index]);
}

Point Map::getCrossPosition(Point p1, Point p2) {
	double a, b, ang;//y=ax+b
	if (p1.x == p2.x) a = 0.0;
	else a = (p2.y - p1.y) / (p2.x - p1.x);
	b = p1.y - a*p1.x;
	ang = atan2(p2.y - p1.y, p2.x - p1.x);


	std::vector<Point> candidate;
	candidate.clear();
	Point pos = p1;
	int map_x, map_y;
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
	candidate.push_back(Point(map_x, map_y));

	do {
		pos.x += 2.0*cos(ang);
		pos.y += 2.0*sin(ang);
		int tmp_x, tmp_y;
		for (int i = 0;; ++i) {
			if (pos.x < 64 * (i + 1)) {
				tmp_x = i;
				break;
			}
		}
		for (int i = 0;; ++i) {
			if (pos.y < 64 * (i + 1)) {
				tmp_y = i;
				break;
			}
		}
		if ((tmp_x == map_x)&&(tmp_y == map_y)) continue;

		candidate.push_back(Point(tmp_x, tmp_y));
		map_x = tmp_x;
		map_y = tmp_y;
	} while (this->isMapChipVisible(map_x, map_y));


	Point cross = Point();
	std::vector<Point> tmp;

	for (Point p : candidate) {
		//std::shared_ptr<Debug_Square> dbg = std::make_shared<Debug_Square>(Point(64.0*p.x+32, 64.0*p.y+32), Size(64, 64), Color(255, 0, 0));
		//dbg->update();

		tmp.clear();
		if ((a*(p.x*64.0) + b >= p.y*64.0) && (a*(p.x*64.0) + b <= (p.y + 1.0)*64.0)) tmp.push_back(Point(p.x*64.0, a*(p.x*64.0) + b));
		if ((a*((p.x + 1)*64.0) + b >= p.y*64.0) && (a*((p.x + 1)*64.0) + b <= (p.y + 1.0)*64.0)) tmp.push_back(Point((p.x + 1.0)*64.0, a*(p.x*64.0) + b));
		if (((p.y*64.0 - b) / a >= p.x*64.0) && ((p.y*64.0 - b) / a <= (p.x + 1.0)*64.0)) tmp.push_back(Point((p.y*64.0 - b) / a, p.y*64.0));
		if ((((p.y + 1)*64.0 - b) / a >= p.x*64.0) && (((p.y + 1)*64.0 - b) / a <= (p.x + 1.0)*64.0)) tmp.push_back(Point((p.y*64.0 - b) / a, (p.y + 1.0)*64.0));

		if (tmp.size() != 2) continue;

		if (this->isCross((int)p.x, (int)p.y, tmp[0], tmp[1])) {
			cross = this->getCrossPointInMapChip((int)p.x, (int)p.y, a, b, p1);
			break;
		}
	}

	return cross;
}

bool Map::intersect(Point lp1, Point lp2, Point mp1, Point mp2) {
	double ta = (mp1.x - mp2.x) * (lp1.y - mp1.y) + (mp1.y - mp2.y) * (mp1.x - lp1.x);
	double tb = (mp1.x - mp2.x) * (lp2.y - mp1.y) + (mp1.y - mp2.y) * (mp1.x - lp2.x);
	double tc = (lp1.x - lp2.x) * (mp1.y - lp1.y) + (lp1.y - lp2.y) * (lp1.x - mp1.x);
	double td = (lp1.x - lp2.x) * (mp2.y - lp1.y) + (lp1.y - lp2.y) * (lp1.x - mp2.x);

	return ((tc * td <= 0.0) && (ta * tb <= 0.0));
}

bool Map::isCross(int chip_x, int chip_y, Point p1, Point p2) {
	if (chip_x < 0) return false;
	if (chip_y < 0) return false;
	if (chip_x >= this->map_size.width) return false;
	if (chip_y >= this->map_size.height) return false;

	switch (this->map_chip[chip_y][chip_x]->getChipKindIndex()) {
	case 0:
		return this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, -32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, -32.0));
		break;
	case 1:
		return this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, -32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, 32.0));
		break;
	case 2:
		return this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, 32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, 32.0));
		break;
	case 3:
		return this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, -32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, 32.0));
		break;

	case 4:
	case 6:
		return this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, 32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, -32.0));
		break;
	case 5:
	case 7:
		return this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, -32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, 32.0));
		break;

	case 12:
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, 32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, -32.0))) return true;
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, -32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, -32.0))) return true;
		break;
	case 13:
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, -32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, -32.0))) return true;
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, -32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, 32.0))) return true;
		break;
	case 14:
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, -32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, 32.0))) return true;
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, 32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, 32.0))) return true;
		break;
	case 15:
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, 32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, 32.0))) return true;
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, 32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, -32.0))) return true;
		break;

	case 20:
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, -32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, -32.0))) return true;
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, -32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, 32.0))) return true;
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(32.0, 32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, 32.0))) return true;
		if (this->intersect(p1, p2, this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, 32.0), this->map_chip[chip_y][chip_x]->getPosition() + Point(-32.0, -32.0))) return true;
		break;
	}
	return false;
}

Point Map::getCrossPointInMapChip(int chip_x, int chip_y, double a, double b, Point player) {
	std::vector<Point> list;
	Point pos;
	switch (this->map_chip[chip_y][chip_x]->getChipKindIndex()) {
	case 0:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y - 32.0;
		pos.x = (pos.y - b) / a;
		list.push_back(pos);
		break;
	case 1:
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x + 32.0;
		pos.y = a*pos.x + b;
		list.push_back(pos);
		break;
	case 2:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y + 32.0;
		pos.x = (pos.y - b) / a;
		list.push_back(pos);
		break;
	case 3:
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x - 32.0;
		pos.y = a*pos.x + b;
		list.push_back(pos);
		break;

	case 4:
	case 6:
		pos.x = (b + this->map_chip[chip_y][chip_x]->getPosition().x - this->map_chip[chip_y][chip_x]->getPosition().y) / (1.0 - a);
		pos.y = pos.x - this->map_chip[chip_y][chip_x]->getPosition().x + this->map_chip[chip_y][chip_x]->getPosition().y;
		list.push_back(pos);
		break;
	case 5:
	case 7:
		pos.x = (b + this->map_chip[chip_y][chip_x]->getPosition().x - this->map_chip[chip_y][chip_x]->getPosition().y) / (-1.0 - a);
		pos.y = -pos.x - this->map_chip[chip_y][chip_x]->getPosition().x + this->map_chip[chip_y][chip_x]->getPosition().y;
		list.push_back(pos);
		break;

	case 12:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y - 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 32.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 32.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x - 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 32.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 32.0)) list.push_back(pos);
		break;
	case 13:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y - 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 32.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 32.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x + 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 32.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 32.0)) list.push_back(pos);
		break;
	case 14:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y + 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 32.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 32.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x + 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 32.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 32.0)) list.push_back(pos);
		break;
	case 15:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y + 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 32.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 32.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x - 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 32.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 32.0)) list.push_back(pos);
		break;

	case 20:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y - 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 32.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 32.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x + 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 32.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 32.0)) list.push_back(pos);
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y + 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 32.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 32.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x - 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 32.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 32.0)) list.push_back(pos);
		break;
	}
	
	std::sort(list.begin(), list.end(), [player](Point &left, Point &right) {
		return (left.x - player.x)*(left.x - player.x) + (left.y - player.y)*(left.y - player.y) < (right.x - player.x)*(right.x - player.x) + (right.y - player.y)*(right.y - player.y);
	});
	return list[0];
}