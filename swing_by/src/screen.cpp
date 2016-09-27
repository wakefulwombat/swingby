#include "screen.h"
#include "DxLib.h"
#include <algorithm>

Size Screen::windowSize, Screen::stageSize;
Point Screen::window_center_world_pos;
Point Screen::target_pos_delta;
double Screen::zoom;
Point Screen::sway;
std::vector<ObjectBase*> Screen::draw_list;

int Screen::move_count, Screen::move_count_max;
Point Screen::tergetPosition_start, Screen::tergetPosition_goal;

int Screen::zoom_count, Screen::zoom_count_max;
double Screen::zoom_magnification_start, Screen::zoom_magnification_end;

int Screen::sway_count, Screen::sway_count_max;
double Screen::sway_intensity_max;

void Screen::initTargetPositionDeltaCenter(Point delta) {
	Screen::target_pos_delta = delta;
}

void Screen::setTargetWorldPosition(Point target, int count_max){
	Screen::move_count = 0;
	Screen::move_count_max = count_max;
	Screen::tergetPosition_goal = target;
	Screen::tergetPosition_start = Screen::window_center_world_pos + Screen::target_pos_delta;
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

void Screen::setStageSize(Size size) {
	Screen::stageSize = size;
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
	Screen::move_count_max = 100;
	Screen::move_count = Screen::move_count_max;
	Screen::tergetPosition_start = Point(window_width / 2, window_height / 2);
	Screen::tergetPosition_goal = Point(window_width / 2, window_height / 2);
	Screen::target_pos_delta = Point();
	Screen::zoom = 1.0;
	Screen::zoom_magnification_end = 1.0;
	Screen::zoom_magnification_start = 1.0;
}

void Screen::update(){
	Screen::move_count++;
	Screen::zoom_count++;
	Screen::sway_count++;

	if (Screen::move_count <= Screen::move_count_max) {
		Screen::window_center_world_pos = Screen::tergetPosition_start + (Screen::tergetPosition_goal - Screen::tergetPosition_start)*(1.0*Screen::move_count/ Screen::move_count_max) + Screen::target_pos_delta;
	}
	else {
		Screen::window_center_world_pos = Screen::tergetPosition_goal + Screen::target_pos_delta;
	}
	
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

void Screen::addDrawObjectMutable(ObjectBase* obj) {
	if (obj->getPosition().x + obj->getExpansion() * obj->getSize().width / 2 < Screen::window_center_world_pos.x - Screen::windowSize.width / Screen::zoom / 2) return;
	if (obj->getPosition().x - obj->getExpansion() * obj->getSize().width / 2 > Screen::window_center_world_pos.x + Screen::windowSize.width / Screen::zoom / 2) return;
	if (obj->getPosition().y + obj->getExpansion() * obj->getSize().height / 2 < Screen::window_center_world_pos.y - Screen::windowSize.height / Screen::zoom / 2) return;
	if (obj->getPosition().y - obj->getExpansion() * obj->getSize().height / 2 > Screen::window_center_world_pos.y + Screen::windowSize.height / Screen::zoom / 2) return;
	
	Screen::draw_list.push_back(obj);
}

void Screen::addDrawObjectWindow(ObjectBase* obj) {
	Screen::draw_list.push_back(obj);
}

bool Screen::isVisible(ObjectBase* obj) {
	if (obj->getPosition().x + obj->getExpansion() * obj->getSize().width / 2 < Screen::window_center_world_pos.x - Screen::windowSize.width / Screen::zoom / 2) return false;
	if (obj->getPosition().x - obj->getExpansion() * obj->getSize().width / 2 > Screen::window_center_world_pos.x + Screen::windowSize.width / Screen::zoom / 2) return false;
	if (obj->getPosition().y + obj->getExpansion() * obj->getSize().height / 2 < Screen::window_center_world_pos.y - Screen::windowSize.height / Screen::zoom / 2) return false;
	if (obj->getPosition().y - obj->getExpansion() * obj->getSize().height / 2 > Screen::window_center_world_pos.y + Screen::windowSize.height / Screen::zoom / 2) return false;

	return true;
}