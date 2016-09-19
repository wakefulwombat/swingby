#pragma once

class Image{
private:
	static void clearAll();

	static int map_chip[22];
	static int item[10];
	static int textBox[9];
public:
	

	static void loadGameScene();
	static void loadOtherScene();
};
