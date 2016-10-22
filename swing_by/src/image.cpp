#include "image.h"
#include "DxLib.h"

int Image::map_chip[22];
int Image::textBox[9];
int Image::mouse_pointer;
int Image::player[2];
int Image::cross_target[3];
int Image::explosion[14];
int Image::message[4];
int Image::number[10];
int Image::dot;
int Image::rank[4];

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

	LoadDivGraph("asset\\explosion.png", 14, 14, 1, 240, 240, Image::explosion);

	Image::message[(int)MessageType::PAUSE] = LoadGraph("asset\\message\\pause.png");
	Image::message[(int)MessageType::GAMEOVER] = LoadGraph("asset\\message\\gameover.png");
	Image::message[(int)MessageType::STAGECLEAR] = LoadGraph("asset\\message\\stageclear.png");
	Image::message[(int)MessageType::RESULT] = LoadGraph("asset\\message\\result.png");

	Image::number[0] = LoadGraph("asset\\number\\w0.png");
	Image::number[1] = LoadGraph("asset\\number\\w1.png");
	Image::number[2] = LoadGraph("asset\\number\\w2.png");
	Image::number[3] = LoadGraph("asset\\number\\w3.png");
	Image::number[4] = LoadGraph("asset\\number\\w4.png");
	Image::number[5] = LoadGraph("asset\\number\\w5.png");
	Image::number[6] = LoadGraph("asset\\number\\w6.png");
	Image::number[7] = LoadGraph("asset\\number\\w7.png");
	Image::number[8] = LoadGraph("asset\\number\\w8.png");
	Image::number[9] = LoadGraph("asset\\number\\w9.png");

	Image::dot = LoadGraph("asset\\number\\dot.png");

	Image::rank[0] = LoadGraph("asset\\rank\\S.png");
	Image::rank[1] = LoadGraph("asset\\rank\\A.png");
	Image::rank[2] = LoadGraph("asset\\rank\\B.png");
	Image::rank[3] = LoadGraph("asset\\rank\\C.png");
}

void Image::loadOtherScene(){

}