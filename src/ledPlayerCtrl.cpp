#include "ledPlayerCtrl.h"



//----------------------------------
void ledPlayerCtrl::setup(string ip, int port)
{	
	if (!_client.setup(ip, port))
	{
		ofLog(OF_LOG_ERROR, "[ledPlayerCtrl::setup]Connection Led player failed");
		return;
	}
	_isConnection = true;
	
}

//----------------------------------
void ledPlayerCtrl::update()
{
	if (!_isConnection)
	{
		return;
	}

	//Receive
	string tempMsg_, msg_;
	unsigned char buffer_[cPackageMaxSize];
	if (_client.receiveRawBytes((char*)buffer_, cPackageMaxSize) > 0)
	{
		packet newPacket_(buffer_);

		if (newPacket_._success)
		{
			ofNotifyEvent(_ledPlayerEvent, newPacket_);
		}
	}

	//Reconnect?
	if (!_client.isConnected())
	{
		_isConnection = false;
	}
}

//----------------------------------
void ledPlayerCtrl::send(packet packet)
{
	_client.sendRaw(packet.toMsg());
}

#pragma region Singletion
//--------------------------------------------------------------
ledPlayerCtrl* ledPlayerCtrl::pInstance = 0;

//--------------------------------------------------------------
ledPlayerCtrl* ledPlayerCtrl::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new ledPlayerCtrl();
	}
	return pInstance;
}

//--------------------------------------------------------------
void ledPlayerCtrl::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}
#pragma endregion