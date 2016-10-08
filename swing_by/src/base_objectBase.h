#pragma once

#include "common.h"
#include "base_requiredFunc.h"
#include "base_externalObjectControllerBase.h"
#include "base_internalObjectControllerBase.h"
#include <memory>

enum class ControlStatus{
	None,//制御なし
	Movable,//自律移動可能
	InternalControlled,//自律移動不可、内部自動制御(制限解除は条件により制御可能)
	ExternalControlled//自律移動不可、外部制御(制限解除は外部が行う)
};

//移動属性
class MoveObjectProperty{
protected:
	//for moving
	double trans_vel, trans_acc, trans_rad, trans_omega;//直進運動
	double rotate_vel, rotate_acc, rotate_rad, rotate_omega;//回転運動

public:
	virtual ~MoveObjectProperty(){}
	double getTransVelNorm() { return this->trans_vel; }
	Point getTransVelVec() { return Point(this->trans_vel*cos(this->trans_rad), this->trans_vel*sin(this->trans_rad)); }
	double getTransRad() { return this->trans_rad; }
	double getRotateVel() { return this->rotate_vel; }
	double getRotateRad() { return this->rotate_rad; }
};

//アニメーション属性
class AnimationObjectProperty{
protected:
	int chip_switch_time;//キャラチップのアニメーション時間間隔
	int chip_count;//キャラチップ用カウンタ
	int show_chip_index;//表示するキャラチップ番号
	bool repeat;//アニメーションを繰り返すか
	int chipSize;//アニメーションチップの個数

public:
	virtual ~AnimationObjectProperty(){}

	bool isChipSwitchTime() { return (this->chip_count%this->chip_switch_time == 0); }
	bool isRepeatable() { return this->repeat; }
};

class ObjectBase : public RequiredFunc, public ExternalObjectControllerBase, public std::enable_shared_from_this<ObjectBase> {
protected:
	Point position;
	Size size;
	bool validation;
	int count;
	
	ControlStatus control_status;//制御権
	std::shared_ptr<InternalObjectController> internalController;//内部制御用

	//for image
	double expansion;//画像拡大率
	double img_rotation;//画像回転角度
	double img_opacity;//画像透明度(0.0~1.0)

	unsigned int z_sort;//zソート

public:
	ObjectBase();
	ObjectBase(Point pos, Size size);
	virtual ~ObjectBase(){}

	Point getPosition(){ return this->position; }
	Size getSize() { return this->size*this->expansion; }
	bool getValidation(){ return this->validation; }
	double getExpansion(){ return this->expansion; }
	double getImageRotationRad(){ return this->img_rotation; }

	unsigned int getZSort() { return this->z_sort; }

	//外部操作用
	void setInvalid() override final { this->validation = false; }
	void setControlRights(ControlStatus status) override final { this->control_status = status; }
	void setPosition(Point pos) { this->position = pos; }
	void setImageRotationRad(double rad) { this->img_rotation = rad; }
	void setImageOpacity(double opacity) { this->img_opacity = opacity; }//0.0~1.0

	virtual void draw() const = 0;
};
