#include "textBox.h"
#include "screen.h"

TextBox::TextBox(Point center, Size chip_size) {
	this->position = center;
	this->chip_size = chip_size;
	this->size = this->chip_size * 12;
	this->expansion = 1.0;

	this->visible = false;
	this->isAppearing = false;
	this->isHiding = false;
}

void TextBox::update() {
	if (!this->visible) return;

	if (this->isAppearing){
		this->expansion = 1.0*this->count / 60;
		if (this->count == 60) this->isAppearing = false;
	}
	if (this->isHiding){
		this->expansion = 1.0*(60 - this->count) / 60;
		if (this->count == 60) {
			this->isAppearing = false;
			this->visible = false;
		}
	}

	this->addDraw();
}

void TextBox::draw() const {

}

void TextBox::addDraw(){
	Screen::addDrawObjectWindow(this->shared_from_this());
}

void TextBox::show(){
	this->isAppearing = true;
	this->visible = true;

	this->expansion = 0.0;
	this->count = 0;
}

void TextBox::hide(){
	this->isHiding = true;

	this->expansion = 1.0;
	this->count = 0;
}