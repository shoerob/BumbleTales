/*
 *  SplashScreen.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SplashScreen.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

SplashScreen::SplashScreen(int splashAsset, float delayTime, int zPos)
{
	splashSprite = graphics_engine->CreateSprite1(false,zPos);
	SetSplashAsset(splashAsset, delayTime);
	m_running = false;
	isFade = false;
	fadeAlpha = 255;
}

SplashScreen::~SplashScreen()
{
	splashSprite->Release();
}

void SplashScreen::SetSplashAsset(int splashAsset, float delayTime)
{
	splashSprite->SetImage(splashAsset);
	SetPosition(160, 240);
	m_baseDelayTime = delayTime;
	m_delayTime = delayTime;
}

void SplashScreen::SetFadeEffect(bool _value)
{
	isFade = _value;
}

void SplashScreen::StartSplash()
{
	m_running = true;
	m_delayTime = m_baseDelayTime;
}

void SplashScreen::Update()
{
	if (!m_running)
		return;
	
	m_delayTime -= Globals::Instance().GetTimer()->GetTimePassed();
	if (m_delayTime <= 0)
	{
		m_running = false;
		SplashFinished();
	}
	
	if (isFade)
	{
		
		CR::Math::Color32 color = CR::Math::Color32(255, 255, 255, fadeAlpha);
		splashSprite->Color(color);
	}
}

void SplashScreen::Render()
{
	if (!m_running)
		return;
	
	if (m_delayTime > 0)
	splashSprite->Render();
}

void SplashScreen::ForceRender()
{
	splashSprite->Render();
}

void SplashScreen::SetPosition(float xLoc, float yLoc)
{
	splashSprite->SetPositionAbsolute(xLoc, yLoc);
}

void SplashScreen::PauseAnimation(bool pause)
{
}

void SplashScreen::SetFrameSet(int frameSet)
{
	splashSprite->SetFrameSet(frameSet);
}