#pragma once

#include "base_sceneInGameMainBase.h"
#include "mousePointer.h"
#include "score.h"

class SceneGameMainResult : public SceneInGameMainBase {
private:
	std::shared_ptr<MousePointer> mouse_pointer;

	const ScoreResult result;
	int count;

public:
	SceneGameMainResult(std::function<void(SceneInGameMainKind)> sceneChanger, const ScoreResult result);
	void initialize() override;
	void update() override;
	void finalize() override;
};