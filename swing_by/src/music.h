#ifndef _MUSIC_
#define _MUSIC_

#include <string>

enum class MusicList{
	Opening,
	Ending
};

struct MusicInfo{
	std::string filename;
	int repeat_start_time;
	int handle;
};

class Music{
private:
	static MusicInfo music_list[];

public:
	static void loadMusics();

	static void playMusic(MusicList music);
	static void stopMusic();
	static void setVolume(int volume);
	static void setSpeedRatio(double ratio);
};

#endif