/*
 *  StoryRecords.cpp
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/16/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "StoryRecords.h"
#include "AssetList.h"
#include "ResourceTile.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

StoryRecords::StoryRecords()
{
	bgSprite = graphics_engine->CreateSprite1(false, 300);
	bgSprite->SetImage(CR::AssetList::Scrapbook_Records_Base_1);
	bgSprite->SetDesignSize(320, 347);
	bgSprite->SetPositionAbsolute(160, 250);
	
	specialFont = new NumberFont(CR::AssetList::Scrapbook_Font_Records_1, 200);
	specialFont->SetDesignSize(12, 16);
	specialFont->SetAlignment(AlignFontRight);
	
	smallNumFont = new NumberFont(CR::AssetList::Scrapbook_Font_Records_1, 200);
	smallNumFont->SetDesignSize(12, 16);
	smallNumFont->SetAlignment(AlignFontRight);
}

StoryRecords::~StoryRecords()
{
	bgSprite->Release();
	delete smallNumFont;
	delete specialFont;
}

void StoryRecords::Update()
{
}

void StoryRecords::Render()
{
	bgSprite->Render();
	
	smallNumFont->Begin();
	
	smallNumFont->SetAlignment(AlignFontLeft);
	smallNumFont->SetPosition(310, 95);
	smallNumFont->RenderNumber(currentLevel);

	smallNumFont->SetPosition(272, 122);
	smallNumFont->RenderNumber(purchaseCompletion);
	specialFont->SetPosition(273, 122);
	specialFont->RenderSpecial(12);
	smallNumFont->SetAlignment(AlignFontRight);
	smallNumFont->SetPosition(286, 122);
	smallNumFont->RenderNumber(90);
	
	smallNumFont->SetAlignment(AlignFontLeft);
	smallNumFont->SetPosition(310, 148);
	smallNumFont->RenderNumber(largestMatch);

	smallNumFont->SetPosition(310, 174);
	smallNumFont->RenderNumber(largestChain);

	smallNumFont->SetPosition(152, 236);
	smallNumFont->RenderNumber(blocksCleared[Brick]);
	smallNumFont->SetPosition(152, 267);
	smallNumFont->RenderNumber(blocksCleared[Wood]);
	smallNumFont->SetPosition(152, 298);
	smallNumFont->RenderNumber(blocksCleared[Leaf]);
	smallNumFont->SetPosition(152, 329);
	smallNumFont->RenderNumber(blocksCleared[QTile]);
	
	smallNumFont->SetPosition(290, 236);
	smallNumFont->RenderNumber(blocksCleared[Gold]);
	smallNumFont->SetPosition(290, 267);
	smallNumFont->RenderNumber(blocksCleared[Crystal]);
	smallNumFont->SetPosition(290, 298);
	smallNumFont->RenderNumber(blocksCleared[Diamond]);
	smallNumFont->SetPosition(290, 329);
	smallNumFont->RenderNumber(blocksCleared[MTile]);
	
	smallNumFont->SetPosition(121, 396);
	//smallNumFont->SetAlignment(AlignFontRight);
	//smallNumFont->SetPosition(55, 396);
	smallNumFont->RenderNumber(bronzeMedals);
	
	smallNumFont->SetPosition(218, 396);
	//smallNumFont->SetPosition(154, 396);
	smallNumFont->RenderNumber(silverMedals);

	smallNumFont->SetPosition(315, 396);
	//smallNumFont->SetPosition(253, 396);
	smallNumFont->RenderNumber(goldMedals);
	
	smallNumFont->End();
}

void StoryRecords::SetPosition(float xLoc, float yLoc)
{
}

void StoryRecords::PauseAnimation(bool pause)
{
}

void StoryRecords::LoadFromStorySaveInfo(StoryModeSaveInfo *saveInfo)
{
	currentLevel = saveInfo->GetLevel();
	//purchaseCompletion = 0;
	largestMatch = saveInfo->GetLargestMatch();
	largestChain = saveInfo->GetLargestChain();
	blocksCleared = saveInfo->GetBlocksCleared();
	bronzeMedals = saveInfo->GetBronzeMedals();
	silverMedals = saveInfo->GetSilverMedals();
	goldMedals = saveInfo->GetGoldMedals();
	
	// Calculate Purchase Completion
	purchaseCompletion = 0;
	
	BuildingLevels *bLevels = saveInfo->GetBuildingLevels();
	purchaseCompletion += bLevels->GetBuildingLevel(TownHall);
	purchaseCompletion += bLevels->GetBuildingLevel(PoliceStation);
	purchaseCompletion += bLevels->GetBuildingLevel(Firehouse);
	purchaseCompletion += bLevels->GetBuildingLevel(Lodge);
	purchaseCompletion += bLevels->GetBuildingLevel(Theatre);
	purchaseCompletion += bLevels->GetBuildingLevel(Greenhouse);
	//delete bLevels;
	
	CharacterLevels *cLevels = saveInfo->GetCharacterLevels();
	purchaseCompletion += cLevels->GetCharacterLevel(Mayor);
	purchaseCompletion += cLevels->GetCharacterLevel(Elder);
	purchaseCompletion += cLevels->GetCharacterLevel(Fireman);
	purchaseCompletion += cLevels->GetCharacterLevel(Dog);
	purchaseCompletion += cLevels->GetCharacterLevel(Baker);
	purchaseCompletion += cLevels->GetCharacterLevel(Teacher);
	purchaseCompletion += cLevels->GetCharacterLevel(Librarian);
	purchaseCompletion += cLevels->GetCharacterLevel(Romeo);
	purchaseCompletion += cLevels->GetCharacterLevel(Felicia);
	purchaseCompletion += cLevels->GetCharacterLevel(Bruiser);
	purchaseCompletion += cLevels->GetCharacterLevel(Marla);
	purchaseCompletion += cLevels->GetCharacterLevel(ChopChop);
	//delete cLevels;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}