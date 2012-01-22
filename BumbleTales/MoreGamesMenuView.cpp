/*
 *  MoreGamesMenuView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/25/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "MoreGamesMenuView.h"
#include "AssetList.h"
//#include <UIKit/UIApplication.h>

extern CR::Graphics::GraphicsEngine *graphics_engine;
extern Input_Engine *input_engine;

MoreGamesMenuView::MoreGamesMenuView()
{
	menuBackground = graphics_engine->CreateSprite1(false,1000);
	menuBackground->SetImage(CR::AssetList::InfoHelp_Background);
	menuBackground->SetPositionAbsolute(160, 240);
	
	titleSprite = graphics_engine->CreateSprite1(false,500);
	titleSprite->SetImage(CR::AssetList::InfoHelp_More_Games);
	titleSprite->SetPositionAbsolute(160, 40);
	
	exitButton = new Input_Button();
	exitButton->SetSpriteAndBounds(82, 432, CR::AssetList::InfoHelp_Main_Menu_Button, 500);
	exitButton->OnClicked += Delegate(this, &MoreGamesMenuView::OnExitButtonClicked);
	exitButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(exitButton);
	
	BoBButton = new Input_Button();
	BoBButton->SetSpriteAndBounds(10, 85, CR::AssetList::InfoHelp_BoB_Button, 500);
	BoBButton->OnClicked += Delegate(this, &MoreGamesMenuView::OnBoBClicked);
	BoBButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(BoBButton);
	
	AFTBButton = new Input_Button();
	AFTBButton->SetSpriteAndBounds(10, 210, CR::AssetList::InfoHelp_AFTB_Button, 500);
	AFTBButton->OnClicked += Delegate(this, &MoreGamesMenuView::OnAFTBClicked);
	AFTBButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(AFTBButton);
	
	DOHButton = new Input_Button();
	DOHButton->SetSpriteAndBounds(11, 335, CR::AssetList::InfoHelp_DoH_Button, 500);
	DOHButton->OnClicked += Delegate(this, &MoreGamesMenuView::OnDOHClicked);
	DOHButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(DOHButton);
}

MoreGamesMenuView::~MoreGamesMenuView()
{
	menuBackground->Release();
	titleSprite->Release();
	delete exitButton;
	delete BoBButton;
	delete AFTBButton;
	delete DOHButton;
}

void MoreGamesMenuView::Update()
{
}

void MoreGamesMenuView::Render()
{
	graphics_engine->BeginFrame();
	
	menuBackground->Render();
	titleSprite->Render();
	BoBButton->Render();
	AFTBButton->Render();
	DOHButton->Render();
	exitButton->Render();
	
	graphics_engine->EndFrame();
}

void MoreGamesMenuView::OnExitButtonClicked()
{
	OnExitClicked();
}

void MoreGamesMenuView::OnBoBClicked()
{
	//[[UIApplication sharedApplication] openURL:[[NSURL alloc]  initWithString: [NSString stringWithCString:"http://itunes.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=308315671&mt=8"]]];
}

void MoreGamesMenuView::OnAFTBClicked()
{
	//[[UIApplication sharedApplication] openURL:[[NSURL alloc]  initWithString: [NSString stringWithCString:"http://itunes.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=299230440&mt=8"]]];
}

void MoreGamesMenuView::OnDOHClicked()
{
	//[[UIApplication sharedApplication] openURL:[[NSURL alloc]  initWithString: [NSString stringWithCString:"http://www.domainofheroes.com/"]]];
}
