#include "message.h"
#include "screen.h"

Message::Message(Point pos, MessageType type) {
	this->position = pos;
	this->type = type;
	this->z_sort = 90001;

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
	}
}

void Message::update() {
	this->addDraw();
}

void Message::draw() const {
	Screen::drawOnWindow(this->position, this->size, Image::getMessage(this->type), 1.0, 0.0, 1.0);
}

void Message::addDraw() {
	Screen::addDrawObjectWindow(this->shared_from_this());
}