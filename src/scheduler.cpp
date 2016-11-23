#include "scheduler.h"

//-------------------------------
scheduler::scheduler()
	:_isStart(false)
	, _nextCheck(0)
	, _nowTime(0)
{}

//-------------------------------
scheduler::~scheduler()
{}

//-------------------------------
void scheduler::update()
{
	if (!_isStart)
	{
		return;
	}
	_nowTime = getTime();

	if (_nowTime >= _nextCheck)
	{
		int length_ = 0;
		if (!checkEventMap(_nowTime, length_))
		{
			length_ = idleEvent();
		}
		_nextCheck += length_;
	}
}

//-------------------------------
void scheduler::start()
{
	_nowTime = getTime();
	//_nextCheck = _nowTime + (cBasicLength - (_nowTime % cBasicLength)) + cBasicLength;
	_nextCheck = _nowTime + (cBasicLength - (_nowTime % cBasicLength));

	_isStart = true;
}

//-------------------------------
float scheduler::addFirework(fireworkData fireworkData)
{
	int eventTime_ = getEventTime(cFireworkLength);
	
	auto Iter_ = _eventMap.find(eventTime_);
	if (Iter_ == _eventMap.end())
	{
		_eventMap.insert(make_pair(eventTime_, ofPtr<hnkBasicEvent>(new fireworkEvent(eventTime_, fireworkData))));
		return (float)(eventTime_) - getTimeDetal();
	}
	else
	{
		ofLog(OF_LOG_ERROR, "[scheduler::addFirework]event time is duplicate");
		return -1;
	}
}

//-------------------------------
void scheduler::addBookingFirework(fireworkData fireworkData, int time)
{
	if (time % cBasicLength != 0)
	{
		ofLog(OF_LOG_ERROR, "[scheduler::addBookingFirework]booking time wrong");
		return;
	}

	auto Iter_ = _eventMap.find(time);
	if (Iter_ == _eventMap.end())
	{
		_eventMap.insert(make_pair(time, ofPtr<hnkBasicEvent>(new fireworkEvent(time, fireworkData))));
	}
	else
	{
		ofLog(OF_LOG_ERROR, "[scheduler::addBookingFirework]event time is duplicate");
	}
}

//-------------------------------
void scheduler::addOthers(eEventType eType)
{
	int eventTime_ = getEventTime(cFireworkLength);

	auto Iter_ = _eventMap.find(eventTime_);
	if (Iter_ == _eventMap.end())
	{
		switch (eType)
		{
			case eEventType::eEventBrand:
			{
				_eventMap.insert(make_pair(eventTime_, ofPtr<hnkBasicEvent>(new brandEvent(eventTime_))));
				break;
			}
			case eEventType::eEventBreathe:
			{
				_eventMap.insert(make_pair(eventTime_, ofPtr<hnkBasicEvent>(new breatheLightEvent(eventTime_))));
				break;
			}
			default:
			{
				break;
			}
		}
		
	}
	else
	{
		ofLog(OF_LOG_ERROR, "[scheduler::addOthers]event time is duplicate");
	}
}

//-------------------------------
int scheduler::getTime()
{
	int s_ = stoi(ofGetTimestampString("%S"));
	int m_ = stoi(ofGetTimestampString("%M"));
	int h_ = stoi(ofGetTimestampString("%H"));

	return (h_ * 60 + m_) * 60 + s_;
}

//-------------------------------
float scheduler::getTimeDetal()
{
	float ms_ = (float)stoi(ofGetTimestampString("%i"))/1000.0f;
	int s_ = stoi(ofGetTimestampString("%s"));
	int m_ = stoi(ofGetTimestampString("%M"));
	int h_ = stoi(ofGetTimestampString("%H"));
	

	return float((h_ * 60 + m_) * 60 + s_) + ms_;
}

//-------------------------------
bool scheduler::checkEventMap(int time, int& refLength)
{
	refLength = 0;

	auto iter_ = _eventMap.begin();
	if (iter_ != _eventMap.end() && time >= iter_->first)
	{
		refLength = iter_->second->getLength();
		iter_->second->execute();
		_eventMap.erase(iter_);

		return true;
	}
	else
	{
		return false;
	}
	
}

//-------------------------------
int scheduler::getEventTime(int length)
{
	int reValue_ = -1;
	auto iter_ = _eventMap.begin();
	if (iter_ == _eventMap.end() || (iter_->first - _nextCheck) >= length)
	{
		reValue_ = _nextCheck;
	}
	else
	{
		iter_++;
		for (; iter_ != _eventMap.end(); iter_++)
		{
			auto preIter_ = iter_;
			preIter_--;

			int finishS_ = preIter_->second->getFinishS();
			if ((iter_->first - finishS_) >= length)
			{
				reValue_ = finishS_;
				break;
			}
		}
	}

	if (reValue_ == -1)
	{
		auto endIter_ = _eventMap.end();
		endIter_--;

		reValue_ = endIter_->second->getFinishS();
	}

	return reValue_;
}

//-------------------------------
int scheduler::idleEvent()
{
	//fireworkData fireworkData_;
	//fireworkData_.generate();
	//fireworkEvent event_(0, fireworkData_);
	//event_.execute();

	//ofLog(OF_LOG_NOTICE, "[scheduler::idleEvent]Add idle event");

	return cFireworkLength;
}
