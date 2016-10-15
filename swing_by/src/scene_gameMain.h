#pragma once

#include "base_sceneBase.h"
#include "base_sceneInGameMainBase.h"
#include <memory>

class SceneGameMain : public SceneBase, public std::enable_shared_from_this<SceneGameMain>{
private:
	//ゲームメイン内でのシーンチェンジ
	SceneInGameMainKind nextSceneInGameMain;
	std::shared_ptr<SceneInGameMainBase> nowSceneInGameMain;

	std::function<void(SceneKind)> sceneChanger;

public:
	SceneGameMain(std::function<void(SceneKind)> changer);
	void initialize() override;
	void update() override;
	void finalize() override;
};