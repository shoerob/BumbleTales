/*
 *  RepeatedSpriteHelper.cpp
 *  Bumble Tales
 *
 *  Created by Eric Duhon on 8/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "RepeatedSpriteHelper.h"
#include <vector>
#include "Graphics.h"
#include <functional>
#include "FunctionObjects.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

using namespace std;
using namespace CR::Graphics;
using namespace CR::Game;
using namespace CR::Utility;

namespace CR
{
	namespace Game
	{
		class RepeatedSpriteHelperImpl
		{
		public:
			RepeatedSpriteHelperImpl(int _image,bool _singleSetMode, int _zInitial) : m_image(_image), m_singleSetMode(_singleSetMode) , m_zInitial(_zInitial) {}
			~RepeatedSpriteHelperImpl();
			void NewSprite();
			void SetPosition(int _x,int _y);
			void SetFrame(int _frame);
			void SetFrameRate(int _frameRate);
			void Start();
			void End();			
			void SetImage(int _image);
		private:
			vector<Sprite*> m_sprites;
			int m_currentSprite;
			bool m_singleSetMode;
			int m_zInitial;
			int m_image;
		};
	}
}


RepeatedSpriteHelper::RepeatedSpriteHelper(int _image,bool _singleSetMode, int _zInitial) : m_impl(new RepeatedSpriteHelperImpl(_image,_singleSetMode,_zInitial))
{

}

RepeatedSpriteHelperImpl::~RepeatedSpriteHelperImpl()
{
	ForEach(m_sprites, mem_fun(&Sprite::Release));
}

void RepeatedSpriteHelperImpl::NewSprite()
{
	++m_currentSprite;
	if(m_currentSprite >= m_sprites.size())
	{
		m_sprites.push_back(graphics_engine->CreateSprite1(m_singleSetMode, m_zInitial));
		m_sprites[m_currentSprite]->SetImage(m_image);
	}
	m_sprites[m_currentSprite]->Render();
}

void RepeatedSpriteHelperImpl::SetPosition(int _x,int _y)
{
	if(m_currentSprite != -1)
		m_sprites[m_currentSprite]->SetPositionAbsolute(_x,_y);
}

void RepeatedSpriteHelperImpl::SetFrame(int _frame)
{
	if(m_currentSprite != -1)
		m_sprites[m_currentSprite]->SetFrame(_frame);
}

void RepeatedSpriteHelperImpl::SetFrameRate(int _frameRate)
{
	if(m_currentSprite != -1)
		m_sprites[m_currentSprite]->SetFrameRate(_frameRate);
}
			

void RepeatedSpriteHelperImpl::Start()
{
	m_currentSprite = -1;
}

void RepeatedSpriteHelperImpl::End()
{
	if(m_currentSprite != -1 && m_sprites.size() > m_currentSprite+1)
	{
		for(int i = m_currentSprite+1;i < m_sprites.size();++i)
		{
			m_sprites[i]->Release();
		}
		m_sprites.resize(m_currentSprite+1);
	}
}

void RepeatedSpriteHelperImpl::SetImage(int _image)
{
	m_image = _image;
}

void RepeatedSpriteHelper::NewSprite()
{
	m_impl->NewSprite();
}

void RepeatedSpriteHelper::SetPosition(int _x,int _y)
{
	m_impl->SetPosition(_x,_y);
}

void RepeatedSpriteHelper::SetFrame(int _frame)
{
	m_impl->SetFrame(_frame);
}

void RepeatedSpriteHelper::SetFrameRate(int _frameRate)
{
	m_impl->SetFrameRate(_frameRate);
}

void RepeatedSpriteHelper::Start()
{
	m_impl->Start();
}

void RepeatedSpriteHelper::End()
{
	m_impl->End();
}

void RepeatedSpriteHelper::SetImage(int _image)
{
	m_impl->SetImage(_image);
}