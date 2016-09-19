#include "input.h"
#include "DxLib.h"
#include <stdio.h>
#include <math.h>

bool Input::joyPadflag=false;
RegistedKeyCode Input::registedKeyCode;
KeyCodeState Input::keyCodeDownCount;
KeyCodeState Input::keyCodeUpCount;

int Input::keyState_DirectionCountX[2];
int Input::keyState_DirectionCountY[2];
int Input::keyState_DirectionSlopeX[2];
int Input::keyState_DirectionSlopeY[2];


bool Input::fileExistT(char* filepath){
	FILE* fp;
	if ((fopen_s(&fp, filepath, "r")) != 0){
		return false;
	}
	fclose(fp);
	return true;
}

bool Input::fileExistB(char* filepath){
	FILE* fp;
	if ((fopen_s(&fp, filepath, "rb")) != 0){
		return false;
	}
	fclose(fp);
	return true;
}

void Input::init(){
	if(Input::fileExistB("config.dat")==true){
		FILE* fp;
		fopen_s(&fp, "config.dat", "rb");

		fread(&Input::registedKeyCode, sizeof(RegistedKeyCode), 1, fp);

		fclose(fp);
	}
	else{
		Input::registedKeyCode.joyPad[(int)KeyType::Common_OK] = PAD_INPUT_1;
		Input::registedKeyCode.joyPad[(int)KeyType::Common_Cancel] = PAD_INPUT_2;
		Input::registedKeyCode.joyPad[(int)KeyType::Common_Pause] = PAD_INPUT_8;


		Input::registedKeyCode.keyBoard[(int)KeyType::Common_OK] = KEY_INPUT_Z;
		Input::registedKeyCode.keyBoard[(int)KeyType::Common_Cancel] = KEY_INPUT_X;
		Input::registedKeyCode.keyBoard[(int)KeyType::Common_Pause] = KEY_INPUT_P;
	}

	if (GetJoypadNum() == 0) Input::joyPadflag = false;
	else Input::joyPadflag = true;
}

bool Input::getJoyPadFlag(){
	return Input::joyPadflag;
}

void Input::writeNewKeyConfig(){
	FILE* fp;
	fopen_s(&fp, "config.dat", "wb");

	fwrite(&Input::registedKeyCode, sizeof(RegistedKeyCode), 1, fp);

	fclose(fp);
}

void Input::keyUpdate(){
	if(Input::joyPadflag==true){//ゲームパッド
		int joyInput = GetJoypadInputState(DX_INPUT_PAD1);
		
		for (int i = 0; i < 13; i++){
			if ((joyInput&Input::registedKeyCode.joyPad[i]) == 0){
				Input::keyCodeUpCount.joyPad[i]++;
				Input::keyCodeDownCount.joyPad[i] = 0;
			}
			else{
				Input::keyCodeUpCount.joyPad[i] = 0;
				Input::keyCodeDownCount.joyPad[i]++;
			}
		}


		DINPUT_JOYSTATE input;
		GetJoypadDirectInputState( DX_INPUT_PAD1, &input ) ;
		Input::keyState_DirectionSlopeX[(int)LeftRight::Left] = input.X;
		Input::keyState_DirectionSlopeY[(int)LeftRight::Left] = input.Y;
		Input::keyState_DirectionSlopeX[(int)LeftRight::Left] = input.Rx;
		Input::keyState_DirectionSlopeY[(int)LeftRight::Left] = input.Ry;

		if(input.X<=-400){
			if (Input::keyState_DirectionCountX[(int)LeftRight::Left]>0) Input::keyState_DirectionCountX[(int)LeftRight::Left] = 0;
			Input::keyState_DirectionCountX[(int)LeftRight::Left]--;
		}
		else if(input.X>=400){
			if (Input::keyState_DirectionCountX[(int)LeftRight::Left]<0) Input::keyState_DirectionCountX[(int)LeftRight::Left] = 0;
			Input::keyState_DirectionCountX[(int)LeftRight::Left]++;
		}
		else{
			Input::keyState_DirectionCountX[(int)LeftRight::Left] = 0;
		}

		if (input.Rx <= -400){
			if (Input::keyState_DirectionCountX[(int)LeftRight::Right]>0) Input::keyState_DirectionCountX[(int)LeftRight::Right] = 0;
			Input::keyState_DirectionCountX[(int)LeftRight::Right]--;
		}
		else if (input.Rx >= 400){
			if (Input::keyState_DirectionCountX[(int)LeftRight::Right]<0) Input::keyState_DirectionCountX[(int)LeftRight::Right] = 0;
			Input::keyState_DirectionCountX[(int)LeftRight::Right]++;
		}
		else{
			Input::keyState_DirectionCountX[(int)LeftRight::Right] = 0;
		}

		if (input.Y <= -400){
			if (Input::keyState_DirectionCountY[(int)LeftRight::Left]>0) Input::keyState_DirectionCountY[(int)LeftRight::Left] = 0;
			Input::keyState_DirectionCountY[(int)LeftRight::Left]--;
		}
		else if (input.Y >= 400){
			if (Input::keyState_DirectionCountY[(int)LeftRight::Left]<0) Input::keyState_DirectionCountY[(int)LeftRight::Left] = 0;
			Input::keyState_DirectionCountY[(int)LeftRight::Left]++;
		}
		else{
			Input::keyState_DirectionCountY[(int)LeftRight::Left] = 0;
		}

		if (input.Ry <= -400){
			if (Input::keyState_DirectionCountY[(int)LeftRight::Right]>0) Input::keyState_DirectionCountY[(int)LeftRight::Right] = 0;
			Input::keyState_DirectionCountY[(int)LeftRight::Right]--;
		}
		else if (input.Ry >= 400){
			if (Input::keyState_DirectionCountY[(int)LeftRight::Right]<0) Input::keyState_DirectionCountY[(int)LeftRight::Right] = 0;
			Input::keyState_DirectionCountY[(int)LeftRight::Right]++;
		}
		else{
			Input::keyState_DirectionCountY[(int)LeftRight::Right] = 0;
		}
	}
	else{//マウス、キーボード
		char tmp[256];
		GetHitKeyStateAll(tmp);

		for (int i = 0; i < 13; i++){
			if (tmp[Input::registedKeyCode.keyBoard[i]]==1){
				Input::keyCodeUpCount.keyBoard[i]++;
				Input::keyCodeDownCount.keyBoard[i] = 0;
			}
			else{
				Input::keyCodeUpCount.keyBoard[i] = 0;
				Input::keyCodeDownCount.keyBoard[i]++;
			}
		}

		
	}
}

double Input::getGridXDown(LeftRight lr){
	return 1.0*(abs(Input::keyState_DirectionSlopeX[(int)lr]) - 400)*Input::keyState_DirectionSlopeX[(int)lr] / abs(Input::keyState_DirectionSlopeX[(int)lr]) / 600;
}

double Input::getGridYDown(LeftRight lr){
	return 1.0*(abs(Input::keyState_DirectionSlopeY[(int)lr]) - 400)*Input::keyState_DirectionSlopeY[(int)lr] / abs(Input::keyState_DirectionSlopeY[(int)lr]) / 600;
}

double Input::getGridAngle(LeftRight lr){
	return atan2((double)Input::keyState_DirectionSlopeY[(int)lr], (double)Input::keyState_DirectionSlopeX[(int)lr]);
}

bool Input::getKeyCodeDown(KeyType key){
	if (Input::joyPadflag){
		if (Input::keyCodeDownCount.joyPad[(int)key] != 0) return true;
		else false;
	}
	else{
		if (Input::keyCodeDownCount.keyBoard[(int)key] != 0) return true;
		else false;
	}

	return false;
}

bool Input::getKeyCodeDownOnce(KeyType key){
	if (Input::joyPadflag){
		if (Input::keyCodeDownCount.joyPad[(int)key] == 1) return true;
		else false;
	}
	else{
		if (Input::keyCodeDownCount.keyBoard[(int)key] == 1) return true;
		else false;
	}

	return false;
}

bool Input::getKeyCodeUpOnce(KeyType key){
	if (Input::joyPadflag){
		if (Input::keyCodeUpCount.joyPad[(int)key] == 1) return true;
		else false;
	}
	else{
		if (Input::keyCodeUpCount.keyBoard[(int)key] == 1) return true;
		else false;
	}

	return false;
}

bool Input::getKeyCodeReDownWithinTime(KeyType key, unsigned int time){
	if (Input::joyPadflag){
		if (Input::keyCodeDownCount.joyPad[(int)key] != 0) return false;
		if (Input::keyCodeUpCount.joyPad[(int)key] > time) return false;
		else true;
	}
	else{
		if (Input::keyCodeDownCount.keyBoard[(int)key] != 0) return false;
		if (Input::keyCodeUpCount.keyBoard[(int)key] > time) return false;
		else true;
	}

	return false;
}

bool Input::getKeyCodeReUpWithinTime(KeyType key, unsigned int time){
	if (Input::joyPadflag){
		if (Input::keyCodeUpCount.joyPad[(int)key] != 0) return false;
		if (Input::keyCodeDownCount.joyPad[(int)key] > time) return false;
		else true;
	}
	else{
		if (Input::keyCodeUpCount.keyBoard[(int)key] != 0) return false;
		if (Input::keyCodeDownCount.keyBoard[(int)key] > time) return false;
		else true;
	}

	return false;
}


unsigned char Input::getRegistedKeyCodeKeyBoard(KeyType keyCode){
	return Input::registedKeyCode.keyBoard[(int)keyCode];
}

unsigned int Input::getRegistedKeyCodeJoyPad(KeyType keyCode){
	return Input::registedKeyCode.joyPad[(int)keyCode];
}

void Input::setRegistedKeyCodeKeyBoard(KeyType keyCode, unsigned char registKeyCode){
	Input::registedKeyCode.keyBoard[(int)keyCode] = registKeyCode;
}

void Input::setRegistedKeyCodeJoyPad(KeyType keyCode, unsigned int registKeyCode){
	Input::registedKeyCode.joyPad[(int)keyCode] = registKeyCode;
}