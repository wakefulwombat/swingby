#include "map.h"
#include "image.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

MapChip::MapChip(Point pos, Size size, int chip_index) {
	this->position = pos;
	this->size = size;
	this->chip_index = chip_index;
	this->z_sort = 10;
	this->expansion = 2.0;
}

void MapChip::update() {
	this->addDraw();
}

void MapChip::draw() const {
	Screen::drawMutable(this->position, this->size, Image::getMapChip(this->chip_index), this->expansion, this->img_rotation, false, this->img_opacity);
}


Map::Map(int stage) {
	std::string filename = this->transformStageToFilename(stage);
	this->loadMapSize(filename);
	this->loadMapStartPoint(filename);
	this->loadMapGoalArea(filename);
	this->loadMapChipData(filename);
}

void Map::update() {
	this->addDraw();
}

void Map::loadMapSize(std::string filename) {
	std::ifstream ifs(filename);
	if (!ifs) return;

	std::string str;
	std::getline(ifs, str);

	std::string tmp;
	std::istringstream stream(str);
	getline(stream, tmp, ',');
	getline(stream, tmp, ',');
	this->map_size.width = std::stoi(tmp);
	getline(stream, tmp, ',');
	this->map_size.height = std::stoi(tmp);
}

void Map::loadMapStartPoint(std::string filename) {
	std::ifstream ifs(filename);
	if (!ifs) return;
	std::string str;
	std::getline(ifs, str);//1çsñ⁄ÇÕì«Ç›îÚÇŒÇ∑
	std::getline(ifs, str);

	std::string tmp;
	std::istringstream stream(str);
	getline(stream, tmp, ',');
	getline(stream, tmp, ',');
	this->start_pos.x = std::stod(tmp);
	getline(stream, tmp, ',');
	this->start_pos.y = std::stoi(tmp);
}

void Map::loadMapGoalArea(std::string filename) {
	std::ifstream ifs(filename);
	if (!ifs) return;
	std::string str;
	std::getline(ifs, str);
	std::getline(ifs, str);//2çsì«Ç›îÚÇŒÇ∑

	std::getline(ifs, str);
	std::string tmp;
	std::istringstream stream(str);
	getline(stream, tmp, ',');
	getline(stream, tmp, ',');
	this->goal_leftup_pos.x = std::stod(tmp);
	getline(stream, tmp, ',');
	this->goal_leftup_pos.y = std::stoi(tmp);
	getline(stream, tmp, ',');
	this->goal_rightdown_pos.x = std::stod(tmp);
	getline(stream, tmp, ',');
	this->goal_rightdown_pos.y = std::stoi(tmp);
}

void Map::loadMapChipData(std::string filename) {
	this->map_chip.clear();
	std::vector<std::shared_ptr<MapChip>> tmp;

	std::ifstream ifs(filename);
	if (!ifs)return;

	std::string str;
	std::getline(ifs, str);
	std::getline(ifs, str);
	std::getline(ifs, str);//3çsì«Ç›îÚÇŒÇ∑

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

std::string Map::transformStageToFilename(int stage) {
	std::string s;
	switch (stage) {
	case 0:
		s = "asset\\map\\map_001.csv";
		break;

	case 1:
		s = "asset\\map\\map_002.csv";
		break;

	case 2:
		s = "asset\\map\\map_003.csv";
		break;
	}

	return s;
}

bool Map::isMapChipVisible(int x_index, int y_index) {
	if (x_index < 0) return false;
	if (y_index < 0) return false;
	if (x_index >= this->map_size.width) return false;
	if (y_index >= this->map_size.height) return false;

	return Screen::isVisible(this->map_chip[y_index][x_index]);
}

Point Map::getMapCrossPosition(Point p1, Point p2) {
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


	std::vector<Point> cross;
	cross.clear();
	std::vector<Point> tmp;

	for (Point p : candidate) {
		if ((int)p.x >= this->map_size.width) continue;
		if ((int)p.y >= this->map_size.height) continue;
		tmp.clear();
		
		if ((a*(p.x*64.0) + b >= p.y*64.0) && (a*(p.x*64.0) + b <= (p.y + 1.0)*64.0)) tmp.push_back(Point(p.x*64.0, a*(p.x*64.0) + b));
		if ((a*((p.x + 1)*64.0) + b >= p.y*64.0) && (a*((p.x + 1)*64.0) + b <= (p.y + 1.0)*64.0)) tmp.push_back(Point((p.x + 1.0)*64.0, a*((p.x + 1.0)*64.0) + b));
		if (((p.y*64.0 - b) / a >= p.x*64.0) && ((p.y*64.0 - b) / a <= (p.x + 1.0)*64.0)) tmp.push_back(Point((p.y*64.0 - b) / a, p.y*64.0));
		if ((((p.y + 1)*64.0 - b) / a >= p.x*64.0) && (((p.y + 1)*64.0 - b) / a <= (p.x + 1.0)*64.0)) tmp.push_back(Point(((p.y + 1.0)*64.0 - b) / a, (p.y + 1.0)*64.0));

		if (tmp.size() != 2) continue;
		
		for (Point c : this->getCrossPointsInMapChip((int)p.x, (int)p.y, a, b)) {
			cross.push_back(c);
		}
		
	}

	std::sort(cross.begin(), cross.end(), [p1](Point &left, Point &right) {
		return (left.x - p1.x)*(left.x - p1.x) + (left.y - p1.y)*(left.y - p1.y) < (right.x - p1.x)*(right.x - p1.x) + (right.y - p1.y)*(right.y - p1.y);
	});
	
	if (cross.size() == 0) return Point();
	return cross[0];
}

std::vector<Point> Map::getCrossPointsInMapChip(int chip_x, int chip_y, double a, double b) {
	std::vector<Point> list;
	Point pos;
	switch (this->map_chip[chip_y][chip_x]->getChipKindIndex()) {
	case 0:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y - 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 33.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 33.0)) list.push_back(pos);
		break;
	case 1:
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x + 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 33.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 33.0)) list.push_back(pos);
		break;
	case 2:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y + 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 33.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 33.0)) list.push_back(pos);
		break;
	case 3:
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x - 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 33.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 33.0)) list.push_back(pos);
		break;


	case 4:
	case 6:
		pos.x = (this->map_chip[chip_y][chip_x]->getPosition().x + this->map_chip[chip_y][chip_x]->getPosition().y - b) / (1.0 + a);
		if ((pos.x < this->map_chip[chip_y][chip_x]->getPosition().x - 32.0) || (pos.x > this->map_chip[chip_y][chip_x]->getPosition().x + 32.0)) break;
		pos.y = a*pos.x + b;
		if ((pos.y < this->map_chip[chip_y][chip_x]->getPosition().y - 32.0) || (pos.y > this->map_chip[chip_y][chip_x]->getPosition().y + 32.0)) break;
		list.push_back(pos);
		break;

	case 5:
	case 7:
		pos.x = (this->map_chip[chip_y][chip_x]->getPosition().x - this->map_chip[chip_y][chip_x]->getPosition().y + b) / (1.0 - a);
		if ((pos.x < this->map_chip[chip_y][chip_x]->getPosition().x - 32.0) || (pos.x > this->map_chip[chip_y][chip_x]->getPosition().x + 32.0)) break;
		pos.y = a*pos.x + b;
		if ((pos.y < this->map_chip[chip_y][chip_x]->getPosition().y - 32.0) || (pos.y > this->map_chip[chip_y][chip_x]->getPosition().y + 32.0)) break;
		list.push_back(pos);
		break;
	

	case 12:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y - 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 33.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 33.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x - 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 33.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 33.0)) list.push_back(pos);
		break;
	case 13:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y - 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 33.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 33.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x + 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 33.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 33.0)) list.push_back(pos);
		break;
	case 14:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y + 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 33.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 33.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x + 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 33.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 33.0)) list.push_back(pos);
		break;
	case 15:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y + 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 33.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 33.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x - 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 33.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 33.0)) list.push_back(pos);
		break;

	case 20:
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y - 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 33.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 33.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x + 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 33.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 33.0)) list.push_back(pos);
		pos.y = this->map_chip[chip_y][chip_x]->getPosition().y + 32.0;
		pos.x = (pos.y - b) / a;
		if ((pos.x >= this->map_chip[chip_y][chip_x]->getPosition().x - 33.0) && (pos.x <= this->map_chip[chip_y][chip_x]->getPosition().x + 33.0)) list.push_back(pos);
		pos.x = this->map_chip[chip_y][chip_x]->getPosition().x - 32.0;
		pos.y = a*pos.x + b;
		if ((pos.y >= this->map_chip[chip_y][chip_x]->getPosition().y - 33.0) && (pos.y <= this->map_chip[chip_y][chip_x]->getPosition().y + 33.0)) list.push_back(pos);
		break;
	}
	
	return list;
}

bool Map::isHitWithWall(const std::shared_ptr<ObjectBase> &obj, double r) {
	if (obj->getPosition().x < -obj->getSize().width) return true;

	std::vector<Point> candidate;
	candidate.clear();

	int map_x, map_y;
	for (int i = 0;; ++i) {
		if (obj->getPosition().x < 64 * (i + 1)) {
			map_x = i;
			break;
		}
	}
	for (int i = 0;; ++i) {
		if (obj->getPosition().y < 64 * (i + 1)) {
			map_y = i;
			break;
		}
	}

	int c = (int)r / 64 + 1;

	for (int x = -c; x <= c; ++x) {
		for (int y = -c; y <= c; ++y) {
			candidate.push_back(Point(map_x + x, map_y + y));
		}
	}

	for each (Point p in candidate)
	{
		if ((int)p.x < 0) continue;
		if ((int)p.y < 0) continue;
		if ((int)p.x >= this->map_size.width) continue;
		if ((int)p.y >= this->map_size.height) continue;

		switch (this->map_chip[(int)p.y][(int)p.x]->getChipKindIndex())
		{
		case 0:
			if (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().y - 32.0 - obj->getPosition().y) < r) return true;
			break;
		case 1:
			if (abs(obj->getPosition().x - (this->map_chip[(int)p.y][(int)p.x]->getPosition().x + 32.0)) < r) return true;
			break;
		case 2:
			if (abs(obj->getPosition().y - (this->map_chip[(int)p.y][(int)p.x]->getPosition().y + 32.0)) < r) return true;
			break;
		case 3:
			if (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().x - 32.0 - obj->getPosition().x) < r) return true;
			break;

		case 4:
		case 6:
			if (abs(obj->getPosition().x - this->map_chip[(int)p.y][(int)p.x]->getPosition().x) > 32) continue;
			if (abs(obj->getPosition().x + obj->getPosition().y - this->map_chip[(int)p.y][(int)p.x]->getPosition().x - this->map_chip[(int)p.y][(int)p.x]->getPosition().y) / sqrt(2) < r) return true;
			break;
		case 5:
		case 7:
			if (abs(obj->getPosition().x - this->map_chip[(int)p.y][(int)p.x]->getPosition().x) > 32) continue;
			if (abs(obj->getPosition().y - obj->getPosition().x - this->map_chip[(int)p.y][(int)p.x]->getPosition().y + this->map_chip[(int)p.y][(int)p.x]->getPosition().x) / sqrt(2) < r) return true;
			break;

		case 12:
			if ((abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().y - 32.0 - obj->getPosition().y) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().x - obj->getPosition().x) < 16.0)) return true;
			if ((abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().x - 32.0 - obj->getPosition().x) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().y - obj->getPosition().y) < 16.0)) return true;
			break;
		case 13:
			if ((abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().y - 32.0 - obj->getPosition().y) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().x - obj->getPosition().x) < 16.0)) return true;
			if ((abs(obj->getPosition().x - (this->map_chip[(int)p.y][(int)p.x]->getPosition().x + 32.0)) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().y - obj->getPosition().y) < 16.0)) return true;
			break;
		case 14:
			if ((abs(obj->getPosition().x - (this->map_chip[(int)p.y][(int)p.x]->getPosition().x + 32.0)) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().y - obj->getPosition().y) < 16.0)) return true;
			if ((abs(obj->getPosition().y - (this->map_chip[(int)p.y][(int)p.x]->getPosition().y + 32.0)) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().x - obj->getPosition().x) < 16.0)) return true;
			break;
		case 15:
			if ((abs(obj->getPosition().y - (this->map_chip[(int)p.y][(int)p.x]->getPosition().y + 32.0)) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().x - obj->getPosition().x) < 16.0)) return true;
			if ((abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().x - 32.0 - obj->getPosition().x) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().y - obj->getPosition().y) < 16.0)) return true;
			break;

		case 20:
			if ((abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().y - 32.0 - obj->getPosition().y) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().x - obj->getPosition().x) < 16.0)) return true;
			if ((abs(obj->getPosition().x - (this->map_chip[(int)p.y][(int)p.x]->getPosition().x + 32.0)) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().y - obj->getPosition().y) < 16.0)) return true;
			if ((abs(obj->getPosition().y - (this->map_chip[(int)p.y][(int)p.x]->getPosition().y + 32.0)) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().x - obj->getPosition().x) < 16.0)) return true;
			if ((abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().x - 32.0 - obj->getPosition().x) < r) && (abs(this->map_chip[(int)p.y][(int)p.x]->getPosition().y - obj->getPosition().y) < 16.0)) return true;
			break;
		}
	}

	return false;
}

bool Map::isInGoalArea(const std::shared_ptr<ObjectBase> &obj) {
	if (obj->getPosition().x - obj->getSize().width / 2 < this->goal_leftup_pos.x*64.0 - 32.0) return false;
	if (obj->getPosition().y - obj->getSize().height / 2 < this->goal_leftup_pos.y*64.0 - 32.0) return false;
	if (obj->getPosition().x + obj->getSize().width / 2 > this->goal_rightdown_pos.x*64.0 + 32.0) return false;
	if (obj->getPosition().y - obj->getSize().height / 2 > this->goal_rightdown_pos.y*64.0 + 32.0) return false;

	return true;
}

void Map::addDraw() {
	for (auto row = this->map_chip.begin(); row != this->map_chip.end(); ++row) {
		for (auto chip = (*row).begin(); chip != (*row).end(); ++chip) {
			(*chip)->addDraw();
		}
	}
}