#include "button.h"
#include "screen.h"

/////////////////////////////////////////////////////////////////////////////////////////////
Button::Button(Point center, Size size, std::string text, std::function<void(void)> callback_clicked, Color text_color, Color background_color, Color mouseover_color) {
	this->position = center;
	this->size = size;
	this->text = text;
	this->callback_clicked = callback_clicked;
	this->text_color = text_color;
	this->background_color = background_color;
	this->mouseover_color = mouseover_color;

	this->validation = true;
	this->z_sort = 90000;
}


void Button::update() {
	if (this->isClicked) {
		this->count++;
		if (this->count >= 10) this->clicked();
	}

	this->addDraw();
}

void Button::draw() const {

}

void Button::addDraw() {
	Screen::addDrawObjectWindow(this->shared_from_this());
}
/////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////