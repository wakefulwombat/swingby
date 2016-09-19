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
	static KeyCodeState keyCodeDownCount;//�L�[�������Ă��鎞��
	static KeyCodeState keyCodeUpCount;//�L�[�������Ă��Ȃ�����

	static int keyState_DirectionCountX[2], keyState_DirectionCountY[2];//�X�e�B�b�N��|���Ă��鎞��
	static int keyState_DirectionSlopeX[2], keyState_DirectionSlopeY[2];//�X�e�B�b�N�̓|��(�A�i���O�l)
	

	static bool fileExistT(char* filepath);//�e�L�X�g
	static bool fileExistB(char* filepath);//�o�C�i��

	static int getKeyCodeDown_KeyBoard(unsigned int keyCode);
	static int getKeyCodeDown_JoyPad(unsigned char keyCode);

public:
	static void init();
	static bool getJoyPadFlag();
	static void writeNewKeyConfig();
	static void keyUpdate();

	static double getGridXDown(LeftRight lr);//x������{-1~1}
	static double getGridYDown(LeftRight lr);//y������{-1~1}
	static double getGridAngle(LeftRight lr);//0~2pi

	static bool getKeyCodeDown(KeyType key);
	static bool getKeyCodeDownOnce(KeyType key);
	static bool getKeyCodeUpOnce(KeyType key);
	static bool getKeyCodeReDownWithinTime(KeyType key, unsigned int time);//�L�[�𗣂��Ă���w�莞�Ԉȓ��ɃL�[����������
	static bool getKeyCodeReUpWithinTime(KeyType key, unsigned int time);//�L�[�������Ă���w�莞�Ԉȓ��ɃL�[�𗣂�����
	
	static unsigned char getRegistedKeyCodeKeyBoard(KeyType keyCode);
	static unsigned int getRegistedKeyCodeJoyPad(KeyType keyCode);
	static unsigned int getRegistedKeyCodeMouse(KeyType keyCode);
	static void setRegistedKeyCodeKeyBoard(KeyType keyCode, unsigned char registKeyCode);
	static void setRegistedKeyCodeJoyPad(KeyType keyCode, unsigned int registKeyCode);
	static void setRegistedKeyCodeMouse(KeyType keyCode, unsigned int registKeyCode);
};
