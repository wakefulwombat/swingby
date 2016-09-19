#pragma once

struct RegistedKeyCode {
	unsigned int mouse[6];
	unsigned char keyBoard[6];
	unsigned int joyPad[6];
};

struct KeyCodeState{
	unsigned int mouse[6];
	unsigned int keyBoard[6];
	unsigned int joyPad[6];
};

enum class LeftRight{
	Left,
	Right
};

enum class KeyType{
	Common_OK,
	Common_Cancel,
	Common_Pause,
	Game_Swing,
	Game_Slow,
	Game_VectorTrans
};

class Input{
private:
	static bool joyPadflag;

	static RegistedKeyCode registedKeyCode;
	static KeyCodeState keyCodeDownCount;//キーを押している時間
	static KeyCodeState keyCodeUpCount;//キーを押していない時間

	static int keyState_DirectionCountX[2], keyState_DirectionCountY[2];//スティックを倒している時間
	static int keyState_DirectionSlopeX[2], keyState_DirectionSlopeY[2];//スティックの倒れ具合(アナログ値)
	

	static bool fileExistT(char* filepath);//テキスト
	static bool fileExistB(char* filepath);//バイナリ

	static int getKeyCodeDown_KeyBoard(unsigned int keyCode);
	static int getKeyCodeDown_JoyPad(unsigned char keyCode);

public:
	static void init();
	static bool getJoyPadFlag();
	static void writeNewKeyConfig();
	static void keyUpdate();

	static double getGridXDown(LeftRight lr);//x軸方向{-1~1}
	static double getGridYDown(LeftRight lr);//y軸方向{-1~1}
	static double getGridAngle(LeftRight lr);//0~2pi

	static bool getKeyCodeDown(KeyType key);
	static bool getKeyCodeDownOnce(KeyType key);
	static bool getKeyCodeUpOnce(KeyType key);
	static bool getKeyCodeReDownWithinTime(KeyType key, unsigned int time);//キーを離してから指定時間以内にキーを押したか
	static bool getKeyCodeReUpWithinTime(KeyType key, unsigned int time);//キーを押してから指定時間以内にキーを離したか
	
	static unsigned char getRegistedKeyCodeKeyBoard(KeyType keyCode);
	static unsigned int getRegistedKeyCodeJoyPad(KeyType keyCode);
	static unsigned int getRegistedKeyCodeMouse(KeyType keyCode);
	static void setRegistedKeyCodeKeyBoard(KeyType keyCode, unsigned char registKeyCode);
	static void setRegistedKeyCodeJoyPad(KeyType keyCode, unsigned int registKeyCode);
	static void setRegistedKeyCodeMouse(KeyType keyCode, unsigned int registKeyCode);
};
