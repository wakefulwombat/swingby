#pragma once

class ISetSceneGameMainStageStatus {
public:
	virtual ~ISetSceneGameMainStageStatus() {};
	virtual void enablePauseScene() = 0;
	virtual void enableGameOverScene() = 0;
};