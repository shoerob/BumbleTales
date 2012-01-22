/*
 *  SplashScreen.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "IRenderable.h"
#include "Graphics.h"
#include "Event.h"
#include "Globals.h"

class SplashScreen : public IRenderable
{
public:
	SplashScreen(int splashAsset, float delayTime, int zPos);
	virtual ~SplashScreen();
	
	void SetSplashAsset(int splashAsset, float delayTime);
	void SetFadeEffect(bool _value);
	void StartSplash();
	
	// IRenderable
	void Update();
	void Render();
	void ForceRender();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	void SetFrameSet(int frameSet);
	Event SplashFinished;
	
private:
	CR::Graphics::Sprite *splashSprite;
	float m_baseDelayTime;
	float m_delayTime;
	bool m_running;
	bool isFade;
	int fadeAlpha;
};