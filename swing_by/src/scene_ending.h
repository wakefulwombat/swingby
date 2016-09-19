#pragma once

#include "base_sceneBase.h"

class SceneEnding : public SceneBase {
private:

public:
	SceneEnding(ISetNextScene* isetNextScene);
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};