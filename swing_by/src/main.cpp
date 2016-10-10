#include "DxLib.h"
#include "input.h"
#include "screen.h"
#include "image.h"
#include "scene_manager.h"
#include <memory>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	//SetUseDXArchiveFlag(TRUE);
	//SetDXArchiveExtension("dat");

	//if (MessageBox(NULL, "フルスクリーンで起動しますか？", "起動オプション", MB_YESNO) == IDYES){
	//ChangeWindowMode(0);
	//}
	//else{
	ChangeWindowMode(1);
	//}
	

	SetGraphMode(960, 540, 16);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetWindowText("Swing By");

	if (DxLib_Init() == -1) return -1;
	SetMouseDispFlag(false);

	SetDrawScreen(DX_SCREEN_BACK);

	Input::init();
	Screen::init(960, 540);
	Image::loadGameScene();
	std::shared_ptr<SceneManager> mgr = std::make_shared<SceneManager>();
	mgr->initialize();

	while (1) {
		ClearDrawScreen();
		
		Input::keyUpdate();
		mgr->update();
		Screen::update();
		
		Screen::drawAll();
		ScreenFlip();

		if (ProcessMessage() == -1) break;
	}
	mgr->finalize();

	//#ifndef _DEBUG
	DxLib_End();
	//#endif
	return 0;
}