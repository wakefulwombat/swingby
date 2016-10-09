#include "scene_gameMainStage.h"
#include "screen.h"

SceneGameMainStage::SceneGameMainStage(const std::shared_ptr<ISetNextSceneInGameMain> &i) : SceneInGameMainBase(i) {
	this->control_factory = std::make_shared<ControllerFactory>();
	this->mouse_pointer = std::make_shared<MousePointer>();
	this->player = std::make_shared<Player>(this->control_factory, this->mouse_pointer);
	this->map = std::make_shared<Map>("asset\\map\\map_001.csv");
	this->orbit_manager = std::make_shared<OrbitManager>(this->player, this->player, this->mouse_pointer, this->map);
}

void SceneGameMainStage::initialize() {
	this->player->initialize(this->map->getStartPosition());
	Screen::setStageSize(this->map->getStageSize());
}

void SceneGameMainStage::update() {
	this->player->update();
	this->mouse_pointer->update();
	this->map->update();
	this->orbit_manager->update();
}

void SceneGameMainStage::finalize() {

}