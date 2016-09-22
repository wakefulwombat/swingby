#pragma once

#include "common.h"

struct KeyCodeState{
	unsigned int key[4];
};

enum class KeyType{
	Common_Pause,
	Game_Slow,
	Game_Swing_OK,	
	Game_VectorTrans_CANCEL
};

class Input{
private:
	static KeyCodeState keyCodeDownCount;//キーを押している時間
	static KeyCodeState keyCodeUpCount;//キーを押していない時間
	static unsigned int mouse_wheel_rotation;//マウスホイールの回転状態
	static Point now_mouse;

public:
	static void keyUpdate();

	static bool getKeyCodeDown(KeyType key);
	static bool getKeyCodeDownOnce(KeyType key);
	static bool getKeyCodeUpOnce(KeyType key);
	static int getMouseWheelRotation();
	static Point getNowMousePoint();

	static void setNowMousePoint(Point pos);

	static bool isObjectOnMouse(Point leftup, Size size);
	static bool isObjectLeftClicked(Point leftup, Size size);
	static bool isObjectRightClicked(Point leftup, Size size);
};
