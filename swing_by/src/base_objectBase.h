#pragma once

#include "common.h"
#include "base_requiredFunc.h"
#include "base_externalObjectControllerBase.h"
#include "base_internalObjectControllerBase.h"
#include <memory>

enum class ControlStatus{
	Movable,//自律移動可能
	InternalControled,//自律移動不可、内部自動制御(制限解除は条件により制御可能)
	ExternalControled//自律移動不可、外部制御(制限解除は外部が行う)
};

//移動属性
class MoveObjectProperty{
protected:
	//for moving
	double trans_vel, trans_acc, trans_rad, trans_omega;//直進運動
	double rotate_vel, rotate_acc, rotate_rad, rotate_omega;//回転運動
	double gravity_move;//重力による落下移動量

public:
	virtual ~MoveObjectProperty(){}
};

//アニメーション属性
class AnimationObjectProperty{
protected:
	int chip_switch_time;//キャラチップのアニメーション時間間隔
	int chip_count;//キャラチップ用カウンタ
	bool repeat;//アニメーションを繰り返すか
	int chipSize;//アニメーションチップの個数

public:
	virtual ~AnimationObjectProperty(){}
};

class ObjectBase : public RequiredFunc, public ExternalObjectControllerBase{
protected:
	Point position;
	Size size;
	bool validation;
	int count;
	
	ControlStatus control_status;//制御権
	std::unique_ptr<InternalObjectController> internalController;//内部制御用

	//for image
	double expansion;//画像拡大率
	double img_rotation;//画像回転角度

	unsigned int z_sort;//zソート

public:
	virtual ~ObjectBase(){};

	Point getPosition(){ return this->position; };
	Size getSize(){ return this->size; };
	bool getValidation(){ return this->validation; };
	double getExpansion(){ return this->expansion; }
	double getImageRotationRad(){ return this->img_rotation; }

	//外部操作用
	void setInvalid() override final { this->validation = false; }
	void setControlRights(ControlStatus status) override final { this->control_status = status; }

	bool operator<(const ObjectBase* obj){ return this->z_sort < obj->z_sort; }

	virtual void draw() const = 0;
};
