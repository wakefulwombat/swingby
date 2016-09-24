#pragma once

class Image{
private:
	static void clearAll();

	static int map_chip[22];
	static int item[10];
	static int textBox[9];
	static int mouse_pointer;

public:
	static void loadGameScene();
	static void loadOtherScene();

	static int getMousePointer() { return Image::mouse_pointer; }
};
