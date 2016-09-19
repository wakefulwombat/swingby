#pragma once

#include "base_sceneInGameMainBase.h"
#include "base_objectBase.h"
#include <vector>
#include <memory>

class SceneGameMainStage : public SceneInGameMainBase {
private:
	std::vector<std::unique_ptr<ObjectBase>> objects;

public:
	SceneGameMainStage(ISetNextSceneInGameMain* isetNextScene);
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};