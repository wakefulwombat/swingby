#pragma once

#include "base_sceneBase.h"

class SceneOpening : public SceneBase {
private:

public:
	SceneOpening(ISetNextScene* isetNextScene);
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};