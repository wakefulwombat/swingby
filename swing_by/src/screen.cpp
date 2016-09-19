#include "screen.h"
#include "DxLib.h"

Size Screen::windowSize, Screen::stageSize;
Point Screen::center;
double Screen::zoom;
Point Screen::sway;


int Screen::center_move_count, Screen::center_move_count_max;
Point Screen::centerTergetPosition_start, Screen::centerTergetPosition_goal;

int Screen::zoom_count, Screen::zoom_count_max;
double Screen::zoom_magnification_start, Screen::zoom_magnification_end;

int Screen::sway_count, Screen::sway_count_max;
double Screen::sway_intensity_max;

void Screen::setCenterTargetPosition(Point target, int count_max){
	Screen::center_move_count = 0;
	Screen::center_move_count_max = count_max;
	Screen::centerTergetPosition_goal = target;
	Screen::centerTergetPosition_start = Screen::center;
}

void Screen::setZoomIn(double zoom_max, int zoomin_count_max){
	Screen::zoom_count = 0;
	Screen::zoom_count_max = zoomin_count_max;
	Screen::zoom_magnification_end = zoom_max;
	Screen::zoom_magnification_start = Screen::zoom;
}

void Screen::setZoomOut(int zoomout_count_max){
	Screen::zoom_count = 0;
	Screen::zoom_count_max = zoomout_count_max;
	Screen::zoom_magnification_end = 1.0;
	Screen::zoom_magnification_start = Screen::zoom;
}

void Screen::setSway(double intensity, int count_max){
	Screen::sway_count = 0;
	Screen::sway_count_max = count_max;
	Screen::sway_intensity_max = intensity;
}

void Screen::drawMutable(Point center_pos, Size size, int graphHandle, double expansion, double rotation, bool turn){
	if (center_pos.x + expansion * size.width / 2 < Screen::center.x - Screen::windowSize.width / Screen::zoom / 2) return;
	if (center_pos.x - expansion * size.width / 2 > Screen::center.x + Screen::windowSize.width / Screen::zoom / 2) return;
	if (center_pos.y + expansion * size.height / 2 < Screen::center.y - Screen::windowSize.height / Screen::zoom / 2) return;
	if (center_pos.y - expansion * size.height / 2 > Screen::center.y + Screen::windowSize.height / Screen::zoom / 2) return;

	DrawRotaGraph2((int)(Screen::sway.x + center_pos.x), (int)(Screen::sway.y + center_pos.y), size.width / 2, size.height / 2, expansion*Screen::zoom, rotation, graphHandle, true, turn);
}

void Screen::drawMutable(Point center_pos, Size size, int graphHandle, double expansion_x, double expansion_y, double rotation, bool turn){
	if (center_pos.x + expansion_x * size.width / 2 < Screen::center.x - Screen::windowSize.width / Screen::zoom / 2) return;
	if (center_pos.x - expansion_x * size.width / 2 > Screen::center.x + Screen::windowSize.width / Screen::zoom / 2) return;
	if (center_pos.y + expansion_y * size.height / 2 < Screen::center.y - Screen::windowSize.height / Screen::zoom / 2) return;
	if (center_pos.y - expansion_y * size.height / 2 > Screen::center.y + Screen::windowSize.height / Screen::zoom / 2) return;

	DrawRotaGraph3((int)(Screen::sway.x + center_pos.x), (int)(Screen::sway.y + center_pos.y), size.width / 2, size.height / 2, expansion_x*Screen::zoom, expansion_y*Screen::zoom, rotation, graphHandle, true, turn);
}

void Screen::drawOnWindow(Point center_pos, Size size, int graphHandle, double expansion, double rotation){
	DrawRotaGraph2((int)center_pos.x, (int)center_pos.y, size.width / 2, size.height / 2, expansion, rotation, graphHandle, true);
}

void Screen::init(int window_width, int window_height){
	Screen::windowSize.width = window_width;
	Screen::windowSize.height = window_height;
}

void Screen::update(){
	Screen::center_move_count++;
	Screen::zoom_count++;
	Screen::sway_count++;

	if (Screen::zoom_count <= Screen::zoom_count_max){
		Screen::zoom = (Screen::zoom_magnification_end - Screen::zoom_magnification_start)*Screen::zoom_count / Screen::zoom_count_max + Screen::zoom_magnification_start;
	}
	Screen::center.x = (Screen::centerTergetPosition_goal.x - Screen::centerTergetPosition_start.x)*Screen::center_move_count / Screen::center_move_count_max;
	Screen::center.y = (Screen::centerTergetPosition_goal.y - Screen::centerTergetPosition_start.y)*Screen::center_move_count / Screen::center_move_count_max;

	if (Screen::sway_count > Screen::sway_count_max) Screen::sway = Point();
	else Screen::sway = Point::getCircleRandomPoint(Point(), Screen::sway_intensity_max*(Screen::sway_count_max - Screen::sway_count) / Screen::sway_count_max, Point(-100, -100), Point(100, 100));


	if (Screen::center.x < 1.0*Screen::windowSize.width / 2.0 / Screen::zoom) Screen::center.x = 1.0*Screen::windowSize.width / 2.0 / Screen::zoom;
	if (Screen::center.y < 1.0*Screen::windowSize.height / 2.0 / Screen::zoom) Screen::center.y = 1.0*Screen::windowSize.height / 2.0 / Screen::zoom;
	if (Screen::center.x > 1.0*Screen::stageSize.width - 1.0*Screen::windowSize.width / 2.0 / Screen::zoom) Screen::center.x = 1.0*Screen::stageSize.width - 1.0*Screen::windowSize.width / 2.0 / Screen::zoom;
	if (Screen::center.y > 1.0*Screen::stageSize.height - 1.0*Screen::windowSize.height / 2.0 / Screen::zoom) Screen::center.y = 1.0*Screen::stageSize.height - 1.0*Screen::windowSize.height / 2.0 / Screen::zoom;
}