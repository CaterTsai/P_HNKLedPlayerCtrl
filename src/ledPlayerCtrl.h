#pragma once

#include "ofxNetwork.h"
#include "constParameter.h"
#include "package.h"

class ledPlayerCtrl
{
public:

	void setup(string ip, int port);
	void update();
	void send(packet packet);

private:
	bool	_isConnection;
	ofxTCPClient	_client;

//------------------------
//Event
public:
	ofEvent<packet>	_ledPlayerEvent;

#pragma region Singleton
	//-------------------
	//Singleton
	//-------------------
private:
	ledPlayerCtrl()
		:_isConnection(false)
	{};
	~ledPlayerCtrl()
	{
		_client.close();
	}
	ledPlayerCtrl(ledPlayerCtrl const&) {};
	void operator=(ledPlayerCtrl const&) {};

public:
	static ledPlayerCtrl* GetInstance();
	static void Destroy();

private:
	static ledPlayerCtrl *pInstance;
#pragma endregion
};
