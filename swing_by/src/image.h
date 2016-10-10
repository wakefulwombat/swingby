#pragma once

class Image{
private:
	static void clearAll();

	static int map_chip[22];
	static int textBox[9];
	static int mouse_pointer;
	static int player[2];
	static int cross_target[3];
	static int explosion[14];

public:
	static void loadGameScene();
	static void loadOtherScene();

	static int getMousePointer() { return Image::mouse_pointer; }
	static int getPlayer(int index) { return Image::player[index]; }
	static int getMapChip(int index){ return Image::map_chip[index]; }
	static int getCrossTarget(int index) { return Image::cross_target[index]; }
	static int getExplosion(int index) { return Image::explosion[index]; }
};
