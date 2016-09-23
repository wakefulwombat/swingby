#include "player.h"
#include "input.h"
#include <math.h>

Player::Player() {
	this->count = 0;
}

void Player::initialize() {

}

void Player::update() {
	this->count++;
	this->internalController->update();

	if (Input::getKeyCodeDownOnce(KeyType::Game_Swing_OK) == 0) {

	}
	if (Input::getKeyCodeUpOnce(KeyType::Game_Swing_OK) == 0) {
		this->internalController = this->controller->getInternalMoveObjectController_GoStraight(this, this);
	}
	if (Input::getKeyCodeDown(KeyType::Game_Swing_OK) == 0) {

	}

	if (Input::getKeyCodeDownOnce(KeyType::Game_VectorTrans_CANCEL) == 0) {

	}
	if (Input::getKeyCodeUpOnce(KeyType::Game_VectorTrans_CANCEL) == 0) {

	}
	if (Input::getKeyCodeDown(KeyType::Game_VectorTrans_CANCEL) == 0) {

	}
}

void Player::draw() const {

}

void Player::finalize() {

}