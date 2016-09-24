#pragma once

#include "common.h"
#include "base_objectBase.h"
#include <vector>

class Screen{
private:
	static Size windowSize, stageSize;
	static Point center;
	static double zoom;
	static Point sway;
	static std::vector<ObjectBase*> draw_list;

	static int center_move_count, center_move_count_max;
	static Point centerTergetPosition_start, centerTergetPosition_goal;

	static int zoom_count, zoom_count_max;
	static double zoom_magnification_start, zoom_magnification_end;

	static int sway_count, sway_count_max;
	static double sway_intensity_max;

public:
	static void setCenterTargetPosition(Point target, int count_max);
	static void setZoomIn(double zoom_max, int zoomin_count_max);
	static void setZoomOut(int zoomout_count_max);
	static void setSway(double intensity, int count_max);

	static void drawMutable(Point center_pos, Size size, int graphHandle, double expansion, double rotation, bool turn);
	static void drawMutable(Point center_pos, Size size, int graphHandle, double expansion_x, double expansion_y, double rotation, bool turn);
	static void drawOnWindow(Point center_pos, Size size, int graphHandle, double expansion, double rotation);
	static void drawOnWindowForMouse(Point leftup_pos, int graphHandle);

	static void init(int window_width, int window_height);
	static void update();

	static void drawAll();
	static void addDrawObject(ObjectBase* obj);

	static Size getWindowSize(){ return Screen::windowSize; }
	static Point getPositionOfWindowCoordinate(Point pos) { return pos - Screen::center; }
};
