#ifndef _INTERFACE_SETNEXTSCENE_
#define _INTERFACE_SETNEXTSCENE_

enum class SceneKind;

class ISetNextScene{
public:
	virtual ~ISetNextScene(){}
	virtual void setNextScene(SceneKind kind) = 0;
};

#endif