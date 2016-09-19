#pragma once

#include "base_sceneBase.h"

class SceneGameMainPause : public SceneBase {
private:

public:
	SceneGameMainPause(ISetNextScene* isetNextScene);
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};