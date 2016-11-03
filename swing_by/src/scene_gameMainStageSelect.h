#pragma once

#include "base_sceneInGameMainBase.h"
#include "scene_manager.h"
#include "button.h"
#include "mousePointer.h"
#include "score.h"
#include "message.h"
#include <vector>
#include <memory>

class SceneGameMainStageSelect : public SceneInGameMainBase {
private:
	std::function<void(int)> setSelectStage;
	std::function<void(SceneKind)> backToTitle;
	std::vector<std::shared_ptr<ButtonMove>> buttons;
	std::shared_ptr<Button> button_go;
	std::shared_ptr<MousePointer> mouse_pointer;

	std::vector<int> highscore_list;
	std::shared_ptr<Rank> highscore;

	int stageMax, selectedStage;
	void loadHighScore();

public:
	SceneGameMainStageSelect(std::function<void(SceneInGameMainKind)> sceneChanger, std::function<void(SceneKind)> backToTitle, std::function<void(int)> setSelectStage);
	void initialize() override;
	void update() override;
	void finalize() override;

	void offButtonInsteadOfIndex(int index);
};