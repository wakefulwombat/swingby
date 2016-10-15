#include "scene_gameMainStage.h"
#include "screen.h"
#include "input.h"

SceneGameMainStage::SceneGameMainStage(std::function<void(SceneInGameMainKind)> gameMainSceneChanger, std::function<void(SceneKind)> changer) : SceneInGameMainBase(gameMainSceneChanger) {
	this->player = std::make_shared<Player>();
	this->control_factory = std::make_shared<ControllerFactory>();
	this->mouse_pointer = std::make_shared<MousePointer>();
	this->map = std::make_shared<Map>("asset\\map\\map_001.csv");
	this->explosion_manager = std::make_shared<ExplosionManager>();
	this->orbit_manager = std::make_shared<OrbitManager>(this->player, this->player, this->mouse_pointer, this->map);
	this->timer = std::make_shared<Timer>();

	this->player->setInterface(this->control_factory, this->orbit_manager->getCrossTarget(), this->orbit_manager, this->mouse_pointer->shared_from_this());

	this->isGameOverNow = false;
	this->isPaused = false;
	this->scene_pause = std::make_shared<SceneGameMainStagePause>([this]() {isPaused = false; }, [gameMainSceneChanger]() {gameMainSceneChanger(SceneInGameMainKind::Stage); }, [changer]() {changer(SceneKind::Opening); });
	this->scene_gameover = std::make_shared<SceneGameMainStageGameOver>([gameMainSceneChanger]() {gameMainSceneChanger(SceneInGameMainKind::Stage); }, [changer]() {changer(SceneKind::Opening); });
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
		this->timer->addDraw();

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
		this->timer->update();

		this->hitCheck();
		if (Input::getKeyCodeDownOnce(KeyType::Common_Pause)) {
			this->enablePauseScene();
		}
	}
}

void SceneGameMainStage::finalize() {

}

void SceneGameMainStage::hitCheck() {
	if (this->map->isHitWithWall(this->player, 12.0)) {
		this->explosion_manager->setExplosion(this->player->getPosition());
		this->player->setInvalid();
		this->enableGameOverScene();
		if (!this->mouse_pointer->getValidation()) this->mouse_pointer->rememberShow();
	}
	if (this->map->isInGoalArea(this->player)) {
		this->player->setInvalid();
		this->timer->setInvalid();
		if (!this->mouse_pointer->getValidation()) this->mouse_pointer->rememberShow();
	}
}