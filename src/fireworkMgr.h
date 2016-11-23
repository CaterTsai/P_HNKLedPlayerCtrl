#pragma once


#include "constParameter.h"
#include "ledPlayerCtrl.h"
#include "starDisplay.h"

class fireworkMgr
{
public:
	void setup(string fontPath, string videoPath);
	void update(float delta);
	void draw();

	void fire(fireworkData& data);
	void showMsg();
	void fireworkFinish();

private:
	enum eFireworkState {
		eFireworkWait = 0
		, eFireworkPlaying
		, eFireworkBreathe
		, eFireworkBranding
	}_eState;

#pragma region LED Ctrl
private:
	void startFirework(fireworkData& data);
	void stopFirework();
#pragma endregion

#pragma region Star Display
private:
	starDisplay	_star;
#pragma endregion

#pragma region Firework Mapper
private:
	void setupMapper();
private:
	unsigned char _mapper[cFireworkTypeNum];
#pragma endregion


#pragma region Singleton
//-------------------
//Singleton
//-------------------
private:
	fireworkMgr()
		:_eState(eFireworkWait)
	{};
	~fireworkMgr(){}
	fireworkMgr(fireworkMgr const&) {};
	void operator=(fireworkMgr const&) {};


public:
	static fireworkMgr* GetInstance();
	static void Destroy();

private:
	static fireworkMgr *pInstance;
#pragma endregion
};