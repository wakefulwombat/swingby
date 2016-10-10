#include "scene_gameMainStage.h"
#include "screen.h"

SceneGameMainStage::SceneGameMainStage(const std::shared_ptr<ISetNextSceneInGameMain> &i) : SceneInGameMainBase(i) {
	this->player = std::make_shared<Player>();
	this->control_factory = std::make_shared<ControllerFactory>();
	this->mouse_pointer = std::make_shared<MousePointer>();
	this->map = std::make_shared<Map>("asset\\map\\map_001.csv");
	this->explosion_manager = std::make_shared<ExplosionManager>();
	this->orbit_manager = std::make_shared<OrbitManager>(this->player, this->player, this->mouse_pointer, this->map);

	this->player->setInterface(this->control_factory, this->orbit_manager->getCrossTarget(), this->orbit_manager);

	this->isGameOverNow = false;
	this->isPaused = false;
	this->scene_pause = std::make_shared<SceneGameMainStagePause>();
	this->scene_gameover = std::make_shared<SceneGameMainStageGameOver>();
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
	this->explosion_manager->update();

	if (this->isPaused) this->scene_pause->update();
	if (this->isGameOverNow) this->scene_gameover->update();

	this->hitCheck();
}

void SceneGameMainStage::finalize() {

}

void SceneGameMainStage::hitCheck() {
	if (this->map->isHitWithWall(this->player, this->player->getSize()*0.8)) {
		this->explosion_manager->setExplosion(this->player->getPosition());
		this->player->setInvalid();
	}
}