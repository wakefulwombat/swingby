#include "scene_gameMainStage.h"
#include "screen.h"
#include "input.h"

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
	if (this->isPaused) {
		this->player->addDraw();
		this->mouse_pointer->update();
		this->map->addDraw();
		this->orbit_manager->addDraw();
		this->explosion_manager->addDraw();

		this->scene_pause->update();
	}
	else if (this->isGameOverNow) {
		this->mouse_pointer->update();
		this->map->update();
		this->explosion_manager->update();
		
		this->scene_gameover->update();
	}
	else {
		this->player->update();
		this->mouse_pointer->update();
		this->map->update();
		this->orbit_manager->update();
		this->explosion_manager->update();

		this->hitCheck();
	}

	if (Input::getKeyCodeDownOnce(KeyType::Common_Pause)) {
		this->isPaused = !this->isPaused;
	}
}

void SceneGameMainStage::finalize() {

}

void SceneGameMainStage::hitCheck() {
	if (this->map->isHitWithWall(this->player, 20.0)) {
		this->explosion_manager->setExplosion(this->player->getPosition());
		this->player->setInvalid();
		this->isGameOverNow = true;
	}
}