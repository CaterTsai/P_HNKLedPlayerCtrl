#include "package.h"

//----------------------------------
packet::packet(string source)
{
	if (source[0] != cPacketSTA)
	{
		ofLog(OF_LOG_ERROR, "[packet]Can't found STA");
		_success = false;
		return;
	}

	const char* pSource_ = source.c_str();

	int packageLength_ = 0;
	
	unsigned char lengthTmp_[4] = { 0 };
	lengthTmp_[0] = pSource_[4];
	lengthTmp_[1] = pSource_[3];
	lengthTmp_[2] = pSource_[2];
	lengthTmp_[3] = pSource_[1];

	memcpy(&packageLength_, lengthTmp_, sizeof(int));
	if (source[packageLength_ - 1] != cPacketEND)
	{
		ofLog(OF_LOG_ERROR, "[packet]Can't found END");
		_success = false;
		return;
	}
	_length = packageLength_ - cPackageHeaderSize;

	memcpy(&_eProtocol, (pSource_ + 5), sizeof(unsigned char));
	if (_eProtocol < C2S_ClientProtocolREQ || _eProtocol >= ProtocolMax)
	{
		ofLog(OF_LOG_ERROR, "[packet]Unknow protocol :" + _eProtocol);
		_success = false;
		return;
	}

	memcpy(_data, (pSource_ + 6), sizeof(unsigned char) * _length);
	_success = true;
}

//----------------------------------
packet::packet(unsigned char * data)
{
	if (data[0] != cPacketSTA)
	{
		ofLog(OF_LOG_ERROR, "[packet]Can't found STA");
		_success = false;
		return;
	}

	int packageLength_ = 0;

	unsigned char lengthTmp_[4] = { 0 };
	lengthTmp_[0] = data[4];
	lengthTmp_[1] = data[3];
	lengthTmp_[2] = data[2];
	lengthTmp_[3] = data[1];

	memcpy(&packageLength_, lengthTmp_, sizeof(int));
	_length = packageLength_ - cPackageHeaderSize;
	memcpy(&_eProtocol, (data + 5), sizeof(unsigned char));

	if (_eProtocol < C2S_ClientProtocolREQ || _eProtocol >= ProtocolMax)
	{
		ofLog(OF_LOG_ERROR, "[packet]Unknow protocol :" + _eProtocol);
		_success = false;
		return;
	}

	memcpy(_data, (data + 6), sizeof(unsigned char) * _length);
	_success = true;
}

//----------------------------------
packet::packet(eProtocol type, string data)
{
	memcpy(_data, data.c_str(), sizeof(unsigned char) * data.size());
	_length = data.size();
	_eProtocol = type;
	_success = true;
}


//----------------------------------
string packet::toMsg()
{
	if (!_success)
	{
		return "";
	}

	char msg_[cPackageDataMaxNum];
	ZeroMemory(msg_, cPackageDataMaxNum);
	int packageLength_ = _length + cPackageHeaderSize;

	msg_[0] = '\x01';
	memcpy(msg_ + 1, &packageLength_, sizeof(int));
	memcpy(msg_ + 5, &_eProtocol, sizeof(unsigned char));
	memcpy(msg_ + 6, &_data, sizeof(unsigned char) * _length);
	msg_[_length + 6] = '\x02';

	string result_;
	result_.assign(msg_, packageLength_);
	return result_;
}
