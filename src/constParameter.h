#pragma once

#include "ofMain.h"

static string ws2s(const wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, 0);
	string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, 0);
	return strTo;
}

static wstring s2ws(const string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	wstring strTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &strTo[0], size_needed);
	return strTo;

}

//Package
static const unsigned char cPacketSTA = '\x01';
static const unsigned char cPacketEND = '\x02';

//Led
static const int cPackageMaxSize = 32;
static const int cPackageHeaderSize = 7;
static const int cPackageDataMaxNum = cPackageMaxSize - cPackageHeaderSize;
//pad
static const int cReceiveMaxSize = 128;

//Scheduler
static const int cBasicLength = 15;
static const int cFireworkLength = 15;
static const int cBreatheLength = 30;
static const int cBrandLength = 30;

enum eEventType
{
	eEventFirework = 0
	,eEventBreathe
	,eEventBrand
};

//Protocol
enum eProtocol : unsigned char
{
	//Client REQ
	C2S_ClientProtocolREQ = 10
	,C2S_GetPlayerInfoREQ
	,C2S_PlayFireworkREQ
	,C2S_StopFireworkREQ
	,C2S_GetAnimInfoREQ
	,C2S_PlayAnimREQ

	//Server ACK 
	,S2C_ServerProtocolACK = 20
	,S2C_GetPlayerInfoACK
	,S2C_PlayFireworkACK
	,S2C_StopFireworkACK
	,S2C_GetAnimInfoACK
	,S2C_PlayAnimACK
	
	//Server Event
	,S2C_OnAnimFinish = 30
	,S2C_OnAnimUp = 31
	,ProtocolMax
};


//Firework 
static const int cFireworkNum = 3;
static const int cFireworkTypeNum = 9;

class fireworkData
{
public:
	void generate()
	{
		_to = ws2s(L"產產");
		_from = ws2s(L"Maymaymayy");
		_wish = ws2s(L"竧较е贾竧较е贾竧较е贾竧较е");

		vector<int> randomList_;
		randomList_.resize(cFireworkTypeNum);
		
		for (int idx_ = 0; idx_ < cFireworkTypeNum; idx_++)
		{
			randomList_[idx_] = idx_;
		}
		random_shuffle(randomList_.begin(), randomList_.end());

		for (int idx_ = 0; idx_ < cFireworkNum; idx_++)
		{
			_firework[idx_] = randomList_[idx_];
		}
	}
public:
	string _to, _from, _wish;
	unsigned char _firework[3];
};

//Star
static const int cStarFontSize = 40;
static const ofVec2f cStarToPos(114, 233);
static const ofVec2f cStarWishUpPos(301, 291);
static const ofVec2f cStarWishDownPos(301, 343);
static const ofVec2f cStarFromPos(444, 396);
static const int cStarWishUpMaxWidth = 380;
static const int cStarWishDownMaxWidth = 300;
static const float cStarTextWaitTime = 2.0f;

static const ofRectangle cDefaultDisplayArea(0, 0, 608, 544);

