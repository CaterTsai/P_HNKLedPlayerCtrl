#pragma once

#include "ofxNetwork.h"
#include "constParameter.h"
#include "padPacket.h"


class padComm {
public:
	padComm()
		:_isSetup(false)
	{}
	void setup(int port);
	void update();
	void exit();

	void send(int socketID, string msg);
private:
	bool	_isSetup;
	ofxTCPServer	_server;

//------------------------
//Event
public:
	ofEvent<padFireworkPacket>	_padEvent;

};