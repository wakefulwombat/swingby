#include "input.h"
#include "common.h"
#include "DxLib.h"
#include <stdio.h>
#include <math.h>

KeyCodeState Input::keyCodeDownCount;
KeyCodeState Input::keyCodeUpCount;
unsigned int Input::mouse_wheel_rotation = 0;
Point Input::now_mouse = Point(-1, -1);


void Input::keyUpdate() {
	//キーボード
	char key[256];
	GetHitKeyStateAll(key);

	if (key[KEY_INPUT_P] != 0) {
		Input::keyCodeDownCount.key[(int)KeyType::Common_Pause]++;
		Input::keyCodeUpCount.key[(int)KeyType::Common_Pause] = 0;
	}
	else {
		Input::keyCodeUpCount.key[(int)KeyType::Common_Pause]++;
		Input::keyCodeDownCount.key[(int)KeyType::Common_Pause] = 0;
	}

	if (key[KEY_INPUT_SPACE] != 0) {
		Input::keyCodeDownCount.key[(int)KeyType::Game_Slow]++;
		Input::keyCodeUpCount.key[(int)KeyType::Game_Slow] = 0;
	}
	else {
		Input::keyCodeUpCount.key[(int)KeyType::Game_Slow]++;
		Input::keyCodeDownCount.key[(int)KeyType::Game_Slow] = 0;
	}

	//マウス
	int x, y;
	GetMousePoint(&x, &y);
	Input::now_mouse.x = x;
	Input::now_mouse.y = y;

	int mouse = GetMouseInput();
	if (mouse&MOUSE_INPUT_LEFT) {//OK or Swing
		Input::keyCodeDownCount.key[(int)KeyType::Game_Swing_OK]++;
		Input::keyCodeUpCount.key[(int)KeyType::Game_Swing_OK] = 0;
	}
	else {
		Input::keyCodeDownCount.key[(int)KeyType::Game_Swing_OK]=0;
		Input::keyCodeUpCount.key[(int)KeyType::Game_Swing_OK]++;
	}

	if (mouse&MOUSE_INPUT_RIGHT) {//Cancel or Trans
		Input::keyCodeDownCount.key[(int)KeyType::Game_VectorTrans_CANCEL]++;
		Input::keyCodeUpCount.key[(int)KeyType::Game_VectorTrans_CANCEL] = 0;
	}
	else {
		Input::keyCodeDownCount.key[(int)KeyType::Game_VectorTrans_CANCEL] = 0;
		Input::keyCodeUpCount.key[(int)KeyType::Game_VectorTrans_CANCEL]++;
	}

	if (mouse&MOUSE_INPUT_MIDDLE) {//pause
		Input::keyCodeDownCount.key[(int)KeyType::Common_Pause]++;
		Input::keyCodeUpCount.key[(int)KeyType::Common_Pause] = 0;
	}
	else {
		Input::keyCodeDownCount.key[(int)KeyType::Common_Pause] = 0;
		Input::keyCodeUpCount.key[(int)KeyType::Common_Pause]++;
	}

	Input::mouse_wheel_rotation = GetMouseWheelRotVol();
}

bool Input::getKeyCodeDown(KeyType key){
	return (Input::keyCodeDownCount.key[(int)key] != 0);
}

bool Input::getKeyCodeDownOnce(KeyType key){
	return (Input::keyCodeDownCount.key[(int)key] == 1);
}

bool Input::getKeyCodeUpOnce(KeyType key){
	return (Input::keyCodeUpCount.key[(int)key] == 1);
}

int Input::getMouseWheelRotation() {
	return Input::mouse_wheel_rotation;
}

Point Input::getNowMousePoint() {
	return Input::now_mouse;
}

bool Input::isObjectOnMouse(Point leftup, Size size) {
	if (Input::now_mouse.x < leftup.x) return false;
	if (Input::now_mouse.y < leftup.y) return false;
	if (Input::now_mouse.x + size.width > leftup.x) return false;
	if (Input::now_mouse.y + size.height > leftup.y) return false;
	return true;
}

bool Input::isObjectLeftClicked(Point leftup, Size size) {
	if (Input::getKeyCodeDownOnce(KeyType::Game_Swing_OK) != 0)return;

	if (Input::now_mouse.x < leftup.x) return false;
	if (Input::now_mouse.y < leftup.y) return false;
	if (Input::now_mouse.x + size.width > leftup.x) return false;
	if (Input::now_mouse.y + size.height > leftup.y) return false;
	return true;
}

bool Input::isObjectRightClicked(Point leftup, Size size) {
	if (Input::getKeyCodeDownOnce(KeyType::Game_VectorTrans_CANCEL) != 0)return;

	if (Input::now_mouse.x < leftup.x) return false;
	if (Input::now_mouse.y < leftup.y) return false;
	if (Input::now_mouse.x + size.width > leftup.x) return false;
	if (Input::now_mouse.y + size.height > leftup.y) return false;
	return true;
}

void Input::setNowMousePoint(Point pos) {
	Input::now_mouse = pos;
	SetMousePoint(pos.x, pos.y);
}