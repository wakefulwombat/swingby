#pragma once

#include "common.h"
#include "base_objectBase.h"
#include <vector>
#include <memory>

class Screen{
private:
	static Size windowSize, stageSize;
	static Point window_center_world_pos;
	static Point target_pos_delta;
	static double zoom;
	static Point sway;
	static std::vector<std::shared_ptr<ObjectBase>> draw_list;

	static int move_count, move_count_max;
	static Point tergetPosition_start, tergetPosition_goal;

	static int zoom_count, zoom_count_max;
	static double zoom_magnification_start, zoom_magnification_end;

	static int sway_count, sway_count_max;
	static double sway_intensity_max;

public:
	static void initTargetPositionDeltaCenter(Point delta);
	static void setTargetWorldPosition(Point target, int time);
	static void setStageSize(Size size);

	static void setZoomIn(double zoom_max, int zoomin_count_max);
	static void setZoomOut(int zoomout_count_max);
	static void setSway(double intensity, int count_max);

	static void drawMutable(Point center_pos, Size size, int graphHandle, double expansion, double rotation, bool turn, double opacity);
	static void drawMutable(Point center_pos, Size size, int graphHandle, double expansion_x, double expansion_y, double rotation, bool turn, double opacity);
	static void drawOnWindow(Point center_pos, Size size, int graphHandle, double expansion, double rotation, double opacity);
	static void drawOnWindowForMouse(Point leftup_pos, int graphHandle, double opacity);

	static void init(int window_width, int window_height);
	static void update();

	static void drawAll();
	static void addDrawObjectMutable(const std::shared_ptr<ObjectBase> &obj);
	static void addDrawObjectWindow(const std::shared_ptr<ObjectBase> &obj);

	static Size getWindowSize(){ return Screen::windowSize; }
	static Point getPositionOfWindowCoordinate(Point pos) { return pos - Screen::window_center_world_pos; }

	static bool isVisible(const std::shared_ptr<ObjectBase> &obj);
};
