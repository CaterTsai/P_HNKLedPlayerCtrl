#include "starDisplay.h"

//------------------------------------
void starDisplay::setup(string font, string videoPath)
{
	_font.setGlobalDpi(72);
	_font.loadFont(font, cStarFontSize);
	
	_animAlpha.setDuration(0.5);	
	_animAlpha.reset(0.0);
	
	if (!_video.loadMovie(videoPath))
	{
		ofLog(OF_LOG_ERROR, "[starDisplay::setup]Load video failed");
		return;
	}
	_video.setLoopState(ofLoopType::OF_LOOP_NONE);

	_canvas.allocate(_drawArea.getWidth(), _drawArea.getHeight(), GL_RGBA);

	setupSetting();
	_isSetup = true;
}

//------------------------------------
void starDisplay::update(float delta)
{
	if (!_isSetup)
	{
		return;
	}
	_video.update();

	textUpdate(delta);
}

//------------------------------------
void starDisplay::draw()
{
	if (!_isSetup)
	{
		return;
	}

	
	ofPushStyle();
	ofSetColor(255);
	if(_video.isPlaying())
	{
		_video.draw(_drawArea.x, _drawArea.y, _drawArea.getWidth(), _drawArea.getHeight());
	}

	ofSetColor(255, _animAlpha.getCurrentValue());
	{
		if (_canvas.isAllocated())
		{
			_canvas.draw(_drawArea);
		}
	}
	ofPopStyle();
}

//------------------------------------
void starDisplay::setData(fireworkData data)
{
	_displayData = data;
	checkWish();
	updateCanvas();
}

//------------------------------------
void starDisplay::show()
{
	_animAlpha.reset(0.0);
	_animAlpha.animateToAfterDelay(255.0, 1.0);
	_eState = eTextFadein;

	
	_video.play();
	_video.setFrame(0);
	_video.update();
}

//------------------------------------
void starDisplay::textUpdate(float delta)
{
	_animAlpha.update(delta);

	switch (_eState)
	{
		case eTextFadein:
		{
			if (_animAlpha.hasFinishedAnimating() && _animAlpha.getPercentDone() == 1.0)
			{
				_waitTimer = cStarTextWaitTime;
				_eState = eTextWait;
			}
			break;
		}
		case eTextWait:
		{
			_waitTimer -= delta;
			if (_waitTimer <= 0.0f)
			{
				_animAlpha.animateTo(0.0f);
				_eState = eTextFadeout;
			}
			break;
		}
		case eTextFadeout:
		{
			if (_animAlpha.hasFinishedAnimating() && _animAlpha.getPercentDone() == 1.0)
			{
				_eState = eTextIdle;
				_video.stop();
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

#pragma region Canvas
//------------------------------------
void starDisplay::checkWish()
{
	auto totalWidth_ = _font.stringWidth(_displayData._wish);

	if (totalWidth_ <= cStarWishUpMaxWidth)
	{
		_displayWishUp = _displayData._wish;
		_displayWishDown = "";
	}
	else
	{
		wstring wsWish_ = s2ws(_displayData._wish);
		vector<int> eachCharW_;
		_font.getEachWorkWidth(_displayData._wish, eachCharW_);

		int index_ = 0;
		int width_ = 0;
		while (index_ < eachCharW_.size())
		{
			width_ += eachCharW_[index_];
			if (width_ > cStarWishUpMaxWidth)
			{
				break;
			}
			else
			{
				index_++;
			}
			
		}

		_displayWishUp = ws2s(wsWish_.substr(0, index_ - 1));
		_displayWishDown = ws2s(wsWish_.substr(index_));
	}
}

//------------------------------------
void starDisplay::updateCanvas()
{
	_canvas.begin();
	ofClear(0);
	{
		ofSetColor(255);

		//Align Left
		_font.drawString(_displayData._to, cStarToPos.x, cStarToPos.y);

		//Align Right
		_font.drawString(_displayData._from, cStarFromPos.x - _font.stringWidth(_displayData._from), cStarFromPos.y);

		if (_displayWishDown == "")
		{
			_font.drawString(_displayWishUp, cStarWishUpPos.x - _font.stringWidth(_displayWishUp) * 0.5f, cStarWishUpPos.y);
		}
		else
		{
			_font.drawString(_displayWishUp, cStarWishUpPos.x - _font.stringWidth(_displayWishUp) * 0.5f, cStarWishUpPos.y);
			_font.drawString(_displayWishDown, cStarWishDownPos.x - _font.stringWidth(_displayWishDown) * 0.5f, cStarWishDownPos.y);
		}
	}
	_canvas.end();
}

#pragma endregion

#pragma region DrawArea Setting
//------------------------------------
void starDisplay::setupSetting()
{
	_checkingImg.loadImage("check.jpg");
	ofRegisterKeyEvents(this);
	_settingMode = false;
}

//------------------------------------
void starDisplay::drawSetting()
{
	if (!_settingMode)
	{
		return;
	}
	ofPushStyle();
	{
		ofPushMatrix();
		{
			ofTranslate(_drawArea.x + _drawArea.width + 1, _drawArea.y);

			ofSetColor(255);
			ofDrawBitmapString("pos(" + ofToString(_drawArea.x) + ", " + ofToString(_drawArea.y) + ")", 0, 20);
			ofDrawBitmapString("width : " + ofToString(_drawArea.getWidth()) + " height : " + ofToString(_drawArea.getHeight()), 0, 40);
		}
		ofPopMatrix();

		ofSetColor(255);
		_checkingImg.draw(_drawArea);

		ofSetColor(0, 0, 255);
		ofNoFill();
		ofRect(_drawArea);


	}
	ofPopStyle();
}

//------------------------------------
void starDisplay::keyPressed(ofKeyEventArgs& e)
{
	if (e.key == '1')
	{
		_settingMode ^= true;
	}


	if (!_settingMode)
	{
		return;
	}


	switch (e.key)
	{
		//Pos
		case OF_KEY_UP:
		{
			_drawArea.y--;
			break;
		}
		case OF_KEY_DOWN:
		{
			_drawArea.y++;
			break;
		}
		case OF_KEY_LEFT:
		{
			_drawArea.x--;
			break;
		}
		case OF_KEY_RIGHT:
		{
			_drawArea.x++;
			break;
		}

		//Scale
		case 'o':
		{
			_drawArea.setWidth(_drawArea.getWidth() - 1);
			break;
		}
		case 'p':
		{
			_drawArea.setWidth(_drawArea.getWidth() + 1);
			break;
		}
		case '[':
		{
			_drawArea.setHeight(_drawArea.getHeight() - 1);
			break;
		}
		case ']':
		{
			_drawArea.setHeight(_drawArea.getHeight() + 1);
			break;
		}
		case 'k':
		{
			_drawArea.x = -32;
			_drawArea.y = -23;
			_drawArea.setWidth(304);
			_drawArea.setHeight(272);
			break;
		}
	}
}
#pragma endregion
