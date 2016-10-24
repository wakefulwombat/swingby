#include "orbit.h"
#include "image.h"
#include "DxLib.h"
#include "input.h"
#include "debug.h"
#include "screen.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
CrossTarget::CrossTarget(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetMapCrossPosition> &map) {
	this->z_sort = 10000;
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
	this->position = this->map->getMapCrossPosition(this->player->getPosition(), Screen::getPositionOfWorldCoordinate(this->mouse_pointer->getPosition()));

	this->target_spin[0] += M_PI / 30;
	this->target_spin[1] -= M_PI / 40;
	for (int i = 0; i < 2; ++i) {
		if (this->target_spin[i] > M_PI * 2) this->target_spin[i] -= M_PI * 2;
		if (this->target_spin[i] < 0) this->target_spin[i] += M_PI * 2;
	}

	this->addDraw();
}

void CrossTarget::draw() const {
	for (int i = 2; i >= 0; --i) Screen::drawMutable(this->position, this->size, Image::getCrossTarget(i), 1.0, this->target_spin[i], false, 1.0);
}

void CrossTarget::finalize() {

}
////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////
Orbit::Orbit(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<MoveObjectProperty> &pl_vel, const std::shared_ptr<ObjectBase> &cross_target) {
	this->player = player;
	this->pl_vel = pl_vel;
	this->cross_target = cross_target;
}

void Orbit::initialize() {

}

void Orbit::update() {
	this->addDraw();
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

std::vector<Point> Orbit::getNavigationPoints(Point player_pos, Point player_vel, Point cross_target) {
	double rotate_rad =atan2(cross_target.y - player_pos.y, cross_target.x - player_pos.x) + M_PI / 2;

	Point pl_pos_ = this->spin(player_pos, cross_target, -rotate_rad);
	Point pl_vel_ = this->spin(player_vel, Point(0, 0), -rotate_rad);
	double r0 = pl_pos_.y - cross_target.y;

	double a = abs((pl_pos_.y - cross_target.y)*(pl_pos_.y - cross_target.y) / (r0*(1 - (pl_vel_.y*pl_vel_.y / (r0*r0*pl_vel_.x*pl_vel_.x))*(pl_pos_.y - cross_target.y)*(pl_pos_.y - cross_target.y))));
	double b = sqrt(r0*a);
	double e = sqrt(a*a + b*b) / a;

	double ell_center_x = pl_pos_.x + (a*pl_vel_.y)*(pl_pos_.y - cross_target.y) / (r0*pl_vel_.x);
	double ell_center_y = cross_target.y;

	std::vector<Point> p;
	double theta = 0.000000;
	for (Point pre = pl_pos_, next = pl_pos_;;) {
		double dx;
		if(pl_vel_.x>=0.0) dx = 50.0 / sqrt(1 + pow(b, 4.0)*pow(pre.x - ell_center_x, 2.0) / pow(a, 4.0) / pow(pre.y - ell_center_y, 2.0));
		else dx = -50.0 / sqrt(1 + pow(b, 4.0)*pow(pre.x - ell_center_x, 2.0) / pow(a, 4.0) / pow(pre.y - ell_center_y, 2.0));
		double dy = -b*b / a / a * (pre.x - ell_center_x) / (pre.y - ell_center_y)*dx;
		next = pre + Point(dx, dy);
		theta += abs(atan2(next.y - cross_target.y, next.x - cross_target.x) - atan2(pre.y - cross_target.y, pre.x - cross_target.x));
		
		if (!Screen::isVisiblePoint(this->spin(next, cross_target, rotate_rad))) break;
		if (theta > M_PI / 2) break;
		p.push_back(this->spin(next, cross_target, rotate_rad));
		pre = next;
	}

	return p;
}

void Orbit::resetParams(Point under_f_pos, Point under_f_vel, Point f_pos) {
	this->ell_rotate_rad = atan2(f_pos.y - under_f_pos.y, f_pos.x - under_f_pos.x) + M_PI / 2;

	Point under_f_pos_ = this->spin(under_f_pos, f_pos, -this->ell_rotate_rad);
	Point under_f_vel_ = this->spin(under_f_vel, Point(0, 0), -this->ell_rotate_rad);
	this->ell_r0 = under_f_pos_.y - f_pos.y;

	this->ell_a = abs((under_f_pos_.y - f_pos.y)*(under_f_pos_.y - f_pos.y) / (this->ell_r0*(1 - (under_f_vel_.y*under_f_vel_.y / (this->ell_r0*this->ell_r0*under_f_vel_.x*under_f_vel_.x))*(under_f_pos_.y - f_pos.y)*(under_f_pos_.y - f_pos.y))));
	this->ell_b = sqrt(this->ell_r0*this->ell_a);
	this->ell_e = sqrt(this->ell_a*this->ell_a + this->ell_b*this->ell_b) / this->ell_a;

	this->ell_center_pos.x = under_f_pos_.x + (this->ell_a*under_f_vel_.y)*(under_f_pos_.y - f_pos.y) / (this->ell_r0*under_f_vel_.x);
	this->ell_center_pos.y = f_pos.y;
	this->ell_f_pos = f_pos;

	this->go_front = under_f_vel_.x >= 0.0;
	this->go_accele = abs(atan2(under_f_vel_.y, under_f_vel_.x) + M_PI / 2) < M_PI / 2;
	this->move_vel = sqrt(under_f_vel.x*under_f_vel.x + under_f_vel.y*under_f_vel.y);
	this->total_rotate_rad = 0.000000;
	this->run_circle = false;
}

Point Orbit::getNextVelocityVector(Point now) {
	double dx, dy;
	Point now_ = this->spin(now, this->ell_f_pos, -this->ell_rotate_rad);

	if(!this->run_circle) {
		if (this->go_accele) this->move_vel *= 1.005;
		else this->move_vel /= 1.005;
		if (this->move_vel < 1.0) this->move_vel = 1.0;

		if (this->go_front) dx = this->move_vel / sqrt(1 + pow(this->ell_b, 4.0)*pow(now_.x - this->ell_center_pos.x, 2.0) / pow(this->ell_a, 4.0) / pow(now_.y - this->ell_center_pos.y, 2.0));
		else dx = -this->move_vel / sqrt(1 + pow(this->ell_b, 4.0)*pow(now_.x - this->ell_center_pos.x, 2.0) / pow(this->ell_a, 4.0) / pow(now_.y - this->ell_center_pos.y, 2.0));
		dy = -this->ell_b*this->ell_b / this->ell_a / this->ell_a * (now_.x - this->ell_center_pos.x) / (now_.y - this->ell_center_pos.y)*dx;
		this->total_rotate_rad += atan2(now_.y + dy - this->ell_f_pos.y, now_.x + dx - this->ell_f_pos.x) - atan2(now_.y - this->ell_f_pos.y, now_.x - this->ell_f_pos.x);
		if (abs(this->total_rotate_rad) > M_PI / 2) this->run_circle = true;
	}
	else {
		double r;
		if (this->go_accele) r = this->ell_r0 / (1 + this->ell_e);
		else r = this->ell_r0 / (1 - this->ell_e);

		Point pre = Point(r*cos(this->total_rotate_rad + M_PI / 2), r*sin(this->total_rotate_rad + M_PI / 2));
		
		double omega;
		if(this->go_front) omega = -this->move_vel / r;
		else omega = this->move_vel / r;
		this->total_rotate_rad += omega;
		
		Point aft = Point(r*cos(this->total_rotate_rad + M_PI / 2), r*sin(this->total_rotate_rad + M_PI / 2));

		dx = aft.x - pre.x;
		dy = aft.y - pre.y;
	}
	return this->spin(Point(dx, dy), Point(0, 0), this->ell_rotate_rad);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////
OrbitManager::OrbitManager(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<MoveObjectProperty> &pl_vel, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetMapCrossPosition> &map) {
	this->mouse_pointer = mouse_pointer;
	this->crossTarget = std::make_shared<CrossTarget>(player, mouse_pointer, map);
	this->orbit = std::make_shared<Orbit>(player, pl_vel, this->crossTarget);

	this->validation = true;
}

void OrbitManager::initialize() {
	
}

void OrbitManager::update() {
	if (!this->validation) return;

	if (this->mouse_pointer->getPosition().x < 0) return;
	if (this->mouse_pointer->getPosition().y < 0) return;
	if (this->mouse_pointer->getPosition().x > Screen::getWindowSize().width) return;
	if (this->mouse_pointer->getPosition().y > Screen::getWindowSize().height) return;

	this->crossTarget->update();

	if (!Screen::isVisible(this->crossTarget)) return;
	if (Input::getKeyCodeDown(KeyType::Game_Swing_OK)) return;
	this->orbit->update();
}

void OrbitManager::finalize() {

}

void OrbitManager::resetOrbitParams(Point player_pos, Point player_vel, Point target_pos) {
	this->orbit->resetParams(player_pos, player_vel, target_pos);
}

Point OrbitManager::getOrbitNextVelocityVector(Point player_now_pos) {
	return this->orbit->getNextVelocityVector(player_now_pos);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////