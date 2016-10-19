#pragma once

#include "interface_setScore.h"
#include <memory>

enum class ScoreRank {
	S,
	A,
	B,
	C
};

struct ScoreResult {
public:
	ScoreRank goal_time, max_speed, goal_speed, swing_tech;
};

struct ScoreValue {
public:
	double goal_time;
	double max_speed;
	double goal_speed;
	int swing_tech;
};

class ScoreManager : public ISetScore , public std::enable_shared_from_this<ScoreManager>{
private:
	ScoreValue now;

	ScoreValue S, A, B;

	void loadRankTable(int stage);

public:
	ScoreManager(int stage);

	void setGoalTime(double goal_time) { this->now.goal_time = goal_time; }
	void setNowSpeed(double now_speed) override;
	void setGoalSpeed(double goal_speed) { this->now.goal_speed = goal_speed; }
	void addSwingCount() override { this->now.swing_tech++; }

	ScoreResult getScoreResult();
};