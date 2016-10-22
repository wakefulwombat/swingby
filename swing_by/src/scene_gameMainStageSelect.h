#pragma once

#include "base_sceneInGameMainBase.h"
#include "button.h"
#include "mousePointer.h"
#include <vector>
#include <memory>

class SceneGameMainStageSelect : public SceneInGameMainBase {
private:
	std::function<void(int)> setSelectStage;
	std::vector<std::shared_ptr<ButtonMove>> buttons;
	std::shared_ptr<Button> button_go;
	std::shared_ptr<MousePointer> mouse_pointer;

public:
	SceneGameMainStageSelect(std::function<void(SceneInGameMainKind)> sceneChanger, std::function<void(int)> setSelectStage);
	void initialize() override;
	void update() override;
	void finalize() override;

	void offButtonInsteadOfIndex(int index);
};