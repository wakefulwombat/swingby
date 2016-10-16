#include "scene_gameMainStageClear.h"
#include "screen.h"
#include "input.h"

SceneGameMainStageClear::SceneGameMainStageClear(std::function<void(void)> result) {
	this->result = result;

	this->explosion = std::make_shared<ExplosionManager>();
	this->clear_mes = std::make_shared<Message>(Point(Screen::getWindowSize().width / 2, Screen::getWindowSize().height / 3), MessageType::STAGECLEAR);
	int count = 0;
}

void SceneGameMainStageClear::update() {
	this->count++;

	if (this->count > 300) {
		this->result();
	}
	if (Input::getKeyCodeDownOnce(KeyType::Game_Swing_OK)) {
		this->result();
	}

	if (this->count % 3 == 0) {
		this->explosion->setExplosion(Point::getRandomPoint(Screen::getPositionOfWorldCoordinate(Point(0, 0)), Screen::getPositionOfWorldCoordinate(Point(Screen::getWindowSize().width, Screen::getWindowSize().height))));
	}

	this->explosion->addDraw();
	this->clear_mes->addDraw();
}