#pragma once

class Image{
private:
	static void clearAll();

	static int map_chip[22];
	static int item[10];
	static int textBox[9];
	static int mouse_pointer;
	static int player[2];

public:
	static void loadGameScene();
	static void loadOtherScene();

	static int getMousePointer() { return Image::mouse_pointer; }
	static int getPlayer(int index) { return Image::player[index]; }
};
