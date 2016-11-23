#include "padPacket.h"

#pragma region padPacketBasic
//-------------------------------------------------------
padPacketBasic::padPacketBasic(int socketID, int padID)
	:_success(false)
	, _socketID(socketID)
	, _padid(padID)
{}

//-------------------------------------------------------
bool padPacketBasic::getSuccess() const
{
	return _success;
}

//-------------------------------------------------------
int padPacketBasic::getSocketID() const
{
	return _socketID;
}

//-------------------------------------------------------
int padPacketBasic::getPadID() const
{
	return _padid;
}
#pragma endregion

#pragma region padFireworkPacket
//-------------------------------------------------------
padFireworkPacket::padFireworkPacket(int socketID, unsigned char * data)
	:padPacketBasic(socketID)
{
	int staIdx_, endIdx_;
	staIdx_ = endIdx_ = 0;
	for (int idx_ = 0; idx_ < cReceiveMaxSize; idx_++)
	{
		if (data[idx_] == cPacketSTA)
		{
			staIdx_ = idx_;
		}
		if (data[idx_] == cPacketEND)
		{
			endIdx_ = idx_;
		}
	}

	if (endIdx_ > cReceiveMaxSize || staIdx_ > cReceiveMaxSize)
	{
		ofLog(OF_LOG_ERROR, "[padFireworkPacket]Can't found STA & END");
		return;
	}

	ZeroMemory(_jsondata, cReceiveMaxSize);
	int length_ = endIdx_ - staIdx_ - 1;
	memcpy(_jsondata, (data + staIdx_ + 1), sizeof(unsigned char) * length_);

	decodeJson();
	_success = true;
}

//-------------------------------------------------------
fireworkData padFireworkPacket::getFirewrok() const
{
	return _fireworkData;
}

//-------------------------------------------------------
void padFireworkPacket::decodeJson()
{
	Json::Value root_;
	Json::Reader reader_;

	if (!reader_.parse((char*)_jsondata, root_))
	{
		ofLog(OF_LOG_ERROR, "[padFireworkPacket]Decode firework json failed");
	}

	_padid = root_["id"].asInt();
	_fireworkData._to = root_["to"].asString();
	_fireworkData._from = root_["from"].asString();
	_fireworkData._wish = root_["wish"].asString();

	string firework_;
	firework_ = root_["firework"].asString();

	_fireworkData._firework[0] = firework_[0] - '0';
	_fireworkData._firework[1] = firework_[1] - '0';
	_fireworkData._firework[2] = firework_[2] - '0';

}
#pragma endregion

#pragma region padWaitSecondPacket
padWaitSecondPacket::padWaitSecondPacket(int socketID, int padID, float waitS)
	:padPacketBasic(socketID, padID)
	, _waitS(waitS)
{

	_success = true;
}

//-------------------------------------------------------
string padWaitSecondPacket::toMsg()
{
	if (_success)
	{
		Json::Value root_;
		Json::FastWriter writer_;

		root_["id"] = _padid;
		root_["s"] = _waitS;

		return ("\x01" + writer_.write(root_) + "\x02");
	}
	else
	{
		return "";
	}
	
}

#pragma endregion


