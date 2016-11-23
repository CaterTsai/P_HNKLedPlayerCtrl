#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(0);
	ofSetVerticalSync(true);
	
	//BGM
	setupBGM();

	setupLedPlayer("127.0.0.1", 11999);
	setupPadComm(9487);
	
	//Firework manager
	fireworkMgr::GetInstance()->setup("fonts/msjhbd.ttf", "videos/star.mov");

	ofToggleFullscreen();
	

	_bgmPlayer.play();
	_scheduler.start();

	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update()
{
	float delta_ = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta_;

	_scheduler.update();
	ledPlayerCtrl::GetInstance()->update();
	_padComm.update();

	fireworkMgr::GetInstance()->update(delta_);

	_bgmPlayer.update();
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw()
{
	fireworkMgr::GetInstance()->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
		case 'f':
		{
			fireworkData newFireworkData_;
			newFireworkData_.generate();
			int waitS = _scheduler.addFirework(newFireworkData_);
			cout << "Fire!! wait : " << waitS << endl;
			break;
		}
		break;
		case 'q':
		{
			ofToggleFullscreen();
			break;
		}
	}
}

#pragma region LED Player
//--------------------------------------------------------------
void ofApp::setupLedPlayer(string IP, int port)
{
	ledPlayerCtrl::GetInstance()->setup(IP, port);

	ofAddListener(ledPlayerCtrl::GetInstance()->_ledPlayerEvent, this, &ofApp::onLedPlayerEvent);
}

//--------------------------------------------------------------
void ofApp::onLedPlayerEvent(packet & e)
{
	switch (e._eProtocol)
	{
		case S2C_GetPlayerInfoACK:
		{
			break;
		}
		case S2C_PlayFireworkACK:
		{
			break;
		}
		case S2C_StopFireworkACK:
		{
			break;
		}
		case S2C_GetAnimInfoACK:
		{
			break;
		}
		case S2C_PlayAnimACK:
		{
			break;
		}
		case S2C_OnAnimFinish:
		{
			ofLog(OF_LOG_NOTICE, ofGetTimestampString("Firework Finish Event:%H-%M-%S-%i"));
			fireworkMgr::GetInstance()->fireworkFinish();
			break;
		}
		case S2C_OnAnimUp:
		{
			fireworkMgr::GetInstance()->showMsg();
			break;
		}
	}
}
#pragma endregion

#pragma region padComm
//--------------------------------------------------------------
void ofApp::setupPadComm(int port)
{
	_padComm.setup(9487);
	ofAddListener(_padComm._padEvent, this, &ofApp::onPadEvent);
}

//--------------------------------------------------------------
void ofApp::onPadEvent(padFireworkPacket & e)
{
	auto fireworkData_ = e.getFirewrok();
	float waitS_ = _scheduler.addFirework(fireworkData_);
	wstring wfrom_ = s2ws(e.getFirewrok()._from);
	padWaitSecondPacket recvPacket_(e.getSocketID(), e.getPadID(), waitS_);

	if (recvPacket_.getSuccess())
	{
		ofLog(OF_LOG_NOTICE, "[ofApp::onPadEvent]Pad wait time : " + ofToString(waitS_));
		_padComm.send(recvPacket_.getSocketID(), recvPacket_.toMsg());
	}
	else
	{
		ofLog(OF_LOG_ERROR, "[ofApp::onPadEvent]padWaitSecondPacket failed");
	}
	
}
#pragma endregion

#pragma region BGM Player
//--------------------------------------------------------------
void ofApp::setupBGM()
{
	_bgmPlayer.addBGM("music/bgm1.mp3");
	_bgmPlayer.addBGM("music/bgm2.mp3");
	_bgmPlayer.addBGM("music/bgm3.mp3");
	_bgmPlayer.addBGM("music/bgm4.mp3");
	_bgmPlayer.addBGM("music/bgm5.mp3");
	_bgmPlayer.addBGM("music/bgm6.mp3");
}
#pragma endregion


