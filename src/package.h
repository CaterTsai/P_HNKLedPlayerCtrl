#pragma once

#include "constParameter.h"

class packet
{
public:
	packet(string source);
	packet(unsigned char* data);
	packet(eProtocol type, string data = "");
	string toMsg();

public:
	bool _success;
	int _length;
	eProtocol _eProtocol;
	unsigned char _data[cPackageDataMaxNum];

};