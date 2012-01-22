/*
 *  ParticleSystem.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/27/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include <vector>
#include "Particle.h"
#include "Point.h"
#include "IRenderable.h"
using namespace std;

class ParticleSystem : public IRenderable
{
public:
	ParticleSystem();
	
	virtual ~ParticleSystem();
	
	virtual void Update() = 0;
	virtual void Render() = 0;
	
float IsDead() const { return m_isDead; }
protected:
	bool m_isDead;
	
	float FloatRand( float MaxVal )
	{
		return ( (float)rand( ) / (float)RAND_MAX ) * MaxVal;	
	}
};