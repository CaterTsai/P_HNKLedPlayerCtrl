#include "hnkEvent.h"

#pragma region hnkBasicEvent
//----------------------------------------------------
hnkBasicEvent::hnkBasicEvent(int triggerS, int length)
	:_triggerS(triggerS)
	, _length(length)
{}

//----------------------------------------------------
int hnkBasicEvent::getTriggerS() const
{
	return _triggerS;
}

//----------------------------------------------------
int hnkBasicEvent::getFinishS() const
{
	return _triggerS + _length;
}

//----------------------------------------------------
int hnkBasicEvent::getLength() const
{
	return _length;
}
#pragma endregion

#pragma region firework Event
//----------------------------------------------------
fireworkEvent::fireworkEvent(int triggerS, fireworkData firewrok)
	:hnkBasicEvent(triggerS, cFireworkLength)
	, _fireworkData(firewrok)
{
}

//----------------------------------------------------
void fireworkEvent::execute()
{
	ofLog(OF_LOG_NOTICE, ofGetTimestampString("Firework Event:%H-%M-%S-%i"));
	fireworkMgr::GetInstance()->fire(_fireworkData);
}
#pragma endregion

#pragma region breatherLight Event
//----------------------------------------------------
breatheLightEvent::breatheLightEvent(int triggerS)
	:hnkBasicEvent(triggerS, cBreatheLength)
{
}

//----------------------------------------------------
void breatheLightEvent::execute()
{
	cout << "breatherLight Event" << endl;
}
#pragma endregion

#pragma region branding Event
//----------------------------------------------------
brandEvent::brandEvent(int triggerS)
	:hnkBasicEvent(triggerS, cBrandLength)
{
}

//----------------------------------------------------
void brandEvent::execute()
{
	cout << "brandEvent Event" << endl;
}
#pragma endregion


