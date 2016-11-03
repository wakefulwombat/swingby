#include "scene_gameMainResult.h"
#include "screen.h"
#include <fstream>
#include <sstream>

SceneGameMainResult::SceneGameMainResult(std::function<void(SceneInGameMainKind)> gameMainSceneChanger, std::function<void(SceneKind)> changer, ScoreResult result) : SceneInGameMainBase(gameMainSceneChanger) {
	this->count = 0;
	this->stageMax = stageMax;

	this->mouse_pointer = std::make_shared<MousePointer>();
	this->mes = std::make_shared<Message>(Point(150, 50), MessageType::RESULT);
	this->mes->setInvalid();

	this->box.push_back(std::make_shared<MapChip>(Point(32, 88), Size(32, 32), 18));
	this->box.push_back(std::make_shared<MapChip>(Point(928, 88), Size(32, 32), 19));
	this->box.push_back(std::make_shared<MapChip>(Point(32, 536), Size(32, 32), 17));
	this->box.push_back(std::make_shared<MapChip>(Point(928, 536), Size(32, 32), 16));
	for (int i = 1; i < 14; ++i) this->box.push_back(std::make_shared<MapChip>(Point(32 + 64 * i, 88), Size(32, 32), 2));
	for (int i = 1; i < 14; ++i) this->box.push_back(std::make_shared<MapChip>(Point(32 + 64 * i, 536), Size(32, 32), 0));
	for (int i = 1; i < 7; ++i) this->box.push_back(std::make_shared<MapChip>(Point(32, 88 + 64 * i), Size(32, 32), 1));
	for (int i = 1; i < 7; ++i) this->box.push_back(std::make_shared<MapChip>(Point(928, 88 + 64 * i), Size(32, 32), 3));

	this->ranks.push_back(std::make_shared<Rank>(Point(400, 180), result.goal_time));
	this->ranks.push_back(std::make_shared<Rank>(Point(750, 180), result.goal_speed));
	this->ranks.push_back(std::make_shared<Rank>(Point(400, 300), result.max_speed));
	this->ranks.push_back(std::make_shared<Rank>(Point(750, 300), result.swing_tech));
	this->ranks.push_back(std::make_shared<Rank>(Point(220, 420), result.total));
	for (auto it = this->ranks.begin(); it != this->ranks.end(); ++it) (*it)->setInvalid();

	this->button.push_back(std::make_shared<Button>(Point(500, 420), Size(200, 70), "ステージセレクト", 22, [gameMainSceneChanger]() {gameMainSceneChanger(SceneInGameMainKind::StageSelect); }));
	this->button.push_back(std::make_shared<Button>(Point(750, 420), Size(200, 70), "タイトル", 22, [changer]() {changer(SceneKind::Opening); }));
	for (auto it = this->button.begin(); it != this->button.end(); ++it) (*it)->setInvalid();
	this->button.push_back(std::make_shared<ButtonMove>(Point(250, 190), Size(200, 70), "タイム", 22, []() {}));
	this->button.push_back(std::make_shared<ButtonMove>(Point(600, 190), Size(200, 70), "スピード", 22, []() {}));
	this->button.push_back(std::make_shared<ButtonMove>(Point(250, 310), Size(200, 70), "マックス", 22, []() {}));
	this->button.push_back(std::make_shared<ButtonMove>(Point(600, 310), Size(200, 70), "スイング", 22, []() {}));
	

	Screen::initTargetPositionDeltaCenter(Point());
	Screen::setTargetWorldPosition(Point(Screen::getWindowSize().width / 2, Screen::getWindowSize().height * 3 / 2), 1);
	Screen::setZoomOut(1);
}

void SceneGameMainResult::initialize() {

}

void SceneGameMainResult::update() {
	this->count++;
	this->mouse_pointer->update();
	this->mes->update();
	for (auto it = this->box.begin(); it != this->box.end(); ++it) (*it)->update();
	for (auto it = this->ranks.begin(); it != this->ranks.end(); ++it) (*it)->update();
	for (auto it = this->button.begin(); it != this->button.end(); ++it) (*it)->update();

	if (this->count < 50) {
		Screen::setTargetWorldPosition(Point(Screen::getWindowSize().width / 2, Screen::getWindowSize().height * 3 / 2 - Screen::getWindowSize().height*this->count / 50), 1);
	}
	if (this->count == 50) this->mes->startShowing();
	for (int i = 0; i < 4; ++i) { if (this->count == 50 + 20 * i) this->ranks[i]->startShowing(3.0, 0.5, 30); }
	if (this->count == 150) this->ranks[4]->startShowing(4.0, 1.0, 60);

	if(this->count==240) { for (auto it = this->button.begin(); it != this->button.end(); ++it) (*it)->setValid(); }
}

void SceneGameMainResult::finalize() {

}