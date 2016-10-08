#pragma once

#include "common.h"
#include "base_objectBase.h"
#include "interface_getCrossPosition.h"
#include <vector>
#include <memory>

class CrossTarget : public ObjectBase {
private:
	double target_spin[3];
	std::shared_ptr<ObjectBase> player;
	std::shared_ptr<ObjectBase> mouse_pointer;
	std::shared_ptr<IGetCrossPosition> map;

public:
	CrossTarget(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetCrossPosition> &map);
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};

class OrbitPoint : public ObjectBase {
private:

public:
	OrbitPoint();
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};

class Orbit : public RequiredFunc{
private:
	std::shared_ptr<CrossTarget> crossTarget;
	std::vector<std::shared_ptr<OrbitPoint>> orbit;
	std::vector<std::shared_ptr<OrbitPoint>> line;

	std::shared_ptr<ObjectBase> mouse_pointer;
	std::shared_ptr<ObjectBase> player;

public:
	Orbit(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetCrossPosition> &map);
	void initialize() override;
	void update() override;
	void finalize() override;
};