/*
 *  ChainEffectManager.cpp
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/29/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ChainEffectManager.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

ChainEffectManager::ChainEffectManager()
{
	dummyChainSprite = graphics_engine->CreateSprite1(true, 1000);
	dummyChainSprite->SetImage(CR::AssetList::Chain_Match_Tags);
}

ChainEffectManager::~ChainEffectManager()
{
	dummyChainSprite->Release();
	
	for (int i = 0; i < chainEffects.size(); i++)
		delete chainEffects[i];
}

void ChainEffectManager::Update()
{
	for (vector<ChainEffect*>::iterator it = chainEffects.begin(); it != chainEffects.end();)
	{
		(*it)->Update();
		
		if ((*it)->IsDead())
		{
			ChainEffect *tmp = (*it);
			it = chainEffects.erase(it);
			delete (tmp);
		}
		else
			it++;
	}
}

void ChainEffectManager::Render()
{
	for (int i = 0; i < chainEffects.size(); i++)
		chainEffects[i]->Render();
}

void ChainEffectManager::AddChainEffect(int amount, int xLoc, int yLoc)
{
	if (amount < 2)
		return;
	
	ChainEffect *effect = new ChainEffect(amount, xLoc, yLoc);
	chainEffects.push_back(effect);
}