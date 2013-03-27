/*
 *  CrystalParticle.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/27/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "CrystalParticle.h"
#include "AssetList.h"
#include "Graphics.h"
#include "Color.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

CrystalParticle::CrystalParticle(CR::Math::PointF position, CrystalParticleStyle cpStyle, ResourceType rType)
{
	m_sprite = graphics_engine->CreateSprite1(true,600);
	maxTimeLeft = 1.0 + FloatRand(1.0);
	timeLeft = maxTimeLeft;
	
	switch (rType)
	{
		case Leaf:
			m_sprite->SetImage(CR::AssetList::Piece_Shatter_3);
			m_sprite->SetDesignSize(28, 26);
			break;
		case Brick:
			m_sprite->SetImage(CR::AssetList::Piece_Shatter_1);
			m_sprite->SetDesignSize(28, 26);
			break;
		case Wood:
			m_sprite->SetImage(CR::AssetList::Piece_Shatter_2);
			m_sprite->SetDesignSize(28, 26);
			break;
		case Crystal:
			m_sprite->SetImage(CR::AssetList::Piece_Shatter_4);
			m_sprite->SetDesignSize(28, 26);
			break;
		case Diamond:
			m_sprite->SetImage(CR::AssetList::Piece_Shatter_6);
			m_sprite->SetDesignSize(28, 26);
			break;
		case Gold:
			m_sprite->SetImage(CR::AssetList::Piece_Shatter_5);
			m_sprite->SetDesignSize(28, 26);
			break;
		case MTile:
			m_sprite->SetImage(CR::AssetList::Piece_Shatter_0);
			m_sprite->SetDesignSize(28, 26);
			break;
		case QTile:
			m_sprite->SetImage(CR::AssetList::Piece_Shatter_0);
			m_sprite->SetDesignSize(28, 26);
			break;
		default:
			m_sprite->SetImage(CR::AssetList::Piece_Shatter_0);
			m_sprite->SetDesignSize(28, 26);
	}

	int xMod = 0;
	if (cpStyle == CPStyleLeft)
	{
		xMod = -1;
	}
	else
	{
		xMod = 1;
	}
	
	float yVel = -4.0f;
	//float xAcc = -0.07f;
	float xAcc = FloatRand(0.4f) + 0.1f;
	float yAcc = FloatRand(0.8f) + 0.6f;
	
	m_velocity = CR::Math::Vector3F(0.0f, yVel, 0.0f);
	m_acceleration = CR::Math::Vector3F(xAcc * xMod, yAcc, 0.0f);
	

	//m_life = 50;
	//m_life_max = m_life;
	m_isDead = false;
	m_position = position;
}

CrystalParticle::~CrystalParticle()
{
	m_sprite->Release();
}

void CrystalParticle::Update()
{
	float timePassed = Globals::Instance().GetTimer()->GetTimePassed();
	timeLeft -= timePassed;
	
	if (timeLeft <= 0)
	{
		m_isDead = true;
		return;
	}
	
	if (timeLeft <= 0.5f)
	{
		CR::Math::Color32 color = CR::Math::Color32(255, 255, 255, 255 * (timeLeft / 0.5) );
		m_sprite->Color(color);
	}
	
	//float deltaPerc = 1.0 - (timeLeft / maxTimeLeft);
	
	/*
	if (m_life > 0)
	{
		m_life--;
		
		CR::Math::Color32 color = CR::Math::Color32(255, 255, 255, ((255/m_life_max) * m_life));
		m_sprite->Color(color);
				
		if (m_life <= 0)
			m_isDead = true;
	}
	*/
	
	m_sprite->SetPositionAbsolute(m_position.X(), m_position.Y());
	m_velocity.X((m_velocity.X())+ m_acceleration.X() * (timePassed * anim_mod));
	m_velocity.Y((m_velocity.Y()) + m_acceleration.Y() * (timePassed* anim_mod));
	m_position.X(m_position.X() + m_velocity.X());
	m_position.Y(m_position.Y() + m_velocity.Y());
}

void CrystalParticle::Render()
{
	m_sprite->Render();
}

void CrystalParticle::PauseAnimation(bool pause)
{
	m_sprite->PauseAnimation(pause);
}