/*
 *  Game.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/21/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
//#import <Foundation/Foundation.h>
#include "Input_Engine.h"
//#include "CRSoundPlayer.h"
//#include "CRMusicPlayer.h"
#include "MainMenuGameState.h"
#include "StoryModeGameState.h"
#include "ArcadeModeGameState.h"
#include "FSM.h"
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "SaveGameManager.h"
#include "Databasefwd.h"
#include <scoreloop/scoreloopcore.h>
#include <sstream>

using namespace std;

#define MAIN_MENU_STATE 0
#define STORY_MODE_STATE 1
#define ARCADE_MODE_STATE 2

class Game
	{
	public:
		Game();
		virtual ~Game();
		
		void Initialize();
		void Execute();
		void ApplicationTerminated();
		
		template<typename T>
		void SavecoreloopString(const char* _valueName, const T& _value) //should really go somewhere else
		{
			SC_Error_t errCode;
			std::stringstream tempStream;

			tempStream << _value;
			
			SC_String_h scString;
			errCode = SC_String_New(&scString, tempStream.str().c_str());
			
			if(errCode == SC_OK)
			{
				SC_Context_Put(m_ScoreloopContext, _valueName, scString);
			}
		}
		
		template<typename T>
		void LoadScoreloopValue(const char* _valueName, T& _value, T _defaultValue) //should really go somewhere else
		{
			SC_String_h scString;
			SC_Error_t errCode;
			std::stringstream tempStream;
			
			errCode = SC_Context_Get(m_ScoreloopContext, _valueName, &scString);
			if(errCode != SC_OK)
			{
				_value = _defaultValue;
			}
			else
			{
				tempStream.str(SC_String_GetData(scString));
				tempStream >> _value;
			}
		}

		SC_Client_h GetScoreloopClient() const { return m_ScoreloopClient; }
		SC_Context_h GetScoreloopContext() const { return m_ScoreloopContext; }

		void ScoreLoopReady() { m_ScoreLoopReady = true; m_ScoreLoopSavePending = false; }
		void WaitForScoreloop();
		void SaveScoreLoop();

	private:

		CR::Utility::FSM gameStateMachine;
		CR::Database::IDatabase *m_database;
		SC_InitData_t m_ScoreloopInit;
		SC_Client_h m_ScoreloopClient;
		SC_Session_h m_ScoreloopSession;
		SC_User_h m_ScoreloopUser;
		SC_Context_h m_ScoreloopContext;

		SC_UserController_h m_ScoreloopUserController;
		volatile bool m_ScoreLoopReady;
		bool m_ScoreLoopSetup;
		volatile bool m_ScoreLoopSaveRequested;
		volatile bool m_ScoreLoopSavePending;
	};