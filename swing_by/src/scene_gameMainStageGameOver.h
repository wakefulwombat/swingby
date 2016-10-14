#pragma once

#include "base_requiredFunc.h"
#include "button.h"
#include <memory>
#include <functional>

class SceneGameMainStageGameOver : public RequiredFunc {
private:
	std::shared_ptr<ButtonManager> btn_mgr;

public:
	SceneGameMainStageGameOver(std::function<void(void)> retry, std::function<void(void)> title);
	void initialize() override;
	void update() override;
	void finalize() override;
};