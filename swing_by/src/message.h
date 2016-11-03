#pragma once

#include "common.h"
#include "base_objectBase.h"
#include "image.h"
#include <memory>

class Message : public ObjectBase , public std::enable_shared_from_this<Message>{
private:
	MessageType type;

public:
	Message(Point pos, MessageType type);
	void update() override;
	void draw() const override;
	void addDraw() override;

	void startShowing();
};


class Rank : public ObjectBase, public std::enable_shared_from_this<Rank> {
private:
	ScoreRank type;
	int time;
	double first_expansion, final_expansion;

public:
	Rank(Point pos, ScoreRank type);
	void update() override;
	void draw() const override;
	void addDraw() override;

	void startShowing(double start_exp, double final_exp, int time);
	void changeType(ScoreRank type) { this->type = type; }
};