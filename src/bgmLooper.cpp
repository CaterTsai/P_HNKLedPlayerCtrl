#include "bgmLooper.h"

//--------------------------------------------------------------
void bgmLooper::addBGM(string strPath)
{
	ofSoundPlayer newPlayer_;
	if (!newPlayer_.loadSound(strPath))
	{
		ofLog(OF_LOG_WARNING, "[bgmLooper::addBGM]load bgm failed :" + strPath);
		return;
	}
	newPlayer_.setLoop(false);
	_playList.push_back(newPlayer_);

}

//--------------------------------------------------------------
void bgmLooper::update()
{
	if (_playList.size() <= 0 || !_playing)
	{
		return;
	}
	
	if (_playList[_playID].getPosition() == 1.0f)
	{
		_playList[_playID].stop();
		_playID = (_playID + 1) % _playList.size();
		_playList[_playID].play();
	}
}

//--------------------------------------------------------------
void bgmLooper::play()
{
	if (_playList.size() <= 0)
	{
		return;
	}

	try {
		_playID = 0;
		_playList[_playID].play();
		_playing = true;
	}
	catch (exception e)
	{
		ofLog(OF_LOG_ERROR, e.what());
	}

}

//--------------------------------------------------------------
void bgmLooper::stop()
{
	if (_playList.size() <= 0)
	{
		return;
	}

	try {
		if (_playList[_playID].getIsPlaying())
		{
			_playList[_playID].stop();
		}
	}
	catch (exception e)
	{
		ofLog(OF_LOG_ERROR, e.what());
	}
	
	_playID = 0;
	_playing = false;
}
