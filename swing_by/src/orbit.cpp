#include "orbit.h"
#include "screen.h"
#include "image.h"
#include "DxLib.h"
#include "input.h"
#include "debug.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
CrossTarget::CrossTarget(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetCrossPosition> &map) {
	this->z_sort = 90000;
	this->size = Size(64, 64);
	for (int i = 0; i < 3; ++i)this->target_spin[i] = 0.000000;

	this->player = player;
	this->mouse_pointer = mouse_pointer;
	this->map = map;
}

void CrossTarget::initialize() {
	for (int i = 0; i < 3; ++i)this->target_spin[i] = 0.000000;
}

void CrossTarget::update() {
	this->position = this->map->getCrossPosition(this->player->getPosition(), Screen::getPositionOfWorldCoordinate(this->mouse_pointer->getPosition()));

	this->target_spin[0] += M_PI / 30;
	this->target_spin[1] -= M_PI / 40;
	for (int i = 0; i < 2; ++i) {
		if (this->target_spin[i] > M_PI * 2) this->target_spin[i] -= M_PI * 2;
		if (this->target_spin[i] < 0) this->target_spin[i] += M_PI * 2;
	}

	Screen::addDrawObjectMutable(this->shared_from_this());
}

void CrossTarget::draw() const {
	for (int i = 2; i >= 0; --i) Screen::drawMutable(this->position, this->size, Image::getCrossTarget(i), 1.0, this->target_spin[i], false, 1.0);
}

void CrossTarget::finalize() {

}
////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////
Orbit::Orbit(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<MoveObjectProperty> &pl_vel, const std::shared_ptr<ObjectBase> &mouse_pointer) {
	this->player = player;
	this->pl_vel = pl_vel;
	this->mouse_pointer = mouse_pointer;
}

void Orbit::initialize() {

}

void Orbit::update() {
	for (Point p : this->getNavigationPoints(this->player->getPosition(), this->pl_vel->getTransVelVec(), Screen::getPositionOfWorldCoordinate(this->mouse_pointer->getPosition()))) {
		std::shared_ptr<Debug_Point> dp = std::make_shared<Debug_Point>(p, 2, Color(255, 255, 0));
		dp->update();
	}
}

void Orbit::draw() const {

}

void Orbit::finalize() {

}

Point Orbit::spin(Point pos, Point center, double rad) {
	Point t;
	t.x = (pos.x - center.x)*cos(rad) - (pos.y - center.y)*sin(rad) + center.x;
	t.y = (pos.x - center.x)*sin(rad) + (pos.y - center.y)*cos(rad) + center.y;
	return t;
}

std::vector<Point> Orbit::getNavigationPoints(Point player_pos, Point player_vel, Point mouse_world_pos) {
	double rotate_rad = atan2(mouse_world_pos.y - player_pos.y, mouse_world_pos.x - player_pos.x) - M_PI / 2;

	Point pl_pos_ = this->spin(player_pos, mouse_world_pos, -rotate_rad);
	Point pl_vel_ = this->spin(player_vel, Point(0, 0), -rotate_rad);
	double r0 = abs(mouse_world_pos.y - pl_pos_.y);

	double a = abs((pl_pos_.y - mouse_world_pos.y)*(pl_pos_.y - mouse_world_pos.y) / (r0*(1 - (pl_vel_.y*pl_vel_.y / (r0*r0*pl_vel_.x*pl_vel_.x))*(pl_pos_.y - mouse_world_pos.y)*(pl_pos_.y - mouse_world_pos.y))));
	double b = sqrt(r0*a);
	double e = sqrt(a*a + b*b) / a;

	std::vector<Point> p;
	for (double theta = M_PI / 2, theta_pre = M_PI / 2; abs(theta - M_PI / 2) <= M_PI / 2; theta += 0.005*player_vel.x / abs(player_vel.x)) {
		double r = r0 / (1 + e*sin(theta));
		Point pre = pl_pos_ + Point(r*sin(theta_pre), r*cos(theta_pre));
		Point next = pl_pos_ + Point(r*sin(theta), r*cos(theta));
		if (!Screen::isVisiblePoint(next)) break;
		if (next.getDistance(pre) > 10.0) {
			theta_pre = theta;
			p.push_back(next);
		}
	}

	for (auto i = p.begin(); i != p.end(); ++i) *i = this->spin(*i, mouse_world_pos, rotate_rad);
	return p;
}

void Orbit::resetParams(Point player_pos, Point player_vel, Point mouse_pos) {
	this->ell_f_pos = mouse_pos;
	this->ell_rotate_rad = atan2(mouse_pos.y - player_pos.y, mouse_pos.x - player_pos.x);

	//mouse Šî€‚Å-ell_rotate_rad‰ñ“]
	this->ell_start_pos = this->spin(player_pos, mouse_pos, -this->ell_rotate_rad);
	this->ell_start_vel = this->spin(player_vel, Point(0, 0), -this->ell_rotate_rad);

	double r0 = abs(this->ell_f_pos.y - this->ell_start_pos.y);

	this->ell_a = (this->ell_start_pos.y - this->ell_f_pos.y)*(this->ell_start_pos.y - this->ell_f_pos.y) / (r0*(1 - (this->ell_start_vel.y*this->ell_start_vel.y / (r0*r0*this->ell_start_vel.x*this->ell_start_vel.x))*(this->ell_start_pos.y - this->ell_f_pos.y)*(this->ell_start_pos.y - this->ell_f_pos.y)));
	this->ell_b = sqrt(r0*this->ell_a);
	this->ell_center_pos.x = this->ell_start_pos.x + (this->ell_a*this->ell_start_vel.y)*(this->ell_start_pos.y - this->ell_f_pos.y) / (r0*this->ell_start_vel.x);
	this->ell_center_pos.y = this->ell_start_pos.y;
	this->ell_e = sqrt(this->ell_a*this->ell_a + this->ell_b*this->ell_b) / this->ell_a;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////
OrbitManager::OrbitManager(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<MoveObjectProperty> &pl_vel, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetCrossPosition> &map) {
	this->mouse_pointer = mouse_pointer;
	this->crossTarget = std::make_shared<CrossTarget>(player, mouse_pointer, map);
	this->orbit = std::make_shared<Orbit>(player, pl_vel, mouse_pointer);
}

void OrbitManager::initialize() {
	
}

void OrbitManager::update() {
	if (this->mouse_pointer->getPosition().x < 0) return;
	if (this->mouse_pointer->getPosition().y < 0) return;
	if (this->mouse_pointer->getPosition().x > Screen::getWindowSize().width) return;
	if (this->mouse_pointer->getPosition().y > Screen::getWindowSize().height) return;

	this->crossTarget->update();

	if (Input::getKeyCodeDown(KeyType::Game_Swing_OK)) return;
	this->orbit->update();
}

void OrbitManager::finalize() {

}
////////////////////////////////////////////////////////////////////////////////////////////////////////