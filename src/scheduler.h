#pragma once

#include "constParameter.h"
#include "hnkEvent.h"

class scheduler
{
public:
	scheduler();
	~scheduler();
	void update();
	
	void start();
	
	float addFirework(fireworkData fireworkData);
	void addBookingFirework(fireworkData fireworkData, int time);
	void addOthers(eEventType eType);

private:
	int getTime();
	float getTimeDetal();
	bool checkEventMap(int time, int& refLength);
	int getEventTime(int length);

	int idleEvent();

private:
	bool _isStart;
	int _nowTime, _nextCheck;
	struct cmpEvent {
		bool operator()(const int &a, const int &b)
		{
			return a < b;
		}
	};
	map<int, ofPtr<hnkBasicEvent>, cmpEvent> _eventMap;
};