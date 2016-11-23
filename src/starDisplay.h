#pragma once

#include "ofxTrueTypeFontUC.h"
#include "ofxHapPlayer.h"
#include "ofxAnimatableFloat.h"
#include "constParameter.h"

class starDisplay
{
public:
	starDisplay()
		:_isSetup(false)
		,_eState(eTextIdle)
		,_drawArea(cDefaultDisplayArea)
	{
		_displayData.generate();
	}

	void setup(string font, string videoPath);
	void update(float delta);
	void draw();

	void setData(fireworkData data);
	void show();

private:
	void textUpdate(float delta);

private:
	enum eTextState {
		eTextIdle = 0
		, eTextFadein
		, eTextWait
		, eTextFadeout
	}_eState;

	bool _isSetup;
	float _waitTimer;
	ofxAnimatableFloat _animAlpha;
	ofRectangle	_drawArea;
	fireworkData _displayData;
	
	ofxHapPlayer _video;

#pragma region Canvas
private:
	void checkWish();
	void updateCanvas();
private:
	string _displayWishUp, _displayWishDown;
	ofFbo	_canvas;
	ofxTrueTypeFontUC	_font;
#pragma endregion

#pragma region Draw Area Setting
private:
	void setupSetting();
	
public:
	void drawSetting();
	void keyPressed(ofKeyEventArgs& e);
	void keyReleased(ofKeyEventArgs& e) {};

private:
	ofImage	_checkingImg;
	bool _settingMode;
#pragma endregion

	
};