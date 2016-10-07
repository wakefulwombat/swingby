#include "image.h"
#include "DxLib.h"

int Image::map_chip[22];
int Image::item[10];
int Image::textBox[9];
int Image::mouse_pointer;
int Image::player[2];
int Image::cross_target[3];

void Image::clearAll(){
	InitGraph();
}

void Image::loadGameScene(){
	Image::map_chip[0] = LoadGraph("asset\\mapchip\\01.bmp");
	Image::map_chip[1] = LoadGraph("asset\\mapchip\\02.bmp");
	Image::map_chip[2] = LoadGraph("asset\\mapchip\\03.bmp");
	Image::map_chip[3] = LoadGraph("asset\\mapchip\\04.bmp");
	Image::map_chip[4] = LoadGraph("asset\\mapchip\\05.bmp");
	Image::map_chip[5] = LoadGraph("asset\\mapchip\\06.bmp");
	Image::map_chip[6] = LoadGraph("asset\\mapchip\\07.bmp");
	Image::map_chip[7] = LoadGraph("asset\\mapchip\\08.bmp");
	Image::map_chip[8] = LoadGraph("asset\\mapchip\\09.bmp");
	Image::map_chip[9] = LoadGraph("asset\\mapchip\\10.bmp");
	Image::map_chip[10] = LoadGraph("asset\\mapchip\\11.bmp");
	Image::map_chip[11] = LoadGraph("asset\\mapchip\\12.bmp");
	Image::map_chip[12] = LoadGraph("asset\\mapchip\\13.bmp");
	Image::map_chip[13] = LoadGraph("asset\\mapchip\\14.bmp");
	Image::map_chip[14] = LoadGraph("asset\\mapchip\\15.bmp");
	Image::map_chip[15] = LoadGraph("asset\\mapchip\\16.bmp");
	Image::map_chip[16] = LoadGraph("asset\\mapchip\\17.bmp");
	Image::map_chip[17] = LoadGraph("asset\\mapchip\\18.bmp");
	Image::map_chip[18] = LoadGraph("asset\\mapchip\\19.bmp");
	Image::map_chip[19] = LoadGraph("asset\\mapchip\\20.bmp");
	Image::map_chip[20] = LoadGraph("asset\\mapchip\\21.bmp");
	Image::map_chip[21] = LoadGraph("asset\\mapchip\\22.bmp");

	LoadDivGraph("asset\\text_box.png", 9, 3, 3, 10, 10, Image::textBox);

	Image::mouse_pointer = LoadGraph("asset\\pointer.png");

	LoadDivGraph("asset\\player.png", 2, 2, 1, 56, 24, Image::player);

	Image::cross_target[0] = LoadGraph("asset\\crosstarget\\1.png");
	Image::cross_target[1] = LoadGraph("asset\\crosstarget\\2.png");
	Image::cross_target[2] = LoadGraph("asset\\crosstarget\\3.png");
}

void Image::loadOtherScene(){

}