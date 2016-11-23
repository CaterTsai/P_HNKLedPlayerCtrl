#pragma once

#include "constParameter.h"
#include "fireworkMgr.h"

class hnkBasicEvent
{
public:
	hnkBasicEvent(int triggerS, int length);
	virtual void execute() {};

	int getTriggerS() const;
	int getFinishS() const;
	int getLength() const;

protected:
	int _triggerS, _length;

};

//------------------------------------------------
class fireworkEvent : public hnkBasicEvent
{
public:
	fireworkEvent(int triggerS, fireworkData firewrok);
	virtual void execute() override;

private:
	fireworkData _fireworkData;
};

//------------------------------------------------
class breatheLightEvent : public hnkBasicEvent
{
public:
	breatheLightEvent(int triggerS);
	virtual void execute() override;
};

//------------------------------------------------
class brandEvent : public hnkBasicEvent
{
public:
	brandEvent(int triggerS);
	virtual void execute() override;
};