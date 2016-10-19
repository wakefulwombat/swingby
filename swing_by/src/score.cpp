#include "score.h"
#include "common.h"
#include <fstream>
#include <sstream>

ScoreManager::ScoreManager(int stage) {
	this->loadRankTable(stage);

	this->now.swing_tech = 0;
}

void ScoreManager::loadRankTable(int stage) {
	std::ifstream ifs("asset\\score_eval.csv");
	if (!ifs) return;

	std::string str;
	for (int i = 0; i < stage + 2; ++i) std::getline(ifs, str);

	std::string tmp;
	std::istringstream stream(str);

	getline(stream, tmp, ',');
	getline(stream, tmp, ',');
	this->S.goal_time = std::stod(tmp);
	getline(stream, tmp, ',');
	this->A.goal_time = std::stod(tmp);
	getline(stream, tmp, ',');
	this->B.goal_time = std::stod(tmp);

	getline(stream, tmp, ',');
	this->S.max_speed = std::stod(tmp);
	getline(stream, tmp, ',');
	this->A.max_speed = std::stod(tmp);
	getline(stream, tmp, ',');
	this->B.max_speed = std::stod(tmp);

	getline(stream, tmp, ',');
	this->S.goal_speed = std::stod(tmp);
	getline(stream, tmp, ',');
	this->A.goal_speed = std::stod(tmp);
	getline(stream, tmp, ',');
	this->B.goal_speed = std::stod(tmp);

	getline(stream, tmp, ',');
	this->S.swing_tech = std::stoi(tmp);
	getline(stream, tmp, ',');
	this->A.swing_tech = std::stoi(tmp);
	getline(stream, tmp, ',');
	this->B.swing_tech = std::stoi(tmp);
}


void ScoreManager::setNowSpeed(double now_speed) {
	if (now_speed > this->now.max_speed) {
		this->now.max_speed = now_speed;
	}
}

ScoreResult ScoreManager::getScoreResult() {
	ScoreResult sr;

	if (this->now.goal_speed >= this->S.goal_speed) sr.goal_speed = ScoreRank::S;
	else if(this->now.goal_speed >= this->A.goal_speed) sr.goal_speed = ScoreRank::A;
	else if (this->now.goal_speed >= this->B.goal_speed) sr.goal_speed = ScoreRank::B;
	else sr.goal_speed = ScoreRank::C;

	if (this->now.goal_time <= this->S.goal_time) sr.goal_time = ScoreRank::S;
	else if (this->now.goal_time <= this->A.goal_time) sr.goal_time = ScoreRank::A;
	else if (this->now.goal_time <= this->B.goal_time) sr.goal_time = ScoreRank::B;
	else sr.goal_time = ScoreRank::C;

	if (this->now.max_speed >= this->S.max_speed) sr.max_speed = ScoreRank::S;
	else if (this->now.max_speed >= this->A.max_speed) sr.max_speed = ScoreRank::A;
	else if (this->now.max_speed >= this->B.max_speed) sr.max_speed = ScoreRank::B;
	else sr.max_speed = ScoreRank::C;

	if (this->now.swing_tech >= this->S.swing_tech) sr.swing_tech = ScoreRank::S;
	else if (this->now.swing_tech >= this->A.swing_tech) sr.swing_tech = ScoreRank::A;
	else if (this->now.swing_tech >= this->B.swing_tech) sr.swing_tech = ScoreRank::B;
	else sr.swing_tech = ScoreRank::C;

	return sr;
}