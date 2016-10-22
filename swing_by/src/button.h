#pragma once

#include "common.h"
#include "base_objectBase.h"
#include "base_objectManagerBase.h"
#include <string>
#include <functional>
#include <memory>

class Button : public ObjectBase, public std::enable_shared_from_this<Button> {
protected:
	std::string text;
	Color text_color;
	Color background_color;
	Color mouseover_color;
	std::function<void(void)> callback_clicked;
	bool isClicked, isHovered;
	int font_size;

public:
	Button(Point center, Size size, std::string text, int font_size, std::function<void(void)> callback_clicked, Color text_color = Color(255, 255, 255), Color background_color = Color(100, 100, 100), Color mouseover_color = Color(150, 150, 150));
	void initialize() override {}
	void update() override;
	void draw() const override;
	void addDraw() override;
	void finalize() override {}

	void clicked() { this->isClicked = true; this->count = 0; }
	void setValid() { this->validation = true; }
};

class ButtonMove : public Button {
private:
	bool isOn;
	Color background_color_on;

public:
	ButtonMove(Point center, Size size, std::string text, int font_size, std::function<void(void)> callback_clicked, Color text_color = Color(255, 255, 255), Color background_color_off = Color(100, 100, 100), Color background_color_on = Color(200, 50, 50), Color mouseover_color = Color(150, 150, 150));
	void update() override;
	void addDraw() override;
	void draw() const override;

	void off() { this->isOn = false; }
};

class ButtonManager : public ObjectManagerBase<Button> {
private:

public:
	void setNewButton(Point center, Size size, std::string text, int font_size, std::function<void(void)> clicked, Color text_color = Color(255, 255, 255), Color background_color = Color(100, 100, 100), Color mouseover_color = Color(150, 150, 150));
};