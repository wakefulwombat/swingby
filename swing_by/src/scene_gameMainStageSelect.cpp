#include "scene_gameMainStageSelect.h"
#include "screen.h"
#include "input.h"
#include <fstream>
#include <sstream>

SceneGameMainStageSelect::SceneGameMainStageSelect(std::function<void(SceneInGameMainKind)> sceneChanger, std::function<void(SceneKind)> backToTitle, std::function<void(int)> setSelectStage) : SceneInGameMainBase(sceneChanger) {
	this->setSelectStage = setSelectStage;
	this->backToTitle = backToTitle;

	this->stageMax = 3;
	this->selectedStage = 0;
	this->loadHighScore();

	for (int i = 0; i < this->stageMax; ++i) {
		int x = i % 4;
		int y = (i - x) / 4;
		this->buttons.push_back(std::make_shared<ButtonMove>(Point(90 + x * 150, 300 + y * 110), Size(140, 100), "STAGE " + std::to_string(i + 1), 20, [setSelectStage, i, this]() {offButtonInsteadOfIndex(i);  setSelectStage(i); selectedStage = i; }));
	}
	this->buttons[0]->clicked();
	this->button_go = std::make_shared<Button>(Point(800, 450), Size(180, 80), "スタート", 20, [sceneChanger]() {sceneChanger(SceneInGameMainKind::Stage); });

	this->mouse_pointer = std::make_shared<MousePointer>();

	if (this->highscore_list[this->selectedStage] == -1) {
		this->highscore = std::make_shared<Rank>(Point(500, 300), ScoreRank::S);
		this->highscore->startShowing(0.5, 0.5, 1);
		this->highscore->setInvalid();
	}
	else {
		this->highscore = std::make_shared<Rank>(Point(800, 300), (ScoreRank)this->highscore_list[this->selectedStage]);
		this->highscore->startShowing(0.8, 0.8, 1);
	}

	Screen::initTargetPositionDeltaCenter(Point());
	Screen::setTargetWorldPosition(Point(Screen::getWindowSize().width / 2, Screen::getWindowSize().height / 2), 1);
	Screen::setStageSize(Size(960, 1050));
	Screen::setZoomOut(1);
}

void SceneGameMainStageSelect::initialize() {

}

void SceneGameMainStageSelect::update() {
	this->mouse_pointer->update();
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) (*it)->update();
	this->button_go->update();

	if (this->highscore_list[this->selectedStage] != -1) {
		this->highscore->changeType((ScoreRank)this->highscore_list[this->selectedStage]);
		this->highscore->update();
	}

	//if (Input::getMouseWheelRotation() != 0)Screen::addTargetWorldPositionDelta(Point(0, -100)*Input::getMouseWheelRotation(), 10);
	if (Input::getKeyCodeDownOnce(KeyType::Game_VectorTrans_CANCEL)) this->backToTitle(SceneKind::Opening);
}

void SceneGameMainStageSelect::finalize() {

}

void SceneGameMainStageSelect::offButtonInsteadOfIndex(int index) {
	for (unsigned int i = 0; i < this->buttons.size(); ++i) {
		if (i == index) continue;
		this->buttons[i]->off();
	}
}

void SceneGameMainStageSelect::loadHighScore() {
	std::ifstream ifs("asset\\highscore.dat");
	if (!ifs) return;

	std::string str;
	for (int i = 0; i < this->stageMax; ++i) {
		std::getline(ifs, str);
		std::string score;
		std::istringstream stream(str);
		
		getline(stream, score, ',');
		this->highscore_list.push_back(std::stoi(score));
	}
}