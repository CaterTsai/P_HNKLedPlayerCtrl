#pragma once

#include "constParameter.h"
#include "json.h"

class padPacketBasic
{
public:
	padPacketBasic(int socketID, int padID = -1);

	bool getSuccess() const;
	int getSocketID() const;
	int getPadID() const;
protected:
	bool _success;
	int _socketID, _padid;
};

class padFireworkPacket : public padPacketBasic
{
public:
	padFireworkPacket(int socketID, unsigned char* data);

	fireworkData getFirewrok() const;
private:
	void decodeJson();

private:
	unsigned char _jsondata[cReceiveMaxSize];
	fireworkData _fireworkData;
};

class padWaitSecondPacket : public padPacketBasic
{
public:
	padWaitSecondPacket(int socketID, int padID, float waitS);
	string toMsg();

private:
	float _waitS;
};