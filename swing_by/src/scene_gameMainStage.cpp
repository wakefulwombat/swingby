#include "scene_gameMainStage.h"
#include "screen.h"

SceneGameMainStage::SceneGameMainStage(ISetNextSceneInGameMain* i) : SceneInGameMainBase(i) {
	this->control_factory = new ControllerFactory();
	this->mouse_pointer = std::shared_ptr<MousePointer>(new MousePointer());
	this->player = std::shared_ptr<Player>(new Player(this->control_factory, this->mouse_pointer));
	this->map = std::shared_ptr<Map>(new Map("asset\\map\\map_001.csv"));
}

void SceneGameMainStage::initialize() {
	this->player->initialize(this->map->getStartPosition());
	Screen::setStageSize(this->map->getStageSize());
}

void SceneGameMainStage::update() {
	this->player->update();
	this->mouse_pointer->update();
	this->map->update();
}

void SceneGameMainStage::finalize() {
	delete this->control_factory;
}