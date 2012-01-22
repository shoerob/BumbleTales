/*
 *  ResourcePuzzle.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ResourcePuzzle.h"
#include "AssetList.h"
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;

extern CR::Graphics::GraphicsEngine *graphics_engine;

const float ResourcePuzzle::anim_fps = 0.15f;

ResourcePuzzle::ResourcePuzzle(int xLoc, int yLoc, int spacing) : m_touchID(-1)
{
	maxHintTime = 10;
	currHintTime = maxHintTime;
	hintOffset.X(0);
	hintOffset.Y(0);
	hintsEnabled = true;
	chainManager = new ChainEffectManager();
	chainCount = 0;
	particleSystemManager = new ParticleSystemManager();
	tile_spacing = spacing;
	offset = CR::Math::PointF(xLoc, yLoc, 0);
	tileSelector = new TileSelector(this);
	tileSelector->SetVisible(false);
	m_isAnimating = false;
	
	// initialize the puzzle with tiles
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			ResourceTile *tmpTile = new ResourceTile(this, x, y);
			resourceTiles[x][y] = tmpTile;
			
			// initialize the special clear tiles with false
			specialClearTiles[x][y] = false;
		}
	}
	
	ResetPuzzle(); // make sure there are no matches in initial puzzle
	hideTileSelectorAfterAnimation = false;
	m_dropRateBonusType = NoTile;
	m_buildingSpecialDown = false;
	specialSelector = new SpecialSelector(this);
	specialSelector->OnDoneAnimating += Delegate(this, &ResourcePuzzle::OnClearBuildingSpecialTiles);
	specialSelector->OnExplodeTiles += Delegate(this, &ResourcePuzzle::OnExplodeTilesSpecial);
	
	resetBoardSprite = graphics_engine->CreateSprite1(false, 750);
	resetBoardSprite->SetImage(CR::AssetList::No_Moves_Cover);
	resetBoardSprite->SetPositionAbsolute(160, 228);
	resettingPuzzle = false;

	touchAllowed = true;
	
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::leaves1::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::leaves2::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::brick1::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::brick2::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::wood::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::wood::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::crystal1::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::crystal2::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::crystal1::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::crystal2::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::gold1::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::gold2::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::mpiece::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::mpiece::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::mpiece::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::mpiece::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::slide1b::ID));//16
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::slide2b::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::slide3b::ID));
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::invalidpiece1b::ID));//19
	sounds.push_back(ISound::Instance().CreateSoundFX(CR::AssetList::sounds::invalidpiece2b::ID));
}

ResourcePuzzle::~ResourcePuzzle()
{
	delete chainManager;
	delete particleSystemManager;
	delete tileSelector;
	resetBoardSprite->Release();
	
	// delete all tiles in the matrix from memory
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			ResourceTile *tmpTile = GetResourceTile(x, y);
			delete tmpTile;
			resourceTiles[x][y] = NULL;
		}
	}
}

void ResourcePuzzle::Update()
{
	bool isAnimating = false;
	tileSelector->Update();
	specialSelector->Update();
	particleSystemManager->Update();
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			if (resourceTiles[x][y] != NULL)
			{
				//if (!resourceTiles[x][y]->TilePositionUpToDate())
				//	isAnimating = true;
				
				if (!resourceTiles[x][y]->TilePositionUpToDate())
					isAnimating = true;
				
				resourceTiles[x][y]->Update();
			}
		}
	}
	
	m_isAnimating = isAnimating;
	
	if (!isAnimating)
	{
		resettingPuzzle = false;
		bool foundMatch = CheckAndRemoveTileMatches();
		// if a match was found, the puzzle is going into an animated state
		if (foundMatch)
			m_isAnimating = true;
		
		// only check if the puzzle is valid if a match has not been found
		if (!foundMatch && !IsPuzzleValid())
		{
			// Puzzle is not in a valid state, tell user, then shuffle
			ResetPuzzle();
			AnimatePuzzleSlideIn();
		}
		else if (foundMatch)
		{
			FindHintBlock();
			currHintTime = maxHintTime;
		}
	}
	
	if (!m_isAnimating && hideTileSelectorAfterAnimation)
	{
		hideTileSelectorAfterAnimation = false;
		tileSelector->SetVisible(false);
	}
	
	if (!m_isAnimating)
	{
		//FindHintBlock();
		chainCount = 0;
		touchAllowed = true;
	}
	
	// Hints
	if (hintsEnabled)
	{
		currHintTime -= Globals::Instance().GetTimer()->GetTimePassed();
		
		if (currHintTime <= 0)
		{
			AnimateHint();
			currHintTime = maxHintTime;
		}
	}
	
	chainManager->Update();
}

void ResourcePuzzle::Render()
{	
	if (resettingPuzzle)
		resetBoardSprite->Render();
	
	//graphics_engine->SetClipper(offset.X(), offset.Y(), 320, 340);
	
	// render the tiles
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			if (resourceTiles[x][y] != NULL)
			{
				if (specialSelector->IsSelector3() && specialSelector->HideTiles())
				{
					if (!specialClearTiles[x][y])
					{
						resourceTiles[x][y]->Render();
					}
				}
				else
					resourceTiles[x][y]->Render();
			}
		}
	}
	
	// render the tile selector
	tileSelector->Render();
	bool specialSelectorRendered = false;
	
	// render special tile selector
	if (m_buildingSpecialDown)
	{
		for (int y = 0; y < y_tiles; y++)
		{
			for (int x = 0; x < x_tiles; x++)
			{
				if (specialClearTiles[x][y] == true)
				{
					specialSelector->SetTilePosition(x, y);
					//specialSelector->Render();
					
					if (specialSelector->IsSelector3())
						resourceTiles[x][y]->RenderSelectorExplode(specialSelector->GetCurrFrame());
					else
						resourceTiles[x][y]->RenderSelectorSpecial(specialSelector->GetCurrFrame());						
					
					specialSelectorRendered = true;
				}
			}
		}
	}
	
	if (!specialSelectorRendered)
		specialSelector->ShowSelector2();
	
	//graphics_engine->ClearClipper();
	
	particleSystemManager->Render();
	chainManager->Render();
}

void ResourcePuzzle::PauseAnimation(bool pause)
{
	tileSelector->PauseAnimation(pause);
	particleSystemManager->PauseAnimation(pause);
	specialSelector->PauseAnimation(pause);
}

void ResourcePuzzle::ResetPuzzle()
{
	bool hasMatches = true;
	
	RandomizeTiles();
	
	while (hasMatches)
	{
		hasMatches = false;
		for (int y = 0; y < y_tiles; y++)
		{
			for (int x = 0; x < x_tiles; x++)
			{
				MatchBounds hMatch = FindHorizontalMatch(x, y);
				MatchBounds vMatch = FindVerticalMatch(x, y);
				
				if (hMatch.foundMatch)
				{
					hasMatches = true;
					for (int i = hMatch.lower; i <= hMatch.upper; i++)
						GetResourceTile(i, y)->RandomizeType(m_dropRateBonusType);
				}
				
				if (vMatch.foundMatch)
				{
					hasMatches = true;
					for (int i = vMatch.lower; i <= vMatch.upper; i++)
						GetResourceTile(x, i)->RandomizeType(m_dropRateBonusType);
				}
			}
		}
		
		if (!IsPuzzleValid())
		{
			hasMatches = true;
			RandomizeTiles();
		}
		//else
		//{
		//	FindHintBlock();
		//}
	}
	
	FindHintBlock();
}

void ResourcePuzzle::AnimatePuzzleSlideIn()
{
	std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
	sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::nomoves::ID);
	sound->Play();
	
	resettingPuzzle = true;
	
	for (int x = 0; x < x_tiles; x++)
	{
		for (int y = 0; y < y_tiles; y++)
		{
			// determine points for slide in animation
			CR::Math::PointI fromPoint = CR::Math::PointI(x, y - y_tiles, 0); // from_point
			CR::Math::PointI tilePoint = CR::Math::PointI(x, y, 0); // to_point
			
			GetResourceTile(x, y)->AnimateSlideIn(fromPoint, tilePoint, anim_fps * y_tiles);
		}
	}
}

// returns true if a shake took place
bool ResourcePuzzle::AnimateShakeTiles(CR::Math::PointI tile1, CR::Math::PointI tile2)
{
	// if the tiles are not within 1 of eachother, or are diagonal from eachother, return without shaking them
	int xDiff = tile1.X() - tile2.X();
	int yDiff = tile1.Y() - tile2.Y();
	int absXDiff = abs(xDiff);
	int absYDiff = abs(yDiff);
	if ( (absXDiff > 1) || (absYDiff > 1) || (absXDiff == 1 && absYDiff == 1) )
		return false;
	
	if (xDiff == -1)
		GetResourceTile(tile1.X(), tile1.Y())->AnimateShakeTo(AnimateRight, anim_fps);
	else if (xDiff == 1)
		GetResourceTile(tile1.X(), tile1.Y())->AnimateShakeTo(AnimateLeft, anim_fps);
	else if (yDiff == -1)
		GetResourceTile(tile1.X(), tile1.Y())->AnimateShakeTo(AnimateDown, anim_fps);
	else if (yDiff == 1)
		GetResourceTile(tile1.X(), tile1.Y())->AnimateShakeTo(AnimateUp, anim_fps);
	
	int isnd = 19 + (rand() & 1);
	sounds[isnd]->Play();
	
	return true;
}

bool ResourcePuzzle::CheckAndRemoveTileMatches()
{
	// TODO: This has a bug, as it loops it removes tiles. It needs to loop, store all matches made, then remove tiles.
	// this has cause vertical rows to be removed, then if a horizontal row thats part of that vertical row has a match,
	// it doesnt get removed because one of it matching tiles has been removed so its undetectable.
	vector<MatchBounds> matches;
	queue<ResourceTile*> tileQueue; // tiles removed from puzzle that can be reused as new tiles
	int resourceCount[ResourceTile::tile_types];// = {0, 0, 0, 0, 0, 0}; // resources receieved through matches
	for (int i = 0; i < ResourceTile::tile_types; i++)
		resourceCount[i] = 0;
	
	bool foundMatch = false;
	
	// storage for the number of null tiles in each column
	int nullTiles[x_tiles];
	for (int i = 0; i < x_tiles; i++)
		nullTiles[i] = 0;
	
	// Remove all match tiles and add them to the tileQueue for reuse
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			MatchBounds hMatch = FindHorizontalMatch(x, y);
			MatchBounds vMatch = FindVerticalMatch(x, y);
			
			// Horizontal Matches
			if (hMatch.foundMatch)
			{
				foundMatch = true;
				matches.push_back(hMatch);
			}
			
			// Vertical Matches
			if (vMatch.foundMatch)
			{
				foundMatch = true;
				matches.push_back(vMatch);
			}
		}
	}
	
	// if a match was not found, there is no need to continue
	if (!foundMatch)
		return false;
	
	// remove all matches found
	bool removedMatch = false;
	
	//bool chainPositionSet = false;
	bool isChain = true;
	int xChainPos = 0;
	int yChainPos = 0;
	bool playedSound = false;
	
	for (int j = 0; j < matches.size(); j++)
	{
		MatchBounds match = matches[j];
		if (match.orientation == HorizontalMatch)
		{
			isChain = true;
			//isChain = (match.upper - match.lower) >= 2;
			if (resourceTiles[(match.lower + match.upper)/2][match.y] != NULL)
			{
				xChainPos = resourceTiles[(match.lower + match.upper)/2][match.y]->GetAbsolutePosition().X();
				yChainPos = resourceTiles[(match.lower + match.upper)/2][match.y]->GetAbsolutePosition().Y();
			}
			
			for (int i = match.lower; i <= match.upper; i++)
			{
				ResourceTile *resourceTile = GetResourceTile(i, match.y);
				if (resourceTile != NULL) 
				{
					resourceTile->StopAnimateHint();
					tileQueue.push(resourceTile);
					resourceTiles[i][match.y] = NULL;
					nullTiles[i]++;
					//resourceCount[(int)resourceTile->GetResourceType()] += (match.upper - match.lower + 1); // store resources retrieved
					resourceCount[(int)resourceTile->GetResourceType()] += 1; // store resources retrieved
					particleSystemManager->AddParticleSystem(new CrystalParticleSystem(resourceTile->GetAbsolutePosition(), resourceTile->GetResourceType()));
					removedMatch = true;
				}
				else isChain = false;
			}
			
			if (removedMatch)
			{
				playedSound = true;
				PlayResourceSound(match.qType);
				
				if (isChain)
				{
					OnIncrementChain();
					chainCount++;
					chainManager->AddChainEffect(chainCount, xChainPos, yChainPos);
				}
				
				resourceCount[(int)match.qType] += match.qTiles;
				removedMatch = false;
			}
		}
		else if (match.orientation == VerticalMatch)
		{
			isChain = true;
			//isChain = (match.upper - match.lower) >= 2;
			if (resourceTiles[match.x][(match.lower + match.upper)/2] != NULL)
			{
				xChainPos = resourceTiles[match.x][(match.lower + match.upper)/2]->GetAbsolutePosition().X();
				yChainPos = resourceTiles[match.x][(match.lower + match.upper)/2]->GetAbsolutePosition().Y();
			}
			
			for (int i = match.lower; i <= match.upper; i++)
			{
				ResourceTile *resourceTile = GetResourceTile(match.x, i);

				if (resourceTile != NULL) // check for null, a horizontal row may have removed a tile in this combination
				{
					resourceTile->StopAnimateHint();
					tileQueue.push(resourceTile);
					resourceTiles[match.x][i] = NULL;
					nullTiles[match.x]++;
					//resourceCount[(int)resourceTile->GetResourceType()] += (match.upper - match.lower + 1); // store resources retrieved
					resourceCount[(int)resourceTile->GetResourceType()] += 1; // store resources retrieved
					particleSystemManager->AddParticleSystem(new CrystalParticleSystem(resourceTile->GetAbsolutePosition(), resourceTile->GetResourceType()));
					removedMatch = true;
				}
				else isChain = false;
			}
			
			if (removedMatch)
			{
				if (!playedSound)
					PlayResourceSound(match.qType);
				
				if (isChain)
				{
					OnIncrementChain();
					chainCount++;
					chainManager->AddChainEffect(chainCount, xChainPos, yChainPos);
				}
				resourceCount[(int)match.qType] += match.qTiles;
				removedMatch = false;
			}
		}
	}
	
	// Report Resources Retrieved
	//OnIncrementChain();
	for (int i = 0; i < ResourceTile::tile_types; i++)
	{
		if (resourceCount[i] > 0)
			ResourcesRetrieved((ResourceType)i, resourceCount[i]);
	}
	
	
	tileSelector->SetVisible(false);
	
	// Shift down all tiles
	for (int x = 0; x < x_tiles; x++)
	{
		for (int y = y_tiles-1; y > 0; y--)
		{
			if (GetResourceTile(x, y) == NULL)
			{
				for (int i = y; i >=0; i--)
				{
					ResourceTile *tmpTile = GetResourceTile(x, i);
					if (tmpTile != NULL)
					{
						resourceTiles[x][i] = NULL;
						resourceTiles[x][y] = tmpTile;
						CR::Math::PointI tilePoint;
						tilePoint.X(x);
						tilePoint.Y(y);
						tmpTile->AnimateSlideTo(tilePoint, anim_fps * (y - i));
						break;
					}
				}
			}
		}
	}
	
	// Use the tiles from the tilequeue as new tiles, slide them in
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			if (resourceTiles[x][y] == NULL)
			{
				resourceTiles[x][y] = tileQueue.front();
				tileQueue.pop();
				
				resourceTiles[x][y]->RandomizeType(m_dropRateBonusType);

				// determine points for slide in animation
				CR::Math::PointI fromPoint = CR::Math::PointI(x, y - nullTiles[x], 0); // from_point
				CR::Math::PointI tilePoint = CR::Math::PointI(x, y, 0); // to_point
				
				resourceTiles[x][y]->AnimateSlideIn(fromPoint, tilePoint, anim_fps * nullTiles[x]);
			}
		}
	}
	
	return true;
}

MatchBounds ResourcePuzzle::FindHorizontalMatch(int xLoc, int yLoc)
{	
	int lower = 0;
	int upper = 0;
	bool foundMatch = false;
	bool matchEnded = false;
	int qTiles = 0;
	
	ResourceTile *resourceTile = GetResourceTile(xLoc, yLoc);
	if (resourceTile == NULL || resourceTile->GetResourceType() == QTile)
		return MatchBounds();
	
	ResourceType resourceType = resourceTile->GetResourceType();
	
	// Check Left
	for (int x = xLoc; x >= 0 && matchEnded != true; x--)
	{
		ResourceTile *tmpTile = GetResourceTile(x, yLoc);
		if (tmpTile == NULL || (tmpTile->GetResourceType() != resourceType && tmpTile->GetResourceType() != QTile))
			matchEnded = true;
		else
		{
			if (tmpTile->GetResourceType() == QTile) qTiles++;
			lower = x;
		}
	}

	// Check Right
	matchEnded = false;
	for (int x = xLoc; x < x_tiles && matchEnded != true; x++)
	{
		ResourceTile *tmpTile = GetResourceTile(x, yLoc);
		if (tmpTile == NULL || (tmpTile->GetResourceType() != resourceType && tmpTile->GetResourceType() != QTile))
			matchEnded = true;
		else
		{
			if (tmpTile->GetResourceType() == QTile) qTiles++;
			upper = x;
		}
	}
	
	if ((upper - lower) >= (tiles_required_for_match -1))
		foundMatch = true;
	
	return MatchBounds(foundMatch, HorizontalMatch, xLoc, yLoc, lower, upper, resourceTile->GetResourceType(), qTiles);
}

MatchBounds ResourcePuzzle::FindVerticalMatch(int xLoc, int yLoc)
{	
	
	// TODO: if the tile being checked is a Q tile, there needs to be a check here
	
	int lower = 0;
	int upper = 0;
	bool foundMatch = false;
	bool matchEnded = false;
	int qTiles = 0;
	
	ResourceTile *resourceTile = GetResourceTile(xLoc, yLoc);
	if (resourceTile == NULL || resourceTile->GetResourceType() == QTile)
		return MatchBounds();
	
	ResourceType resourceType = resourceTile->GetResourceType();
	
	// Check Up
	for (int y = yLoc; y >= 0 && matchEnded != true; y--)
	{
		ResourceTile *tmpTile = GetResourceTile(xLoc, y);
		if (tmpTile == NULL || (tmpTile->GetResourceType() != resourceType && tmpTile->GetResourceType() != QTile))
			matchEnded = true;
		else
		{
			if (tmpTile->GetResourceType() == QTile) qTiles++;
			lower = y;
		}
	}
	
	// Check Down
	matchEnded = false;
	for (int y = yLoc; y < y_tiles && matchEnded != true; y++)
	{
		ResourceTile *tmpTile = GetResourceTile(xLoc, y);
		if (tmpTile == NULL || (tmpTile->GetResourceType() != resourceType && tmpTile->GetResourceType() != QTile))
			matchEnded = true;
		else
		{
			if (tmpTile->GetResourceType() == QTile) qTiles++;
			upper = y;
		}
	}
	
	if ((upper - lower) >= (tiles_required_for_match-1))
		foundMatch = true;
	
	return MatchBounds(foundMatch, VerticalMatch, xLoc, yLoc, lower, upper, resourceTile->GetResourceType(), qTiles);
}

void ResourcePuzzle::SwapTiles(CR::Math::PointI tile1, CR::Math::PointI tile2)
{
	ResourceTile *rTile1 = GetResourceTile(tile1.X(), tile1.Y());
	ResourceTile *rTile2 = GetResourceTile(tile2.X(), tile2.Y());
	resourceTiles[tile1.X()][tile1.Y()] = rTile2;
	resourceTiles[tile2.X()][tile2.Y()] = rTile1;
	rTile1->AnimateSlideTo(tile2, anim_fps);
	rTile2->AnimateSlideTo(tile1, anim_fps);
	
	int isnd = 16 + (rand() % 3);
	sounds[isnd]->Play();
}

bool ResourcePuzzle::CanSwapTiles(CR::Math::PointI tile1, CR::Math::PointI tile2)
{
	// if the tiles are not within 1 of eachother, or are diagonal from eachother, return false
	int xDiff = tile1.X() - tile2.X();
	int yDiff = tile1.Y() - tile2.Y();
	int absXDiff = abs(xDiff);
	int absYDiff = abs(yDiff);
	if ( (absXDiff > 1) || (absYDiff > 1) || (absXDiff == 1 && absYDiff == 1) )
		return false;
	
	// Horizontal Swap Detected
	if (xDiff == -1)
	{
		if (CheckForRightSwapMatch(tile1.X(), tile1.Y()) || CheckForLeftSwapMatch(tile2.X(), tile2.Y()))
			return true;
	}
	else if (xDiff == 1)
	{
		if (CheckForLeftSwapMatch(tile1.X(), tile1.Y()) || CheckForRightSwapMatch(tile2.X(), tile2.Y()))
			return true;
	}
	else if (yDiff == -1) // Vertical Swap Detected
	{
		if (CheckForDownSwapMatch(tile1.X(), tile1.Y()) || CheckForUpSwapMatch(tile2.X(), tile2.Y()))
			return true;
	}
	else if (yDiff == 1)
	{
		if (CheckForUpSwapMatch(tile1.X(), tile1.Y()) || CheckForDownSwapMatch(tile2.X(), tile2.Y()))
			return true;
	}
	
	return false;
}

void ResourcePuzzle::RandomizeTiles()
{
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			resourceTiles[x][y]->RandomizeType(m_dropRateBonusType);
		}
	}
}

bool ResourcePuzzle::IsPuzzleValid()
{	
	// loop through tiles
	for (int x = 0; x < x_tiles; x++)
	{
		for (int y = 0; y < y_tiles; y++)
		{
			// left swap checks
			if (CheckForLeftMatch(x - 1, y, GetResourceTile(x, y)) ||
				CheckForUpMatch(x - 1, y, GetResourceTile(x, y)) ||
				CheckForDownMatch(x - 1, y, GetResourceTile(x, y)) ||
				CheckForMiddleVerticalMatch(x - 1, y, GetResourceTile(x, y)))
				return true;
			
			// right swap checks
			if (CheckForRightMatch(x + 1, y, GetResourceTile(x, y)) ||
				CheckForUpMatch(x + 1, y, GetResourceTile(x, y)) ||
				CheckForDownMatch(x + 1, y, GetResourceTile(x, y)) ||
				CheckForMiddleVerticalMatch(x + 1, y, GetResourceTile(x, y)))
				return true;
			
			// up swap checks
			if (CheckForLeftMatch(x, y - 1, GetResourceTile(x, y)) ||
				CheckForRightMatch(x, y - 1, GetResourceTile(x, y)) ||
				CheckForUpMatch(x, y - 1, GetResourceTile(x, y)) ||
				CheckForMiddleHorizontalMatch(x, y - 1, GetResourceTile(x, y)))
				return true;
			
			// down swap checks
			if (CheckForLeftMatch(x, y + 1, GetResourceTile(x, y)) ||
				CheckForRightMatch(x, y + 1, GetResourceTile(x, y)) ||
				CheckForDownMatch(x, y + 1, GetResourceTile(x, y)) ||
				CheckForMiddleHorizontalMatch(x, y + 1, GetResourceTile(x, y)))
				return true;
		}
	}
	
	return false;
}

bool ResourcePuzzle::CheckForLeftMatch(int x, int y, ResourceTile *rTile)
{
	if (rTile == NULL)
		return false;
	
	ResourceTile *t1;
	ResourceType rType = rTile->GetResourceType();
	
	for (int i = -1 ; i >= -2; i--)
	{
		t1 = GetResourceTile(x + i, y);
		if (t1 != NULL && rType == QTile) rType = t1->GetResourceType();
		
		if (t1 == NULL || (t1->GetResourceType() != rType && t1->GetResourceType() != QTile))
			return false;
	}

	return true;
}

bool ResourcePuzzle::CheckForRightMatch(int x, int y, ResourceTile *rTile)
{	
	if (rTile == NULL)
		return false;
	
	ResourceTile *t1;
	ResourceType rType = rTile->GetResourceType();
	
	for (int i = 1 ; i <= 2; i++)
	{
		t1 = GetResourceTile(x + i, y);
		if (t1 != NULL && rType == QTile) rType = t1->GetResourceType();
		
		if (t1 == NULL || (t1->GetResourceType() != rType && t1->GetResourceType() != QTile))
			return false;
	}
	
	return true;
	
}

bool ResourcePuzzle::CheckForUpMatch(int x, int y, ResourceTile *rTile)
{
	if (rTile == NULL)
		return false;
	
	ResourceTile *t1;
	ResourceType rType = rTile->GetResourceType();
		
	for (int i = -1 ; i >= -2; i--)
	{
		t1 = GetResourceTile(x, y + i);
		if (t1 != NULL && rType == QTile) rType = t1->GetResourceType();
		
		if (t1 == NULL || (t1->GetResourceType() != rType && t1->GetResourceType() != QTile))
			return false;
	}
	
	return true;
}

bool ResourcePuzzle::CheckForDownMatch(int x, int y, ResourceTile *rTile)
{
	if (rTile == NULL)
		return false;
	
	ResourceTile *t1;
	ResourceType rType = rTile->GetResourceType();
	
	for (int i = 1 ; i <= 2; i++)
	{
		t1 = GetResourceTile(x, y + i);
		if (t1 != NULL && rType == QTile) rType = t1->GetResourceType();
		
		if (t1 == NULL || (t1->GetResourceType() != rType && t1->GetResourceType() != QTile))
			return false;
	}
	
	return true;
}

bool ResourcePuzzle::CheckForMiddleVerticalMatch(int x, int y, ResourceTile *rTile)
{
	if (rTile == NULL)
		return false;
	
	ResourceTile *t1;
	ResourceTile *t2;
	ResourceType rType = rTile->GetResourceType();
	
	t1 = GetResourceTile(x, y - 1);
	t2 = GetResourceTile(x, y + 1);
	
	if (rType == QTile)
	{
		if (t1 != NULL && t2 != NULL && (t1->GetResourceType() == t2->GetResourceType() || (t1->GetResourceType() == QTile) || t2->GetResourceType() == QTile))
			return true;
	}
	else
	{
		if (t1 != NULL && t2 != NULL && (t1->GetResourceType() == rType || t1->GetResourceType() == QTile) && (t2->GetResourceType() == rType || t2->GetResourceType() == QTile))
			return true;
	}
	
	return false;
}

bool ResourcePuzzle::CheckForMiddleHorizontalMatch(int x, int y, ResourceTile *rTile)
{
	if (rTile == NULL)
		return false;
	
	ResourceTile *t1;
	ResourceTile *t2;
	ResourceType rType = rTile->GetResourceType();
	
	t1 = GetResourceTile(x - 1, y);
	t2 = GetResourceTile(x + 1, y);
	
	if (rType == QTile)
	{
		if (t1 != NULL && t2 != NULL && (t1->GetResourceType() == t2->GetResourceType() || (t1->GetResourceType() == QTile) || t2->GetResourceType() == QTile))
			return true;
	}
	else
	{
		if (t1 != NULL && t2 != NULL && (t1->GetResourceType() == rType || t1->GetResourceType() == QTile) && (t2->GetResourceType() == rType || t2->GetResourceType() == QTile))
			return true;
	}
	
	return false;
}

bool ResourcePuzzle::CheckForUpSwapMatch(int x, int y)
{
	if (CheckForLeftMatch(x, y - 1, GetResourceTile(x, y)) ||
		CheckForRightMatch(x, y - 1, GetResourceTile(x, y)) ||
		CheckForUpMatch(x, y - 1, GetResourceTile(x, y)) ||
		CheckForMiddleHorizontalMatch(x, y - 1, GetResourceTile(x, y)))
		return true;
	else
		return false;
}

bool ResourcePuzzle::CheckForDownSwapMatch(int x, int y)
{
	if (CheckForLeftMatch(x, y + 1, GetResourceTile(x, y)) ||
		CheckForRightMatch(x, y + 1, GetResourceTile(x, y)) ||
		CheckForDownMatch(x, y + 1, GetResourceTile(x, y)) ||
		CheckForMiddleHorizontalMatch(x, y + 1, GetResourceTile(x, y)))
		return true;
	else
		return false;
}

bool ResourcePuzzle::CheckForLeftSwapMatch(int x, int y)
{
	if (CheckForLeftMatch(x - 1, y, GetResourceTile(x, y)) ||
		CheckForUpMatch(x - 1, y, GetResourceTile(x, y)) ||
		CheckForDownMatch(x - 1, y, GetResourceTile(x, y)) ||
		CheckForMiddleVerticalMatch(x - 1, y, GetResourceTile(x, y)))
		return true;
	else
		return false;
}

bool ResourcePuzzle::CheckForRightSwapMatch(int x, int y)
{
	if (CheckForRightMatch(x + 1, y, GetResourceTile(x, y)) ||
		CheckForUpMatch(x + 1, y, GetResourceTile(x, y)) ||
		CheckForDownMatch(x + 1, y, GetResourceTile(x, y)) ||
		CheckForMiddleVerticalMatch(x + 1, y, GetResourceTile(x, y)))
		return true;
	else
		return false;
}

ResourceTile *ResourcePuzzle::GetResourceTile(int xLoc, int yLoc) const
{
	if (xLoc >= 0 && xLoc < x_tiles && yLoc >= 0 && yLoc < y_tiles)
		return resourceTiles[xLoc][yLoc];
	else
		return NULL;
}

bool ResourcePuzzle::IsPuzzleAnimating() const
{
	return m_isAnimating || specialSelector->IsSelector3();
}

void ResourcePuzzle::SetDropRateBonusType(ResourceType rType)
{
	m_dropRateBonusType = rType;
}

void ResourcePuzzle::SetBuildingSpecialDown(BuildingName bName, int level)
{
	int breakBlocks = 0;
	bool breakAllBlocks = false;
	
	tileSelector->SetVisible(false);
	
	// determine how many random blocks to mark for breaking
	if (level <= 2) breakBlocks = 3;
	else if (level <= 4) breakBlocks = 4;
	else breakAllBlocks = true;
	
	// determine the resource type
	ResourceType rType = NoTile;
	switch (bName)
	{
		case Firehouse:
			rType = Brick;
			break;
		case Lodge:
			rType = Wood;
			break;
		case Greenhouse:
			rType = Leaf;
			break;
		case TownHall:
			rType = Gold;
			break;
		case PoliceStation:
			rType = Crystal;
			break;
		case Theatre:
			rType = Diamond;
			break;
		default:
			break;
	}
	
	vector<CR::Math::PointI> tilePoints;
	
	// find all blocks of the specified resource type
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			if (resourceTiles[x][y]->GetResourceType() == rType)
				tilePoints.push_back(CR::Math::PointI(x, y, 0));
		}
	}
	
	// mark all of the blocks if tilePoints <= breakblocks
	if (tilePoints.size() <= breakBlocks || breakAllBlocks)
	{
		for (int i = 0; i < tilePoints.size(); i++)
		{
			specialClearTiles[tilePoints[i].X()][tilePoints[i].Y()] = true;
		}
	}
	else // mark random blocks up to the amount required
	{
		// randomize the list, set special tiles to true for clearing
		int rndCount = 0;
		for (int i = 0; i < tilePoints.size(); i++)
		{
			int rndPoint = random() % (tilePoints.size() - i) + i;
			swap(tilePoints[i], tilePoints[rndPoint]);
			
			specialClearTiles[tilePoints[i].X()][tilePoints[i].Y()] = true;
			rndCount++;
			if (rndCount >= breakBlocks)
				break;
		}
	}
	
	m_buildingSpecialDown = true;
}

void ResourcePuzzle::SetBuildingSpecialUp(BuildingName bName, int level)
{
	if (!specialSelector->IsSelector3())
	{
		std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
		sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::powerused1c::ID);
		sound->Play();
		
		StopAnimateHint();
	}
	
	specialSelector->ShowSelector3();
}

void ResourcePuzzle::CancelBuildingSpecial()
{
	if (!specialSelector->IsSelector3())
	{
		for (int y = 0; y < y_tiles; y++)
		{
			for (int x = 0; x < x_tiles; x++)
			{
				specialClearTiles[x][y] = false;
			}
		}
		
		m_buildingSpecialDown = false;
	}
}

void ResourcePuzzle::OnClearBuildingSpecialTiles()
{
	queue<ResourceTile*> tileQueue;
	
	int resourceCount[ResourceTile::tile_types];// = {0, 0, 0, 0, 0, 0}; // resources receieved through matches
	for (int i = 0; i < ResourceTile::tile_types; i++)
		resourceCount[i] = 0;
	
	// storage for the number of null tiles in each column
	int nullTiles[x_tiles];
	for (int i = 0; i < x_tiles; i++)
		nullTiles[i] = 0;
	
	bool removedMatch = false;
	
	m_buildingSpecialDown = false;
	
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			if (specialClearTiles[x][y] == true)
			{
				ResourceTile *resourceTile = GetResourceTile(x, y);
				if (resourceTile != NULL) 
				{
					tileQueue.push(resourceTile);
					resourceTiles[x][y] = NULL;
					nullTiles[x]++;
					resourceCount[(int)resourceTile->GetResourceType()] += 1; // store resources retrieved
					//particleSystemManager->AddParticleSystem(new CrystalParticleSystem(resourceTile->GetAbsolutePosition(), resourceTile->GetResourceType()));
					removedMatch = true;
				}
			}
			
			specialClearTiles[x][y] = false;
		}
	}
	
	if (!removedMatch) return;
	
	// Report Resources Retrieved
	for (int i = 0; i < ResourceTile::tile_types; i++)
	{
		if (resourceCount[i] > 0)
			ResourcesRetrieved((ResourceType)i, resourceCount[i]);
	}
	
	tileSelector->SetVisible(false);
	
	// Shift down all tiles
	for (int x = 0; x < x_tiles; x++)
	{
		for (int y = y_tiles-1; y > 0; y--)
		{
			if (GetResourceTile(x, y) == NULL)
			{
				for (int i = y; i >=0; i--)
				{
					ResourceTile *tmpTile = GetResourceTile(x, i);
					if (tmpTile != NULL)
					{
						resourceTiles[x][i] = NULL;
						resourceTiles[x][y] = tmpTile;
						CR::Math::PointI tilePoint;
						tilePoint.X(x);
						tilePoint.Y(y);
						tmpTile->AnimateSlideTo(tilePoint, anim_fps * (y - i));
						break;
					}
				}
			}
		}
	}
	
	// Use the tiles from the tilequeue as new tiles, slide them in
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			if (resourceTiles[x][y] == NULL)
			{
				resourceTiles[x][y] = tileQueue.front();
				tileQueue.pop();
				
				resourceTiles[x][y]->RandomizeType(m_dropRateBonusType);
				
				// determine points for slide in animation
				CR::Math::PointI fromPoint = CR::Math::PointI(x, y - nullTiles[x], 0); // from_point
				CR::Math::PointI tilePoint = CR::Math::PointI(x, y, 0); // to_point
				
				resourceTiles[x][y]->AnimateSlideIn(fromPoint, tilePoint, anim_fps * nullTiles[x]);
			}
		}
	}
	
	FindHintBlock();
}

void ResourcePuzzle::OnExplodeTilesSpecial()
{
	// render special tile selector
	if (m_buildingSpecialDown)
	{
		for (int y = 0; y < y_tiles; y++)
		{
			for (int x = 0; x < x_tiles; x++)
			{
				if (specialClearTiles[x][y] == true)
				{
					//specialSelector->SetTilePosition(x, y);
					//specialSelector->Render();
					
					//if (specialSelector->IsSelector3())
					//	resourceTiles[x][y]->RenderSelectorExplode(specialSelector->GetCurrFrame());
					//else
					//	resourceTiles[x][y]->RenderSelectorSpecial(specialSelector->GetCurrFrame());						
					
					//specialSelectorRendered = true;
					particleSystemManager->AddParticleSystem(new CrystalParticleSystem(resourceTiles[x][y]->GetAbsolutePosition(), resourceTiles[x][y]->GetResourceType()));
				}
			}
		}
	}
}

void ResourcePuzzle::FindHintBlock()
{
	if (!hintsEnabled) return;
	
	vector<CR::Math::PointI> validMoves;
	
	// loop through tiles
	for (int x = 0; x < x_tiles; x++)
	{
		for (int y = 0; y < y_tiles; y++)
		{
			// left swap checks
			if (CheckForLeftMatch(x - 1, y, GetResourceTile(x, y)) ||
				CheckForUpMatch(x - 1, y, GetResourceTile(x, y)) ||
				CheckForDownMatch(x - 1, y, GetResourceTile(x, y)) ||
				CheckForMiddleVerticalMatch(x - 1, y, GetResourceTile(x, y)))
			{
				validMoves.push_back(CR::Math::PointI(x, y, 0));
			}
			
			// right swap checks
			if (CheckForRightMatch(x + 1, y, GetResourceTile(x, y)) ||
				CheckForUpMatch(x + 1, y, GetResourceTile(x, y)) ||
				CheckForDownMatch(x + 1, y, GetResourceTile(x, y)) ||
				CheckForMiddleVerticalMatch(x + 1, y, GetResourceTile(x, y)))
			{
				validMoves.push_back(CR::Math::PointI(x, y, 0));
			}
			
			// up swap checks
			if (CheckForLeftMatch(x, y - 1, GetResourceTile(x, y)) ||
				CheckForRightMatch(x, y - 1, GetResourceTile(x, y)) ||
				CheckForUpMatch(x, y - 1, GetResourceTile(x, y)) ||
				CheckForMiddleHorizontalMatch(x, y - 1, GetResourceTile(x, y)))
			{
				validMoves.push_back(CR::Math::PointI(x, y, 0));
			}
			
			// down swap checks
			if (CheckForLeftMatch(x, y + 1, GetResourceTile(x, y)) ||
				CheckForRightMatch(x, y + 1, GetResourceTile(x, y)) ||
				CheckForDownMatch(x, y + 1, GetResourceTile(x, y)) ||
				CheckForMiddleHorizontalMatch(x, y + 1, GetResourceTile(x, y)))
			{
				validMoves.push_back(CR::Math::PointI(x, y, 0));
			}
		}
	}
	
	if (validMoves.size() > 0)
	{
		int rndTile = rand() % validMoves.size();
		hintOffset.X(validMoves[rndTile].X());
		hintOffset.Y(validMoves[rndTile].Y());
	}
}

void ResourcePuzzle::AnimateHint()
{
	resourceTiles[hintOffset.X()][hintOffset.Y()]->AnimateHint();
}

void ResourcePuzzle::StopAnimateHint()
{
	resourceTiles[hintOffset.X()][hintOffset.Y()]->StopAnimateHint();
}

void ResourcePuzzle::PlayResourceSound(ResourceType rType)
{
	int i =	rType * 2 + (rand() & 1);
	sounds[i]->Play();
}

void ResourcePuzzle::TouchesBeganImpl(Touch &_touches)
{
	//if(m_touchID != -1 || _touches.ID != m_touchID)
	//	return;

	// no input is allowed during animation
	if (!touchAllowed || m_isAnimating || specialSelector->IsSelector3() || m_buildingSpecialDown)
		return;

	// detect of the touch was in the bounds of the puzzle
	if ( !(_touches.X > Offset_X() && _touches.X < Offset_X() + (ResourceTile::tile_width * x_tiles + (tile_spacing * x_tiles)) &&
			_touches.Y > Offset_Y() && _touches.Y < Offset_Y() + (ResourceTile::tile_height * y_tiles + (tile_spacing * y_tiles))))
	{
		m_touchID = -1;
		return;
	}
	else
	{
		m_touchID = _touches.ID;
	}
		
	CR::Math::PointI mtxPosition;
	mtxPosition.X((_touches.X - Offset_X()) / (ResourceTile::tile_width + tile_spacing));
	mtxPosition.Y((_touches.Y - Offset_Y()) / (ResourceTile::tile_height + tile_spacing));

	bool wasVisible = tileSelector->Visible();
	CR::Math::PointI oldPosition = tileSelector->GetPosition();
	tileSelector->SetPosition(mtxPosition);
	tileSelector->SetVisible(true);
		
	if (wasVisible && !(tileSelector->GetPosition().X() == oldPosition.X() && tileSelector->GetPosition().Y() == oldPosition.Y()))
	{
		if (hintsEnabled)
		{
			currHintTime = maxHintTime;
			StopAnimateHint();
		}
			
		if (CanSwapTiles(oldPosition, tileSelector->GetPosition()))
			SwapTiles(oldPosition, tileSelector->GetPosition());
		else
		{
			if (AnimateShakeTiles(oldPosition, tileSelector->GetPosition()))
			{
				//tileSelector->SetVisible(false);
				hideTileSelectorAfterAnimation = true;
				m_touchID = -1;
			}
		}
			
		// A move was made or attempted
		MoveMade();
		touchAllowed = false;
	}
}

void ResourcePuzzle::TouchesMovedImpl(Touch &_touches)
{
	if(m_touchID == _touches.ID)
		TouchesBeganImpl(_touches);
}

void ResourcePuzzle::TouchesEndedImpl(Touch &_touches)
{
	if(m_touchID == _touches.ID)
	{
		m_touchID = -1;
	}
}

/*
void ResourcePuzzle::TouchesBeganImpl(UIView *view, NSSet *touches)
{
	// no input is allowed during animation
	if (!touchAllowed || m_isAnimating || specialSelector->IsSelector3() || m_buildingSpecialDown)
		return;
	
	CGPoint glLocation;
	for (UITouch *touch in touches)
	{
		if (this->touch != NULL && touch != this->touch)
			continue;
		
		glLocation = GetGLLocation(view, touch);

		// detect of the touch was in the bounds of the puzzle
		if ( !(glLocation.x > Offset_X() && glLocation.x < Offset_X() + (ResourceTile::tile_width * x_tiles + (tile_spacing * x_tiles)) &&
			  glLocation.y > Offset_Y() && glLocation.y < Offset_Y() + (ResourceTile::tile_height * y_tiles + (tile_spacing * y_tiles))))
		{
			this->touch = NULL;
			return;
		}
		else
		{
			this->touch = touch;
		}
		
		CR::Math::PointI mtxPosition;
		mtxPosition.X((glLocation.x - Offset_X()) / (ResourceTile::tile_width + tile_spacing));
		mtxPosition.Y((glLocation.y - Offset_Y()) / (ResourceTile::tile_height + tile_spacing));

		bool wasVisible = tileSelector->Visible();
		CR::Math::PointI oldPosition = tileSelector->GetPosition();
		tileSelector->SetPosition(mtxPosition);
		tileSelector->SetVisible(true);
		
		if (wasVisible && !(tileSelector->GetPosition().X() == oldPosition.X() && tileSelector->GetPosition().Y() == oldPosition.Y()))
		{
			if (hintsEnabled)
			{
				currHintTime = maxHintTime;
				StopAnimateHint();
			}
			
			if (CanSwapTiles(oldPosition, tileSelector->GetPosition()))
				SwapTiles(oldPosition, tileSelector->GetPosition());
			else
			{
				if (AnimateShakeTiles(oldPosition, tileSelector->GetPosition()))
				{
					//tileSelector->SetVisible(false);
					hideTileSelectorAfterAnimation = true;
					this->touch = NULL;
				}
			}
			
			// A move was made or attempted
			MoveMade();
			touchAllowed = false;
		}
	}
}

void ResourcePuzzle::TouchesMovedImpl(UIView *view, NSSet *touches)
{
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			this->TouchesBeganImpl(view, touches);
			break;
		}
	}
}

void ResourcePuzzle::TouchesEndedImpl(UIView *view, NSSet *touches)
{
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			this->touch = NULL;
			break;
		}
	}
}

void ResourcePuzzle::TouchesCancelledImpl(UIView *view, NSSet *touches)
{
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			this->touch = NULL;
			break;
		}
	}
}
*/







