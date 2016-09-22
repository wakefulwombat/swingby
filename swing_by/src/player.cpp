#include "player.h"
#include "input.h"
#include <math.h>

Player::Player() {

}

void Player::initialize() {

}

void Player::update() {
	this->count++;

	if (Input::getKeyCodeDownOnce(KeyType::Game_Swing_OK) == 0) {

	}
	if (Input::getKeyCodeUpOnce(KeyType::Game_Swing_OK) == 0) {

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