/*
 *  ParticleSystemManager
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/28/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ParticleSystemManager.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

ParticleSystemManager::ParticleSystemManager()
{
	CR::Graphics::Sprite *tmpSprite = graphics_engine->CreateSprite1(true, 600);
	tmpSprite->SetImage(CR::AssetList::Piece_Shatter_0);
	tmpSprite->SetDesignSize(28, 26);
	dummyParticles.push_back(tmpSprite);
	tmpSprite = graphics_engine->CreateSprite1(true, 600);
	tmpSprite->SetImage(CR::AssetList::Piece_Shatter_1);
	tmpSprite->SetDesignSize(28, 26);
	dummyParticles.push_back(tmpSprite);
	tmpSprite = graphics_engine->CreateSprite1(true, 600);
	tmpSprite->SetImage(CR::AssetList::Piece_Shatter_2);
	tmpSprite->SetDesignSize(28, 26);
	dummyParticles.push_back(tmpSprite);
	tmpSprite = graphics_engine->CreateSprite1(true, 600);
	tmpSprite->SetImage(CR::AssetList::Piece_Shatter_3);
	tmpSprite->SetDesignSize(28, 26);
	dummyParticles.push_back(tmpSprite);
	tmpSprite = graphics_engine->CreateSprite1(true, 600);
	tmpSprite->SetImage(CR::AssetList::Piece_Shatter_4);
	tmpSprite->SetDesignSize(28, 26);
	dummyParticles.push_back(tmpSprite);
	tmpSprite = graphics_engine->CreateSprite1(true, 600);
	tmpSprite->SetImage(CR::AssetList::Piece_Shatter_5);
	tmpSprite->SetDesignSize(28, 26);
	dummyParticles.push_back(tmpSprite);
	tmpSprite = graphics_engine->CreateSprite1(true, 600);
	tmpSprite->SetImage(CR::AssetList::Piece_Shatter_6);
	tmpSprite->SetDesignSize(28, 26);
	dummyParticles.push_back(tmpSprite);
}

ParticleSystemManager::~ParticleSystemManager()
{
	//for (vector<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end(); ++it)
	//{
		//it = particleSystems.erase(it);
		//delete (*it);
	//}
	
	for (int i = 0; i < particleSystems.size(); i++)
	{
		delete particleSystems[i];
	}
	
	for (int i = 0; i < dummyParticles.size(); i++)
	{
		delete dummyParticles[i];
	}
}

void ParticleSystemManager::AddParticleSystem(ParticleSystem *pSystem)
{
	particleSystems.push_back(pSystem);
}

void ParticleSystemManager::Update()
{
	for (vector<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end();)
	{
		(*it)->Update();
		if ((*it)->IsDead())
		{
			ParticleSystem *tmp = *it;
			it = particleSystems.erase(it);
			delete (tmp);
		}
		else
			it++;
	}
}

void ParticleSystemManager::Render()
{
	for (vector<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end(); it++)
	{
		(*it)->Render();
	}
}

void ParticleSystemManager::PauseAnimation(bool pause)
{
	for (vector<ParticleSystem*>::iterator it = particleSystems.begin(); it != particleSystems.end(); it++)
	{
		(*it)->PauseAnimation(pause);
	}
}