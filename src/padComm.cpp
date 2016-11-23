#include "padComm.h"

//--------------------------------------------
void padComm::setup(int port)
{
	_server.setup(port);
	_isSetup = true;
}

//--------------------------------------------
void padComm::update()
{
	if (!_isSetup)
	{
		return;
	}

	for (int idx_ = 0; idx_ < _server.getLastID(); idx_++)
	{
		if (!_server.isClientConnected(idx_))
		{
			continue;
		}

		unsigned char buffer_[cReceiveMaxSize];
		if (_server.receiveRawBytes(idx_, (char*)buffer_, cReceiveMaxSize) > 0)
		{
			padFireworkPacket newPacket_(idx_, buffer_);

			if (newPacket_.getSuccess())
			{
				ofNotifyEvent(_padEvent, newPacket_);
			}
		}
	}
}

//--------------------------------------------
void padComm::exit()
{
	_server.close();
	_isSetup = false;
}

//--------------------------------------------
void padComm::send(int socketID, string msg)
{
	if (_server.isClientConnected(socketID))
	{
		if (!_server.sendRawMsg(socketID, msg.c_str(), msg.length()))
		{
			ofLog(OF_LOG_ERROR, "[padComm::send]send failed :" + socketID);
		}
	}
	else
	{
		ofLog(OF_LOG_ERROR, "[padComm::send]socket is disconnect :" + socketID);
	}
	
}
