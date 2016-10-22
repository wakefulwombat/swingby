#include "message.h"
#include "screen.h"

Message::Message(Point pos, MessageType type) {
	this->position = pos;
	this->type = type;
	this->z_sort = 90001;
	this->expansion = 1.0;
	this->img_opacity = 1.0;
	this->count = 100;

	switch (type) {
	case MessageType::PAUSE:
		this->size = Size(402, 126);
		break;

	case MessageType::GAMEOVER:
		this->size = Size(730, 119);
		break;

	case MessageType::STAGECLEAR:
		this->size = Size(943, 128);
		break;

	case MessageType::RESULT:
		this->size = Size(480, 119);
		this->expansion = 0.5;
		break;
	}
}

void Message::update() {
	if (!this->validation) return;

	this->count++;
	this->img_opacity = 1.0*this->count / 120;
	if (this->img_opacity > 1.0) this->img_opacity = 1.0;

	this->addDraw();
}

void Message::draw() const {
	Screen::drawOnWindow(this->position, this->size, Image::getMessage(this->type), this->expansion, 0.0, this->img_opacity);
}

void Message::addDraw() {
	Screen::addDrawObjectWindow(this->shared_from_this());
}

void Message::startShowing() {
	this->img_opacity = 0.0;
	this->count = 0;
	this->validation = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////

Rank::Rank(Point pos, ScoreRank type) {
	this->position = pos;
	this->type = type;
	this->z_sort = 90001;
	this->expansion = 1.0;
	this->img_opacity = 1.0;
	this->count = 100;

	switch (type) {
	case ScoreRank::S:
		this->size = Size(165, 150);
		break;

	case ScoreRank::A:
		this->size = Size(250, 150);
		break;

	case ScoreRank::B:
		this->size = Size(240, 150);
		break;

	case ScoreRank::C:
		this->size = Size(170, 150);
		break;
	}
}

void Rank::update() {
	if (!this->validation) return;

	if (this->count <= this->time) {
		this->count++;
		this->expansion = this->first_expansion + (this->final_expansion - this->first_expansion)*this->count / this->time;
	}

	this->addDraw();
}

void Rank::draw() const {
	Screen::drawOnWindow(this->position, this->size, Image::getRank(this->type), this->expansion, 0.0, this->img_opacity);
}

void Rank::addDraw() {
	Screen::addDrawObjectWindow(this->shared_from_this());
}

void Rank::startShowing(double start_exp, double final_exp, int time) {
	this->first_expansion = start_exp;
	this->final_expansion = final_exp;
	this->count = 0;
	this->time = time;
	this->validation = true;
}