#pragma once

#include "base_requiredFunc.h"

class SceneGameMainStageGameOver : public RequiredFunc {
private:

public:
	SceneGameMainStageGameOver();
	void initialize() override;
	void update() override;
	void finalize() override;
};