#include "scene_gameMainStageClear.h"
#include "screen.h"
#include "input.h"

SceneGameMainStageClear::SceneGameMainStageClear(std::function<void(void)> sceneChanger, std::function<void(Point)> setExplosion) {
	this->sceneChanger = sceneChanger;
	this->setExplosion = setExplosion;

	this->clear_mes = std::make_shared<Message>(Point(Screen::getWindowSize().width / 2, Screen::getWindowSize().height / 3), MessageType::STAGECLEAR);
	this->count = 0;
}

void SceneGameMainStageClear::update() {
	this->count++;

	if (this->count > 300) {
		this->sceneChanger();
	}
	if (Input::getKeyCodeDownOnce(KeyType::Game_Swing_OK)) {
		this->sceneChanger();
	}

	if (this->count % 3 == 0) {
		this->setExplosion(Point::getRandomPoint(Screen::getPositionOfWorldCoordinate(Point(0, 0)), Screen::getPositionOfWorldCoordinate(Point(Screen::getWindowSize().width, Screen::getWindowSize().height))));
	}

	this->clear_mes->addDraw();
}