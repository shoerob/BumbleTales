/*
 *  SplashScreenMenuView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "Input_Engine.h"
#include "Event.h"
#include "Graphics.h"
#include "IView.h"
#include "SplashScreen.h"
#include "Sound.h"

class SplashScreenMenuView : public IView
{
public:
	SplashScreenMenuView();
	virtual ~SplashScreenMenuView();
	
	void Update();
	void Render();
	
	void OnSplashScreen1Done();
	void OnSplashScreen2Done();
	
	Event ExitSplashScreen;
	
private:
	SplashScreen *m_splashScreen;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> tandemSound;
};