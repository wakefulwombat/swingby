#include "player.h"
#include "input.h"
#include "screen.h"
#include <math.h>

Player::Player(IGetController* ctrl_mgr) {
	this->count = 0;
	this->ctrl_mgr = ctrl_mgr;
	this->internalController = this->ctrl_mgr->getInternalMoveObjectController_None();
}

void Player::initialize() {

}

void Player::update() {
	this->count++;
	this->internalController->update();

	if (Input::getKeyCodeDownOnce(KeyType::Game_Swing_OK) == 0) {

	}
	if (Input::getKeyCodeUpOnce(KeyType::Game_Swing_OK) == 0) {
		this->internalController = this->ctrl_mgr->getInternalMoveObjectController_GoStraight(this, this);
	}
	if (Input::getKeyCodeDown(KeyType::Game_Swing_OK) == 0) {

	}

	if (Input::getKeyCodeDownOnce(KeyType::Game_VectorTrans_CANCEL) == 0) {

	}
	if (Input::getKeyCodeUpOnce(KeyType::Game_VectorTrans_CANCEL) == 0) {

	}
	if (Input::getKeyCodeDown(KeyType::Game_VectorTrans_CANCEL) == 0) {

	}

	Screen::addDrawObject(this);
}

void Player::draw() const {

}

void Player::finalize() {

}