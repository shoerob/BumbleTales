/*
 *  ResourceTile.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ResourceTile.h"
#include "Graphics.h"
#include "AssetList.h"
#include "ResourcePuzzle.h"
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;

extern CR::Graphics::GraphicsEngine *graphics_engine;

ResourceTile::ResourceTile(ResourcePuzzle *parentPuzzle, int xLoc, int yLoc)
{
	m_parentPuzzle = parentPuzzle;

	//m_specialClearSprite = graphics_engine->CreateSprite1(true);
	//m_specialClearSprite->SetImage(CR::AssetList::Selector_3);
	//m_specialClearSprite->SetAutoAnimate(false);
	//showSpecialClear = false;
	
	// Generate the tile randomly
	m_tileSprite = graphics_engine->CreateSprite1(false,950);
	m_tileSprite->SetImage(CR::AssetList::Resource_Tiles);
	m_tileSprite->SetDesignSize(60, 60);
	//m_tileSprite->SetAutoAnimate(true);
	m_tileSprite->SetFrameRate(20);
	RandomizeType(NoTile);

	//this->position.X(xLoc * m_tileSprite->GetFrameWidth() + m_tileSprite->GetFrameWidth()/2 + (xLoc * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_X());
	//this->position.Y(yLoc * m_tileSprite->GetFrameHeight() + m_tileSprite->GetFrameHeight()/2 + (yLoc * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_Y());
	this->position.X(xLoc * tile_width + tile_width/2 + (xLoc * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_X());
	this->position.Y(yLoc * tile_height + tile_height/2 + (yLoc * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_Y());
	m_tileSprite->SetPositionAbsolute(position.X(), position.Y());
	
	animationStatus = AnimationOff;
	
	selectorSprite = graphics_engine->CreateSprite1(true,800);
	selectorSprite->SetImage(CR::AssetList::Selector_2);
	selectorSprite->SetDesignSize(44, 44);
	shakeToAnim = false;
	

	//sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::tanlogo::ID));
	//sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::tanlogo::ID));
	//sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::tanlogo::ID));
}

ResourceTile::~ResourceTile()
{
	this->m_tileSprite->Release();
	selectorSprite->Release();
}

void ResourceTile::Update()
{	
	if (animationStatus == AnimationOn)
	{
		/*
		// get the next node of animation
		CR::Math::PointF animPoint = animationQueue.front();
		animationQueue.pop();
		
		// set the position to the animation node
		this->position.X(animPoint.X());
		this->position.Y(animPoint.Y());
		m_tileSprite->SetPositionAbsolute(position.X(), position.Y());
		
		if (animationQueue.size() == 0)
			animationStatus = AnimationOff;
		 */
		float timePassed = Globals::Instance().GetTimer()->GetTimePassed();
		animTimeLeft -= timePassed;
		
		
		float deltaPerc = animTimeLeft / animTotalTime;
		
		this->position.X(finalAnimPoint.X() - animDelta.X() * deltaPerc);
		this->position.Y(finalAnimPoint.Y() - animDelta.Y() * deltaPerc);
		
		m_tileSprite->SetPositionAbsolute(position.X(), position.Y());
		
		
		if (animTimeLeft <= 0)
		{
			this->position.X(finalAnimPoint.X());
			this->position.Y(finalAnimPoint.Y());
			m_tileSprite->SetPositionAbsolute(finalAnimPoint.X(), finalAnimPoint.Y());
			animationStatus = AnimationOff;
			
			if (shakeToAnim)
			{
				shakeToAnim = false;
				AnimateSlideToPoint(shakeToStartPoint, animTotalTime);
			}
		}
	}
	
	if (!m_tileSprite->IsAnimating() && m_tileSprite->GetFrame() > 0)
	{
		m_tileSprite->SetFrame(0);
	}
}

void ResourceTile::AnimateSlideTo(CR::Math::PointI to_point, float timeSpan)
{
	if (animationStatus == AnimationOn)
		return;
	
	StopAnimateHint();
	
	animTotalTime = timeSpan;
	animTimeLeft = animTotalTime;
	
	CR::Math::PointF newPosition;
	newPosition.X(to_point.X() * tile_width + tile_width/2 + (to_point.X() * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_X());
	newPosition.Y(to_point.Y() * tile_height + tile_height/2 + (to_point.Y() * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_Y());
	finalAnimPoint = newPosition;
	animDelta.X(newPosition.X() - position.X());
	animDelta.Y(newPosition.Y() - position.Y());
	
	animationStatus = AnimationOn;
}

void ResourceTile::AnimateSlideIn(CR::Math::PointI from_point, CR::Math::PointI to_point, float timeSpan)
{
	this->position.X(from_point.X() * tile_width + tile_width/2 + (from_point.X() * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_X());
	this->position.Y(from_point.Y() * tile_height + tile_height/2 + (from_point.Y() * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_Y());
	m_tileSprite->SetPositionAbsolute(position.X(), position.Y());
	AnimateSlideTo(to_point, timeSpan);
}

void ResourceTile::AnimateShakeTo(AnimationDirection direction, float timeSpan)
{
	if (animationStatus == AnimationOn)
		return;
	
	StopAnimateHint();
	
	CR::Math::PointF currPos = this->position;
	CR::Math::PointF newPosition;
	
	shakeToStartPoint.X(position.X());
	shakeToStartPoint.Y(position.Y());
	
	switch (direction)
	{
		case AnimateUp:
			newPosition.X(currPos.X());
			newPosition.Y(currPos.Y() - tile_width/2 - m_parentPuzzle->Spacing());
			break;
		case AnimateDown:
			newPosition.X(currPos.X());
			newPosition.Y(currPos.Y() + tile_width/2 + m_parentPuzzle->Spacing());
			break;
		case AnimateLeft:
			newPosition.X(currPos.X() - tile_height/2 - m_parentPuzzle->Spacing());
			newPosition.Y(currPos.Y());
			break;
		case AnimateRight:
			newPosition.X(currPos.X() + tile_height/2 + m_parentPuzzle->Spacing());
			newPosition.Y(currPos.Y());
			break;
		default:
			break;
	}
	
	shakeToAnim = true;
	AnimateSlideToPoint(newPosition, timeSpan/2.0f);

	/*
	// clear the animation queue
	animationQueue = queue<CR::Math::PointF>();
	// Forward animation
	float xStep = (newPosition.X() - position.X()) / (animFrames / 2);
	float yStep = (newPosition.Y() - position.Y()) / (animFrames / 2);
	
	// interpolate all frames except final
	for (int i = 1; i < (animFrames/2) - 1; i++)
	{
		CR::Math::PointF pnt;
		pnt.X((xStep * i) + position.X());
		pnt.Y((yStep * i) + position.Y());
		animationQueue.push(pnt);
	}
	
	// final point should be exact
	animationQueue.push(newPosition);
	
	// Animation back to original position
	// interpolate all frames except final
	for (int i = 1; i < (animFrames/2) - 1; i++)
	{
		CR::Math::PointF pnt;
		pnt.X((-xStep * i) + newPosition.X());
		pnt.Y((-yStep * i) + newPosition.Y());
		animationQueue.push(pnt);
	}
	
	// final point should be exact
	animationQueue.push(currPos);
	
	animationStatus = AnimationOn;*/
}

void ResourceTile::AnimateSlideToPoint(CR::Math::PointF to_point, float timeSpan)
{
	if (animationStatus == AnimationOn)
		return;
	
	StopAnimateHint();
	
	animTotalTime = timeSpan;
	animTimeLeft = animTotalTime;
	
	//CR::Math::PointF newPosition;
	//newPosition.X(to_point.X() * tile_width + tile_width/2 + (to_point.X() * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_X());
	//newPosition.Y(to_point.Y() * tile_height + tile_height/2 + (to_point.Y() * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_Y());
	//newPosition = to_point;
	finalAnimPoint = to_point;
	animDelta.X(to_point.X() - position.X());
	animDelta.Y(to_point.Y() - position.Y());
	
	animationStatus = AnimationOn;
}

void ResourceTile::AnimateHint()
{
	//m_tileSprite->SetFrame(2);
	//m_tileSprite->AutoStopAnimate();
	m_tileSprite->SetAutoAnimate(true);
	m_tileSprite->AutoStopAnimate();
}

void ResourceTile::StopAnimateHint()
{
	m_tileSprite->SetAutoAnimate(false);
	m_tileSprite->SetFrame(0);
}

/*void ResourceTile::AnimateSpecialClearThenSlideIn(CR::Math::PointI from_point, CR::Math::PointI to_point, int animFrames)
{
	showSpecialClear = true;
	m_specialClearSprite->AutoStopAnimate();
}*/

void ResourceTile::Render()
{
	m_tileSprite->Render();
	//selectorSprite->Render();
}


void ResourceTile::PauseAnimation(bool pause)
{
	m_tileSprite->PauseAnimation(pause);
}

void ResourceTile::RandomizeType(ResourceType dropRateBonusType)
{
	// TODO: Change this hoopty code to not happen here for speed purposes
	int dropRates[8] = { 16, 32, 48, 64, 80, 96, 98, 100 };
	if (dropRateBonusType != NoTile)
	{
		int pCount = 0;
		for (int i = 0; i < 6; i++)
		{
			if (i == (int)dropRateBonusType)
				pCount += 21;
			else
				pCount += 15;
			
			dropRates[i] = pCount;
		}
	}
	
	int dropPercent = (rand() % 101); // 0 to 100
	for (int i = 0; i < 8; i++)
	{
		if (dropPercent <= dropRates[i])
		{
			resourceType = (ResourceType) i;
			m_tileSprite->SetFrameSet((int)resourceType);
			break;
		}
	}
	
}

CR::Math::PointF ResourceTile::GetAbsolutePosition() const
{
	return position;
}

void ResourceTile::RenderSelectorSpecial(int _frame)
{
	//if (selectorSprite->GetImage() != CR::AssetList::Selector_2)
		selectorSprite->SetImage(CR::AssetList::Selector_2);
	selectorSprite->SetDesignSize(44, 44);
	
	selectorSprite->SetFrame(_frame);
	selectorSprite->SetPositionAbsolute(position.X(), position.Y());
	selectorSprite->SetAutoAnimate(false);
	selectorSprite->Render();
}

void ResourceTile::RenderSelectorExplode(int _frame)
{
	//if (selectorSprite->GetImage() != CR::AssetList::Selector_3)
		selectorSprite->SetImage(CR::AssetList::Selector_3);
	selectorSprite->SetDesignSize(44, 44);
	
	selectorSprite->SetFrame(_frame);
	selectorSprite->SetPositionAbsolute(position.X(), position.Y());
	selectorSprite->SetAutoAnimate(false);
	selectorSprite->Render();
}