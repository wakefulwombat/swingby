#ifndef _SOUND_
#define _SOUND_

enum class SoundList{
	OK,
	CANCEL
};

struct SoundInfo{
	int handle;
	bool validation;
};

class Sound{
private:
	static SoundInfo sound_list[];

public:
	static void loadSounds();

	static void setPlay(SoundList sound);

	static void playAll();
};

#endif