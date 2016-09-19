#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	//SetUseDXArchiveFlag(TRUE);
	//SetDXArchiveExtension("dat");

	//if (MessageBox(NULL, "�t���X�N���[���ŋN�����܂����H", "�N���I�v�V����", MB_YESNO) == IDYES){
	//ChangeWindowMode(0);
	//}
	//else{
	ChangeWindowMode(1);
	//}
	

	SetGraphMode(640, 480, 16);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetWindowText("Swing By");


	if (DxLib_Init() == -1) return -1;


	SetDrawScreen(DX_SCREEN_BACK);


	while (1) {
		ClearDrawScreen();


		ScreenFlip();

		if (ProcessMessage() == -1) break;
	}


	//#ifndef _DEBUG
	DxLib_End();
	//#endif
	return 0;
}