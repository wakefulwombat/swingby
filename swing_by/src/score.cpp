#include "score.h"

ScoreManager::ScoreManager(int stage) {
	this->loadStageHighScore(stage);
	this->loadRankTable(stage);

	this->now.swing_tech = 0;
}

void ScoreManager::loadStageHighScore(int stage) {

}

void ScoreManager::loadRankTable(int stage) {

}


void ScoreManager::setNowSpeed(double now_speed) {
	if (now_speed > this->now.max_speed) {
		this->now.max_speed = now_speed;
	}
}