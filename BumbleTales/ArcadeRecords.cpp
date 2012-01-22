/*
 *  ArcadeRecords.cpp
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/16/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ArcadeRecords.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

ArcadeRecords::ArcadeRecords()
{
	bgSprite = graphics_engine->CreateSprite1(false, 300);
	bgSprite->SetImage(CR::AssetList::Scrapbook_Records_Base_2);
	bgSprite->SetPositionAbsolute(160, 250);
	
	bigNumFont = new NumberFont(CR::AssetList::Scrapbook_Font_Records_2, 200);
	bigNumFont->SetAlignment(AlignFontRight);
	
	smallNumFont = new NumberFont(CR::AssetList::Scrapbook_Font_Records_1, 200);
	smallNumFont->SetAlignment(AlignFontRight);
	
	timeDisplay = new TimeDisplay();
	timeDisplay->SetFontAsset(CR::AssetList::Scrapbook_Font_Records_1);
}

ArcadeRecords::~ArcadeRecords()
{
	bgSprite->Release();
	delete bigNumFont;
	delete smallNumFont;
	delete timeDisplay;
}

void ArcadeRecords::Update()
{
}

void ArcadeRecords::Render()
{
	bgSprite->Render();
	
	smallNumFont->Begin();
	bigNumFont->Begin();
	
	bigNumFont->SetAlignment(AlignFontRight);
	bigNumFont->SetPosition(50, 135);
	bigNumFont->RenderNumber(highScores[0]);
	bigNumFont->SetPosition(50, 160);
	bigNumFont->RenderNumber(highScores[1]);
	bigNumFont->SetPosition(50, 186);
	bigNumFont->RenderNumber(highScores[2]);
	bigNumFont->SetPosition(50, 212);
	bigNumFont->RenderNumber(highScores[3]);
	bigNumFont->SetPosition(50, 238);
	bigNumFont->RenderNumber(highScores[4]);

	/*
	bigNumFont->SetAlignment(AlignFontRight);
	bigNumFont->SetPosition(260, 135);
	bigNumFont->RenderNumber(highScoresLevels[0]);
	bigNumFont->SetPosition(260, 160);
	bigNumFont->RenderNumber(highScoresLevels[1]);
	bigNumFont->SetPosition(260, 186);
	bigNumFont->RenderNumber(highScoresLevels[2]);
	bigNumFont->SetPosition(260, 212);
	bigNumFont->RenderNumber(highScoresLevels[3]);
	bigNumFont->SetPosition(260, 238);
	bigNumFont->RenderNumber(highScoresLevels[4]);
	*/
	
	
	bigNumFont->SetAlignment(AlignFontLeft);
	bigNumFont->SetPosition(310, 135);
	bigNumFont->RenderNumber(highScoresLevels[0]);
	bigNumFont->SetPosition(310, 160);
	bigNumFont->RenderNumber(highScoresLevels[1]);
	bigNumFont->SetPosition(310, 186);
	bigNumFont->RenderNumber(highScoresLevels[2]);
	bigNumFont->SetPosition(310, 212);
	bigNumFont->RenderNumber(highScoresLevels[3]);
	bigNumFont->SetPosition(310, 238);
	bigNumFont->RenderNumber(highScoresLevels[4]);
	

	
	smallNumFont->SetAlignment(AlignFontLeft);
	smallNumFont->SetPosition(160, 279);
	smallNumFont->RenderNumber(largestMatch);

	smallNumFont->SetPosition(310, 279);
	smallNumFont->RenderNumber(largestChain);

	smallNumFont->SetPosition(310, 305);
	smallNumFont->RenderNumber(maxPointsOnSingleMove);

	smallNumFont->SetPosition(310, 333);
	smallNumFont->RenderNumber(highestNumMoves);
	
	smallNumFont->SetPosition(310, 361);
	smallNumFont->RenderNumber(mostPowersUsed);
	
	//smallNumFont->SetPosition(310, 391);
	//smallNumFont->RenderNumber(longestSession);
	timeDisplay->SetPosition(262, 391);
	timeDisplay->Render();
	
	bigNumFont->End();
	smallNumFont->End();
}

void ArcadeRecords::SetPosition(float xLoc, float yLoc)
{
}

void ArcadeRecords::PauseAnimation(bool pause)
{
}

void ArcadeRecords::LoadFromArcadeSaveInfo(ArcadeModeSaveInfo *saveInfo)
{
	highScores = saveInfo->GetHighScores();
	highScoresLevels = saveInfo->GetHighScoresLevels();
	largestMatch = saveInfo->GetLargestMatch();
	largestChain = saveInfo->GetLargestChain();
	maxPointsOnSingleMove = saveInfo->GetMaxPointsOnOneMove();
	highestNumMoves = saveInfo->GetMaxMovesInSession();
	mostPowersUsed = saveInfo->GetMaxPowersUsedInSession();
	longestSession = saveInfo->GetLongestSessionTime();
	
	timeDisplay->SetSeconds(longestSession);
}