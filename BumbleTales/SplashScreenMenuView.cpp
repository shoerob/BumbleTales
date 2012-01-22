/*
 *  SplashScreenMenuView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SplashScreenMenuView.h"
#include "AssetList.h"
#include "NewAssetList.h"

using namespace CR::Sound;

SplashScreenMenuView::SplashScreenMenuView()
{
	tandemSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::tanlogo::ID);
	m_splashScreen = new SplashScreen(CR::AssetList::Splash_Screen_1, 2.0f, 1000);
	m_splashScreen->SplashFinished += Delegate(this, &SplashScreenMenuView::OnSplashScreen1Done);
	m_splashScreen->StartSplash();
	tandemSound->Play();
}

SplashScreenMenuView::~SplashScreenMenuView()
{
	delete m_splashScreen;
}

void SplashScreenMenuView::Update()
{
	m_splashScreen->Update();
}

void SplashScreenMenuView::Render()
{
	m_splashScreen->ForceRender();
}

void SplashScreenMenuView::OnSplashScreen1Done()
{
	m_splashScreen->SplashFinished.Clear();
	m_splashScreen->SplashFinished += Delegate(this, &SplashScreenMenuView::OnSplashScreen2Done);
	m_splashScreen->SetSplashAsset(CR::AssetList::Splash_Screen_2, 2.0f);
	m_splashScreen->StartSplash();
}

void SplashScreenMenuView::OnSplashScreen2Done()
{
	ExitSplashScreen();
}