/*
 *  BuildingButtonControl.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/1/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "BuildingButtonControl.h"
#include "AssetList.h"
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;

extern CR::Graphics::GraphicsEngine *graphics_engine;

BuildingButtonControl::BuildingButtonControl() : m_touchID(-1)
{
	m_active = true;
	buttonSprite = graphics_engine->CreateSprite1(true,800);
	m_tag = -1;
	m_wasPaused = false;
	m_showBuildAnimation = false;
	fadeColor = CR::Math::Color32(255, 255, 255, 255);
	alphaStep = 0;
	buildSprite = NULL;
}

BuildingButtonControl::~BuildingButtonControl()
{
	buttonSprite->Release();
	
	if (buildSprite != NULL)
		buildSprite->Release();
}

void BuildingButtonControl::Update()
{
	if (!m_active && !Disabled())
	{
		// skip the time decrease this time since the game was paused
		if (!m_wasPaused)
		{
			m_currTime -= Globals::Instance().GetTimer()->GetTimePassed();
			
			if (m_currTime <= 0)
			{
				m_active = true;
				buttonSprite->SetAutoAnimate(true);
				
				// play activate sound
				std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
				sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::building_readied_1::ID);
				sound->Play();
			}
		}
		else
			m_wasPaused = false;
	}
}

void BuildingButtonControl::Render()
{
	buttonSprite->Render();
	
	if (m_showBuildAnimation)
	{
		if (!buildSprite->IsAnimating())
		{
			buildSprite->Release();
			buildSprite = NULL;
			m_showBuildAnimation = false;
			//fadeColor = CR::Math::Color32(255, 255, 255, 255);
			fadeColor.Alpha(255);
		}
		else
		{
			buildSprite->Render();
			
			if (fadeColor.Alpha() + alphaStep >= 255)
				fadeColor.Alpha(255);
			else
				fadeColor.Alpha(fadeColor.Alpha() + alphaStep);
		}
		
		buttonSprite->Color(fadeColor);
	}
}

void BuildingButtonControl::SetDelayTime(float _value)
{
	m_delayTime = _value;
	
	if (m_currTime > m_delayTime)
		m_currTime = m_delayTime;
}

void BuildingButtonControl::StartCountDown()
{
	m_active = false;
	m_currTime = m_delayTime;
	
	buttonSprite->SetAutoAnimate(false);
	buttonSprite->SetFrame(0);
}

void BuildingButtonControl::SetSprite(int nSprite)
{
	buttonSprite->SetImage(nSprite);
}

void BuildingButtonControl::SetPosition(int xLoc, int yLoc)
{
	Rect r;
	r.top = yLoc;
	r.left = xLoc;
	r.bottom = buttonSprite->GetFrameHeight();
	r.right = buttonSprite->GetFrameWidth();
	bounds = r;
	
	buttonSprite->SetPositionAbsolute(bounds.left + (buttonSprite->GetFrameWidth()/2), bounds.top + (buttonSprite->GetFrameHeight()/2));
}

void BuildingButtonControl::PauseAnimation(bool pause)
{
	if (pause)
	{
		buttonSprite->SetAutoAnimate(false);
		m_wasPaused = true;
	}
	else if (m_active)
	{
		buttonSprite->SetAutoAnimate(true);
	}
}

void BuildingButtonControl::ShowBuildAnimation()
{
	m_showBuildAnimation = true;
	buildSprite = graphics_engine->CreateSprite1(true,700);
	buildSprite->SetImage(CR::AssetList::Building_HUD_Dust);
	buildSprite->SetDesignSize(66, 36);
	buildSprite->SetAutoAnimate(true);
	buildSprite->SetFrame(0);
	buildSprite->SetPositionAbsolute(bounds.left + (buttonSprite->GetFrameWidth()/2), bounds.top + (buttonSprite->GetFrameHeight()/2));
	buildSprite->AutoStopAnimate();
	
	fadeColor = CR::Math::Color32(255, 255, 255, 0);
	alphaStep = 3;//255 / 60;
}

void BuildingButtonControl::Activate()
{
	m_active = true;
	buttonSprite->SetAutoAnimate(true);
	m_touchID = -1;
}

void BuildingButtonControl::CancelIfDown()
{
	if (m_touchID != -1)
	{
		Activate();
	}
}

void BuildingButtonControl::TouchesBeganImpl(Touch &_touches)
{	
	if (m_touchID != -1 && m_touchID != _touches.ID)
		return;
		
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		m_touchID = _touches.ID;
			
		if (!m_active)
		{
			std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
			sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::building_notcharged_1a::ID);
			sound->Play();
			return;
		}
			
		OnDown(m_tag);
	}
}

void BuildingButtonControl::TouchesMovedImpl(Touch &_touches)
{
	if (!m_active || m_touchID != -1)
	{		
		return;
	}
	
	if (m_touchID != -1 && _touches.ID != m_touchID)
		return;
		
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		// TODO: Test this
		m_touchID = _touches.ID;
		OnDown(m_tag);
	}
}

void BuildingButtonControl::TouchesEndedImpl(Touch &_touches)
{
	if (_touches.ID == m_touchID)
	{
		if (m_active)
		{
			StartCountDown();
			OnUp(m_tag);
		}
			
		m_touchID = -1;
	}
}

void BuildingButtonControl::SetDesignSize(int _width, int _height)
{
	buttonSprite->SetDesignSize(_width, _height);
}