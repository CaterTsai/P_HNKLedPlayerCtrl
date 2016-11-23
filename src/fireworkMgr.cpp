#include "fireworkMgr.h"

#pragma region Basic Method
void fireworkMgr::setup(string fontPath, string videoPath)
{
	_star.setup(fontPath, videoPath);
	setupMapper();
}

//--------------------------------------------------------------
void fireworkMgr::update(float delta)
{
	_star.update(delta);
}

//--------------------------------------------------------------
void fireworkMgr::draw()
{
	_star.drawSetting();


	if (_eState == eFireworkWait)
	{
		return;
	}
	_star.draw();
}

//--------------------------------------------------------------
void fireworkMgr::fire(fireworkData & data)
{
	if (_eState != eFireworkWait)
	{
		stopFirework();
	}

	//Led Ctrl
	startFirework(data);

	//Star
	_star.setData(data);

	_eState = eFireworkPlaying;
}

//--------------------------------------------------------------
void fireworkMgr::showMsg()
{
	if (_eState == eFireworkWait)
	{
		return;
	}

	_star.show();
}

//--------------------------------------------------------------
void fireworkMgr::fireworkFinish()
{
	if (_eState == eFireworkWait)
	{
		return;
	}
	_eState = eFireworkWait;
}

#pragma endregion

#pragma region LED Ctrl
//--------------------------------------------------------------
void fireworkMgr::startFirework(fireworkData & data)
{
	string packetData_;
	packetData_.resize(4);
	packetData_[0] = cFireworkNum;
	packetData_[1] = _mapper[data._firework[0]];
	packetData_[2] = _mapper[data._firework[1]];
	packetData_[3] = _mapper[data._firework[2]];

	packet fireworkPacket_(eProtocol::C2S_PlayFireworkREQ, packetData_);
	ledPlayerCtrl::GetInstance()->send(fireworkPacket_);
}

//--------------------------------------------------------------
void fireworkMgr::stopFirework()
{
	packet stopfireworkPacket_(eProtocol::C2S_StopFireworkREQ);
	ledPlayerCtrl::GetInstance()->send(stopfireworkPacket_);

	_eState = eFireworkWait;
}

//--------------------------------------------------------------
void fireworkMgr::setupMapper()
{
	_mapper[0] = 1;	_mapper[1] = 3;	_mapper[2] = 8;
	_mapper[3] = 4;	_mapper[4] = 7;	_mapper[5] = 9;
	_mapper[6] = 6;	_mapper[7] = 2;	_mapper[8] = 5;
}
#pragma endregion

#pragma region Singletion
//--------------------------------------------------------------
fireworkMgr* fireworkMgr::pInstance = 0;
//--------------------------------------------------------------
fireworkMgr* fireworkMgr::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new fireworkMgr();
	}
	return pInstance;
}

//--------------------------------------------------------------
void fireworkMgr::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}
#pragma endregion