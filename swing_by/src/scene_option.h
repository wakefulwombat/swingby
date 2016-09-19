#pragma once

#include "base_sceneBase.h"

class SceneOption : public SceneBase {
private:

public:
	SceneOption(ISetNextScene* isetNextScene);
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};