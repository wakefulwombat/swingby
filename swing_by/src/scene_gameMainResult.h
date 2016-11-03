#pragma once

#include "base_sceneInGameMainBase.h"
#include "base_sceneBase.h"
#include "mousePointer.h"
#include "score.h"
#include "message.h"
#include "map.h"
#include "button.h"
#include <vector>

class SceneGameMainResult : public SceneInGameMainBase {
private:
	std::shared_ptr<MousePointer> mouse_pointer;
	std::shared_ptr<Message> mes;
	std::vector<std::shared_ptr<MapChip>> box;
	std::vector<std::shared_ptr<Rank>> ranks;
	std::vector<std::shared_ptr<Button>> button;

	int count;
	int stageMax;

public:
	SceneGameMainResult(std::function<void(SceneInGameMainKind)> gameMainSceneChanger, std::function<void(SceneKind)> changer, ScoreResult result);
	void initialize() override;
	void update() override;
	void finalize() override;
};