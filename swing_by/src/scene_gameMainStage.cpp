#include "scene_gameMainStage.h"

SceneGameMainStage::SceneGameMainStage(ISetNextSceneInGameMain* i) : SceneInGameMainBase(i) {
	this->control_factory = new ControllerFactory();
	this->player = std::unique_ptr<Player>(new Player(this->control_factory));
}

void SceneGameMainStage::initialize() {

}

void SceneGameMainStage::update() {
	this->player->update();
}

void SceneGameMainStage::finalize() {
	delete this->control_factory;
}