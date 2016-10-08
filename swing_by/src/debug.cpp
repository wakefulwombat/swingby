#include "debug.h"
#include "screen.h"

Debug_Square::Debug_Square(Point center, Size size, Color color)
{
	this->position = center;
	this->size = size;
	this->expansion = 1.0;
	this->col = color;

	this->z_sort = 200000;
}

void Debug_Square::update() {
	Screen::addDrawObjectMutable(this->shared_from_this());
}

void Debug_Square::draw() const {
	Screen::drawSquare(this->position, this->size, this->col);
}



Debug_Line::Debug_Line(Point start, Point end, Color col)
{
	this->position = start;
	this->end = end;
	this->expansion = 1.0;
	this->col = col;

	this->z_sort = 200001;
}

void Debug_Line::update() {
	Screen::addDrawObjectMutable(this->shared_from_this());
}

void Debug_Line::draw() const {
	Screen::drawLine(this->position, this->end, this->col);
}