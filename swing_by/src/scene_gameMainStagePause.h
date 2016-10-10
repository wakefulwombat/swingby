#pragma once

#include "base_requiredFunc.h"

class SceneGameMainStagePause : public RequiredFunc {
private:

public:
	SceneGameMainStagePause();
	void initialize() override;
	void update() override;
	void finalize() override;
};