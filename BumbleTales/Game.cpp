/*
 *  Game.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/21/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "Game.h"
#include "Graphics.h"
#include "Globals.h"
#include "Database.h"
#include "StringUtil.h"
#include <string>
#include "Sound.h"
#include "NewAssetList.h"

using namespace std;
using namespace CR::Utility;
using namespace CR::Database;
using namespace CR::Sound;

CR::Graphics::GraphicsEngine *graphics_engine = 0;
SaveGameManager *saveGameManager = 0;
//SavedGame *saved_game = 0;
Input_Engine *input_engine = 0;
//CRSoundPlayer *soundPlayer = 0;
//CRMusicPlayer *musicPlayer = 0;

Game::Game()
{
}

Game::~Game()
{
	m_database->Release();
}

void Game::Initialize()
{
	srand(time(NULL));
	
	graphics_engine = GetGraphicsEngine();
	graphics_engine->SetBackgroundColor(0, 0, 0);
	
	graphics_engine->ShowFPS(true);
	graphics_engine->ShowSceneGraphCount(true);
	
	//saved_game = new SavedGame();
	//saved_game->Load();
	saveGameManager = new SaveGameManager();
	
	// load the main graphics file
	//NSString *path = [[NSBundle mainBundle] pathForResource: @"main" ofType: @"hgf"];
	//const char *mainhgf = [path UTF8String];
	//graphics_engine->LoadHGF(const_cast<char*>(mainhgf));
	graphics_engine->LoadHGF("main.hgf");
		
	// load the database
	//NSString *dbpath = [[NSBundle mainBundle] pathForResource: @"data" ofType: @"edf"];
	//const char *dbFile = [dbpath UTF8String];
	//string dbFilemb(dbFile);
	//Convert converter;
	//wstring dbFilewc = converter(dbFilemb);
	m_database = DatabaseFactory::Instance().CreateDatabase(L"data.edf");
	
	ISound::Instance().SetDatabase(m_database);
	
	SettingsSaveInfo *saveInfo = saveGameManager->LoadSettingsSaveInfo();
	ISound::Instance().MuteMusic(!saveInfo->GetOptionsMusicOn());
	ISound::Instance().MuteSounds(!saveInfo->GetOptionsSoundOn());
	
	// set up the game states
	gameStateMachine << new MainMenuGameState() << new StoryModeGameState() << new ArcadeModeGameState();
	gameStateMachine.State = MAIN_MENU_STATE;
}

void Game::Execute()
{	
	gameStateMachine();
	Globals::Instance().Update();
	ISound::Instance().Tick();
}

void Game::ApplicationTerminated()
{
	saveGameManager->SaveOnTerminate();
}
