#include "button.h"
#include "screen.h"
#include "input.h"

/////////////////////////////////////////////////////////////////////////////////////////////
Button::Button(Point center, Size size, std::string text, int font_size, std::function<void(void)> callback_clicked, Color text_color, Color background_color, Color mouseover_color) {
	this->position = center;
	this->size = size;
	this->text = text;
	this->font_size = font_size;
	this->callback_clicked = callback_clicked;
	this->text_color = text_color;
	this->background_color = background_color;
	this->mouseover_color = mouseover_color;

	this->validation = true;
	this->z_sort = 90000;

	this->isClicked = false;
	this->isHovered = false;
}


void Button::update() {
	if (!this->validation) return;

	if (this->isClicked) {
		this->count++;
		if (this->count >= 10) {
			this->count = 0;
			this->callback_clicked();
			this->isClicked = false;
		}
	}

	this->addDraw();
	this->isHovered = false;

	Point mouse = Input::getNowMousePoint();
	if (mouse.x < this->position.x - this->size.width / 2) return;
	if (mouse.y < this->position.y - this->size.height / 2) return;
	if (mouse.x > this->position.x + this->size.width / 2) return;
	if (mouse.y > this->position.y + this->size.height / 2) return;

	this->isHovered = true;

	if (Input::getKeyCodeDownOnce(KeyType::Game_Swing_OK)) {
		this->isClicked = true;
	}
}

void Button::draw() const {
	Color col;
	if (this->isHovered) {
		col = this->mouseover_color;
	}
	else {
		col = this->background_color;
	}
	Screen::drawSquare(Screen::getPositionOfWorldCoordinate(this->position), this->size, col);

	col = this->text_color;
	Screen::drawString(Screen::getPositionOfWorldCoordinate(this->position), col, this->text, this->font_size);
}

void Button::addDraw() {
	Screen::addDrawObjectWindow(this->shared_from_this());
}
/////////////////////////////////////////////////////////////////////////////////////////////

ButtonMove::ButtonMove(Point center, Size size, std::string text, int font_size, std::function<void(void)> callback_clicked, Color text_color, Color background_color_off, Color background_color_on, Color mouseover_color) : Button(center, size, text, font_size, callback_clicked, text_color, background_color_off, mouseover_color) {
	this->background_color_on = background_color_on;

	this->validation = true;
	this->z_sort = 90000;
	this->isOn = false;

	this->isClicked = false;
	this->isHovered = false;
}

void ButtonMove::update() {
	if (!this->validation) return;

	if (this->isClicked) {
		this->callback_clicked();
		this->isClicked = false;
		this->isOn = true;
	}

	this->addDraw();
	this->isHovered = false;

	Point mouse = Screen::getPositionOfWorldCoordinate(Input::getNowMousePoint());
	if (mouse.x < this->position.x - this->size.width / 2) return;
	if (mouse.y < this->position.y - this->size.height / 2) return;
	if (mouse.x > this->position.x + this->size.width / 2) return;
	if (mouse.y > this->position.y + this->size.height / 2) return;

	this->isHovered = true;

	if (Input::getKeyCodeDownOnce(KeyType::Game_Swing_OK)) {
		this->isClicked = true;
	}
}

void ButtonMove::addDraw() {
	Screen::addDrawObjectMutable(this->shared_from_this()); 
}

void ButtonMove::draw() const {
	Color col;

	if (this->isOn) {
		col = this->background_color_on;
	}
	else {
		if (this->isHovered) {
			col = this->mouseover_color;
		}
		else {
			col = this->background_color;
		}
	}
	Screen::drawSquare(this->position, this->size, col);

	col = this->text_color;
	Screen::drawString(this->position, col, this->text, this->font_size);
}

/////////////////////////////////////////////////////////////////////////////////////////////
void ButtonManager::setNewButton(Point center, Size size, std::string text, int font_size, std::function<void(void)> clicked, Color text_color, Color background_color, Color mouseover_color) {
	this->obj_list.push_back(std::make_shared<Button>(center, size, text, font_size, clicked, text_color, background_color, mouseover_color));
}
/////////////////////////////////////////////////////////////////////////////////////////////