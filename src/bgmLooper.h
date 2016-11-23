#pragma once

#include "constParameter.h"

class bgmLooper
{
public:
	bgmLooper()
		:_playID(-1)
		, _playing(false)
	{}
	void addBGM(string strPath);
	void update();

	void play();
	void stop();

private:
	bool _playing;
	vector<ofSoundPlayer>	_playList;
	int _playID;
};