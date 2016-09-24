#include "screen.h"
#include "DxLib.h"
#include <algorithm>

Size Screen::windowSize, Screen::stageSize;
Point Screen::window_center_world_pos;
double Screen::zoom;
Point Screen::sway;
std::vector<ObjectBase*> Screen::draw_list;

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
	Screen::centerTergetPosition_start = Screen::window_center_world_pos;
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

void Screen::drawMutable(Point center_pos, Size size, int graphHandle, double expansion, double rotation, bool turn, double opacity){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(opacity * 255));
	DrawRotaGraph2((int)(Screen::sway.x + center_pos.x - Screen::window_center_world_pos.x + Screen::windowSize.width / Screen::zoom / 2), (int)(Screen::sway.y + center_pos.y - Screen::window_center_world_pos.y + Screen::windowSize.height / Screen::zoom / 2), size.width / 2, size.height / 2, expansion*Screen::zoom, rotation, graphHandle, true, turn);
}

void Screen::drawMutable(Point center_pos, Size size, int graphHandle, double expansion_x, double expansion_y, double rotation, bool turn, double opacity){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(opacity * 255));
	DrawRotaGraph3((int)(Screen::sway.x + center_pos.x - Screen::window_center_world_pos.x + Screen::windowSize.width / Screen::zoom / 2), (int)(Screen::sway.y + center_pos.y - Screen::window_center_world_pos.y + Screen::windowSize.height / Screen::zoom / 2), size.width / 2, size.height / 2, expansion_x*Screen::zoom, expansion_y*Screen::zoom, rotation, graphHandle, true, turn);
}

void Screen::drawOnWindow(Point center_pos, Size size, int graphHandle, double expansion, double rotation, double opacity){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(opacity * 255));
	DrawRotaGraph2((int)center_pos.x, (int)center_pos.y, size.width / 2, size.height / 2, expansion, rotation, graphHandle, true);
}

void Screen::drawOnWindowForMouse(Point leftup_pos, int graphHandle, double opacity) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(opacity * 255));
	DrawGraph((int)leftup_pos.x, (int)leftup_pos.y, graphHandle, true);
}

void Screen::init(int window_width, int window_height){
	Screen::windowSize.width = window_width;
	Screen::windowSize.height = window_height;
	Screen::window_center_world_pos = Point(window_width / 2, window_height / 2);
	Screen::center_move_count_max = 100;
	Screen::center_move_count = Screen::center_move_count_max;
	Screen::centerTergetPosition_start = Point(window_width / 2, window_height / 2);
	Screen::centerTergetPosition_goal = Point(window_width / 2, window_height / 2);
	Screen::zoom = 1.0;
	Screen::zoom_magnification_end = 1.0;
	Screen::zoom_magnification_start = 1.0;
}

void Screen::update(){
	Screen::center_move_count++;
	Screen::zoom_count++;
	Screen::sway_count++;

	if (Screen::zoom_count <= Screen::zoom_count_max){
		Screen::zoom = (Screen::zoom_magnification_end - Screen::zoom_magnification_start)*Screen::zoom_count / Screen::zoom_count_max + Screen::zoom_magnification_start;
	}
	Screen::window_center_world_pos.x = Screen::centerTergetPosition_start.x + (Screen::centerTergetPosition_goal.x - Screen::centerTergetPosition_start.x)*Screen::center_move_count / Screen::center_move_count_max;
	Screen::window_center_world_pos.y = Screen::centerTergetPosition_start.y + (Screen::centerTergetPosition_goal.y - Screen::centerTergetPosition_start.y)*Screen::center_move_count / Screen::center_move_count_max;

	if (Screen::sway_count > Screen::sway_count_max) Screen::sway = Point();
	else Screen::sway = Point::getCircleRandomPoint(Point(), Screen::sway_intensity_max*(Screen::sway_count_max - Screen::sway_count) / Screen::sway_count_max, Point(-100, -100), Point(100, 100));


	if (Screen::window_center_world_pos.x < 1.0*Screen::windowSize.width / 2.0 / Screen::zoom) Screen::window_center_world_pos.x = 1.0*Screen::windowSize.width / 2.0 / Screen::zoom;
	if (Screen::window_center_world_pos.y < 1.0*Screen::windowSize.height / 2.0 / Screen::zoom) Screen::window_center_world_pos.y = 1.0*Screen::windowSize.height / 2.0 / Screen::zoom;
	if (Screen::window_center_world_pos.x > 1.0*Screen::stageSize.width - 1.0*Screen::windowSize.width / 2.0 / Screen::zoom) Screen::window_center_world_pos.x = 1.0*Screen::stageSize.width - 1.0*Screen::windowSize.width / 2.0 / Screen::zoom;
	if (Screen::window_center_world_pos.y > 1.0*Screen::stageSize.height - 1.0*Screen::windowSize.height / 2.0 / Screen::zoom) Screen::window_center_world_pos.y = 1.0*Screen::stageSize.height - 1.0*Screen::windowSize.height / 2.0 / Screen::zoom;
}

void Screen::drawAll() {
	std::sort(Screen::draw_list.begin(), Screen::draw_list.end());
	for(auto var : Screen::draw_list)
	{
		var->draw();
	}
	Screen::draw_list.clear();
}

void Screen::addDrawObject(ObjectBase* obj) {
	if (obj->getPosition().x + obj->getExpansion() * obj->getSize().width / 2 < Screen::window_center_world_pos.x - Screen::windowSize.width / Screen::zoom / 2) return;
	if (obj->getPosition().x - obj->getExpansion() * obj->getSize().width / 2 > Screen::window_center_world_pos.x + Screen::windowSize.width / Screen::zoom / 2) return;
	if (obj->getPosition().y + obj->getExpansion() * obj->getSize().height / 2 < Screen::window_center_world_pos.y - Screen::windowSize.height / Screen::zoom / 2) return;
	if (obj->getPosition().y - obj->getExpansion() * obj->getSize().height / 2 > Screen::window_center_world_pos.y + Screen::windowSize.height / Screen::zoom / 2) return;
	
	Screen::draw_list.push_back(obj);
}