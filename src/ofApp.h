#pragma once

#include "ofxTrueTypeFontUC.h"
#include "constParameter.h"
#include "scheduler.h"
#include "fireworkMgr.h"
#include "ledPlayerCtrl.h"
#include "padComm.h"
#include "bgmLooper.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	float _mainTimer;
#pragma region Scheduler
private:
	scheduler	_scheduler;
#pragma endregion

#pragma region Firework Manager

#pragma endregion
	
#pragma region LED Player
//----------------------------------
public:
	void setupLedPlayer(string IP, int port);
	void onLedPlayerEvent(packet& e);

#pragma endregion

#pragma region padComm
public:
	void setupPadComm(int port);
	void onPadEvent(padFireworkPacket& e);
private:
	padComm _padComm;
#pragma endregion

#pragma region BGM Player
public:
	void setupBGM();
private:
	bgmLooper	_bgmPlayer;
#pragma endregion



};
