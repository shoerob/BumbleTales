/*
 *  CrystalParticle.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/27/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Particle.h"
#include "Vector.h"
#include "ResourceTile.h"
#include "Globals.h"

enum CrystalParticleStyle { CPStyleLeft, CPStyleRight };

class CrystalParticle : public Particle
{
public:
	CrystalParticle(CR::Math::PointF position, CrystalParticleStyle cpStyle, ResourceType rType);
	virtual ~CrystalParticle();

	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc) {};
	void PauseAnimation(bool pause);
	
private:
	CR::Graphics::Sprite *m_sprite;	
	CR::Math::Vector3F m_velocity;
	CR::Math::Vector3F m_acceleration;
	CR::Math::PointF m_position;
	
	//int m_life;
	//int m_life_max;
	static const int anim_mod = 20;
	
	float maxTimeLeft;
	float timeLeft;
};