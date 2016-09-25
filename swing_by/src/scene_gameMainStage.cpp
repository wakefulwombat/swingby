#include "scene_gameMainStage.h"

SceneGameMainStage::SceneGameMainStage(ISetNextSceneInGameMain* i) : SceneInGameMainBase(i) {
	this->control_factory = new ControllerFactory();
	this->player = std::unique_ptr<Player>(new Player(this->control_factory));
	this->mouse_pointer = std::unique_ptr<MousePointer>(new MousePointer());
	this->map = std::unique_ptr<Map>(new Map("asset\\map\\map_001.csv"));
}

void SceneGameMainStage::initialize() {
	this->player->initialize(this->map->getStartPosition());
}

void SceneGameMainStage::update() {
	this->player->update();
	this->mouse_pointer->update();
	this->map->update();
}

void SceneGameMainStage::finalize() {
	delete this->control_factory;
}