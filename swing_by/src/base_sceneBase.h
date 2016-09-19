#ifndef _BASE_SCENEBASE_
#define _BASE_SCENEBASE_

#include "base_taskBase.h"
#include "interface_setNextScene.h"

class SceneBase : public TaskBase{
protected:
	ISetNextScene* sceneChanger;

public:
	SceneBase(ISetNextScene* changer){ this->sceneChanger = changer; }
	virtual ~SceneBase(){}
};

#endif