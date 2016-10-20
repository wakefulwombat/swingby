#include "scene_gameMainResult.h"
#include "screen.h"

SceneGameMainResult::SceneGameMainResult(std::function<void(SceneInGameMainKind)> sceneChanger, const ScoreResult result) : SceneInGameMainBase(sceneChanger), result(result) {
	this->count = 0;

	this->mouse_pointer = std::make_shared<MousePointer>();

	Screen::initTargetPositionDeltaCenter(Point());
	Screen::setTargetWorldPosition(Point(Screen::getWindowSize().width / 2, Screen::getWindowSize().height * 3 / 2), 1);
}

void SceneGameMainResult::initialize() {

}

void SceneGameMainResult::update() {
	this->count++;
	this->mouse_pointer->update();

	if (this->count < 100) {
		Screen::setTargetWorldPosition(Point(Screen::getWindowSize().width / 2, Screen::getWindowSize().height * 3 / 2 - Screen::getWindowSize().height*this->count / 100), 1);
	}
}

void SceneGameMainResult::finalize() {

}