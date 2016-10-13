#pragma once

#include "base_requiredFunc.h"
#include "button.h"
#include <memory>
#include <functional>

class SceneGameMainStagePause : public RequiredFunc {
private:
	std::shared_ptr<ButtonManager> btn_mgr;
	std::function<void(void)> de_pause;

public:
	SceneGameMainStagePause(std::function<void(void)> de_pause);
	void initialize() override;
	void update() override;
	void finalize() override;
};