/*
 *  Game.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/21/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "s3e.h" 
#include "Game.h"
#include "Graphics.h"
#include "Globals.h"
#include "Database.h"
#include "StringUtil.h"
#include <string>
#include "Sound.h"
#include "NewAssetList.h"
#include "AppConfig.h"

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

namespace
{
	void ScoreloopControllercallback(void* _gameClass, SC_Error_t _completionStatus) 
	{
		Game* game = reinterpret_cast<Game*>(_gameClass);
		if(_completionStatus != SC_OK)
		{
			AppConfig::Instance().DisableScoreloop();
		}
		game->ScoreLoopReady();
	}
}

Game::Game() : m_ScoreLoopSavePending(false), m_ScoreLoopSaveRequested(false)
{
	SC_Error_t errCode;
	//scoreloop, get this started asap
	if(AppConfig::Instance().UseScoreloop())
	{
		m_ScoreloopInit.clientType = 0;

		SC_InitData_Init(&m_ScoreloopInit);
		const char* scoreGameID = "c42dcddd-2b24-497c-8da5-5c5513b4fc49";
		const char* scoreGameSecret = "ax2+Lwci2+vBULlaBf0FJ3YDvLZqLUa3nTDwN1CRmEn8zMurC/gAMg==";
		const char* scoreGameCurrency = "JHL";

		errCode = SC_Client_New(&m_ScoreloopClient, &m_ScoreloopInit, scoreGameID, 
			scoreGameSecret, "1.0", scoreGameCurrency, "en");
		if(errCode != SC_OK)
		{
			AppConfig::Instance().DisableScoreloop();
		}
	}
	if(AppConfig::Instance().UseScoreloop())
	{
		m_ScoreloopSession = SC_Client_GetSession(m_ScoreloopClient);

		/*errCode = SC_Context_New(&m_ScoreloopContext);
		if(errCode != SC_OK)
		{
			AppConfig::Instance().DisableScoreloop();
		}*/
	}
	if(AppConfig::Instance().UseScoreloop())
	{
		SC_SessionState_tag sessionState = SC_Session_GetState(m_ScoreloopSession);
		m_ScoreLoopReady = false;
		errCode = SC_Client_CreateUserController(m_ScoreloopClient, &m_ScoreloopUserController, ScoreloopControllercallback, this);
		
		if(errCode != SC_OK)
		{
			AppConfig::Instance().DisableScoreloop();
		}
	}
	if(AppConfig::Instance().UseScoreloop())
	{
		errCode = SC_UserController_LoadUserContext(m_ScoreloopUserController);
		if(errCode != SC_OK)
		{
			AppConfig::Instance().DisableScoreloop();
		}
	}
}

Game::~Game()
{
	m_database->Release();
	if(AppConfig::Instance().UseScoreloop())
	{
		SC_Client_Release(m_ScoreloopClient);
	}
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

	m_ScoreLoopSetup = false;
	/*if(AppConfig::Instance().UseScoreloop())
	{
		SC_SessionState_tag sessionState = SC_Session_GetState(m_ScoreloopSession);
		while(!m_ScoreLoopReady)
		{
			s3eDeviceYield(100); 
		}
	}
	if(AppConfig::Instance().UseScoreloop())
	{
		m_ScoreloopUser = SC_Session_GetUser(m_ScoreloopSession);
		m_ScoreloopContext = SC_User_GetContext(m_ScoreloopUser);
	}*/
}

void Game::WaitForScoreloop()
{
	if(AppConfig::Instance().UseScoreloop())
	{
		if(!m_ScoreLoopSetup)
		{
			SC_SessionState_tag sessionState = SC_Session_GetState(m_ScoreloopSession);
			while(!m_ScoreLoopReady)
			{
				s3eDeviceYield(100); 
			}
			
			if(AppConfig::Instance().UseScoreloop())
			{
				m_ScoreloopUser = SC_Session_GetUser(m_ScoreloopSession);
				m_ScoreloopContext = SC_User_GetContext(m_ScoreloopUser);
			}
		}
	}
}

void Game::SaveScoreLoop()
{
	m_ScoreLoopSaveRequested = true;
}

void Game::Execute()
{	
	if(AppConfig::Instance().UseScoreloop())
	{
		if(m_ScoreLoopSaveRequested && !m_ScoreLoopSavePending)
		{
			SC_UserController_UpdateUserContext(m_ScoreloopUserController);
			m_ScoreLoopSavePending = true;
			m_ScoreLoopSaveRequested = false;
		}
	}

	gameStateMachine();
	Globals::Instance().Update();
	ISound::Instance().Tick();
}

void Game::ApplicationTerminated()
{
	saveGameManager->SaveOnTerminate();
}
