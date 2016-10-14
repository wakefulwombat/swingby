#include "scene_gameMainStageGameOver.h"

SceneGameMainStageGameOver::SceneGameMainStageGameOver(std::function<void(void)> retry, std::function<void(void)> title) {
	this->btn_mgr = std::make_shared<ButtonManager>();
	this->btn_mgr->setNewButton(Point(150, 300), Size(80, 30), "リトライ", 18, [retry]() {retry(); });
	this->btn_mgr->setNewButton(Point(500, 300), Size(80, 30), "タイトルへ", 18, [title]() {title(); });
}

void SceneGameMainStageGameOver::initialize() {

}

void SceneGameMainStageGameOver::update() {

}

void SceneGameMainStageGameOver::finalize() {

}