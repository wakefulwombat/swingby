#pragma once

#include "common.h"
#include "base_objectBase.h"
#include "debug.h"
#include <vector>
#include <string>
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
	static void addTargetWorldPositionDelta(Point delta, int time);
	static void setStageSize(Size size);

	static void setZoomIn(double zoom_max, int zoomin_count_max);
	static void setZoomOut(int zoomout_count_max);
	static void setSway(double intensity, int count_max);

	static void drawMutable(Point center_pos, Size size, int graphHandle, double expansion, double rotation, bool turn, double opacity);
	static void drawMutable(Point center_pos, Size size, int graphHandle, double expansion_x, double expansion_y, double rotation, bool turn, double opacity);
	static void drawOnWindow(Point center_pos, Size size, int graphHandle, double expansion, double rotation, double opacity);
	static void drawOnWindowForMouse(Point leftup_pos, int graphHandle, double opacity);
	
	static void drawSquare(Point center_pos, Size size, Color color, bool fill = true);
	static void drawLine(Point start, Point end, Color color);
	static void drawPoint(Point center, int r, Color color, bool fill = true);
	static void drawString(Point center, Color color, std::string text, int font_size);

	//static void drawSquareFixSize(Point center_pos, Size size, Color color, bool fill = true);
	//static void drawStringFixSize(Point center, Color color, std::string text, int font_size);
	static void drawSquareOnWindow(Point center_pos, Size size, Color color, bool fill = true);
	static void drawStringOnWindow(Point center, Color color, std::string text, int font_size);

	static void init(int window_width, int window_height);
	static void update();

	static void drawAll();
	static void addDrawObjectMutable(const std::shared_ptr<ObjectBase> &obj);
	static void addDrawObjectWindow(const std::shared_ptr<ObjectBase> &obj);

	static Size getWindowSize(){ return Screen::windowSize; }
	static Point getPositionOfWindowCoordinate(Point world_pos) { return world_pos - Screen::window_center_world_pos + Screen::windowSize / 2; }
	static Point getPositionOfWorldCoordinate(Point window_pos) { return window_pos + Screen::window_center_world_pos - Screen::windowSize / 2; }
	static Point toWindowPosPxFromWorldPos(Point world_pos) { return ((world_pos - Screen::window_center_world_pos)*Screen::zoom + Screen::windowSize / 2); }
	static Point toWorldPosFromWindowPosPx(Point window_pos) { return (Screen::window_center_world_pos + (window_pos - Screen::windowSize / 2) / Screen::zoom); }

	static bool isVisible(const std::shared_ptr<ObjectBase> &obj);
	static bool isVisiblePoint(Point pos);
};
