#pragma once

#include "interface_setScore.h"

struct Score {
public:
	double goal_time;
	double max_speed;
	double goal_speed;
	int swing_tech;
};

class ScoreManager : public ISetScore {
private:
	Score now;
	Score high_score;

	Score S, A, B;

	void loadStageHighScore(int stage);
	void loadRankTable(int stage);

public:
	ScoreManager(int stage);

	void setGoalTime(double goal_time) override { this->now.goal_time = goal_time; }
	void setNowSpeed(double now_speed) override;
	void setGoalSpeed(double goal_speed) override { this->now.goal_speed = goal_speed; }
	void addSwingCound() override { this->now.swing_tech++; }
};