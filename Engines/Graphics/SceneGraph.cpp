/*
 *  SceneGraph.cpp
 *  Bumble Tales
 *
 *  Created by Eric Duhon on 8/13/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "SceneGraph.h"
#include <vector>
#include <functional>
#include <tr1/functional>
#include <tr1/unordered_map>
#include <map>
#include "Graphics.h"
#include "SpriteInternal.h"
#include "FunctionObjects.h"
#include "Vector.h"

#include "s3e.h"
#include "GLES/gl.h"
#include "GLES/egl.h"

using namespace std;
using namespace std::tr1;
using namespace CR::Graphics;
using namespace CR::Utility;

namespace CR
{
	namespace Graphics
	{
		class SceneGraphImpl
		{
		public:
			void AddSprite(SpriteInternal *_sprite);
			void RemoveSprite(SpriteInternal *_sprite);
			int Size();
			void Render();
			int NumGroups();
			void BeginFrame();
		private:
			int GenerateKey(SpriteInternal *_sprite);
			void AddSprite(SpriteInternal *_sprite,int _key);
			void RemoveSprite(SpriteInternal *_sprite,int _key);
			
			std::vector<SpriteInternal*> m_sceneList;
			map<int,map<int,vector<SpriteInternal*> >, greater<int> > m_scene_graph;			
		};	
	}
}
	
static void checkEGLErrors()
{
    EGLint error = eglGetError();
    if (error != EGL_SUCCESS)
    {
		s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "EGL Error");
    }
}
			
SceneGraph::SceneGraph() : m_impl(new SceneGraphImpl())
{
}

void SceneGraph::AddSprite(SpriteInternal *_sprite)
{
	m_impl->AddSprite(_sprite);
}

void SceneGraph::RemoveSprite(SpriteInternal *_sprite)
{
	m_impl->RemoveSprite(_sprite);
}

int SceneGraph::Size()
{
	return m_impl->Size();
}

void SceneGraph::Render()
{
	m_impl->Render();
}

int SceneGraph::NumGroups()
{
	return m_impl->NumGroups();
}

void SceneGraph::BeginFrame()
{
	m_impl->BeginFrame();
}

int SceneGraphImpl::GenerateKey(SpriteInternal *_sprite)
{
	//return (_sprite->GetImage() << 16) | _sprite->GetFrameSet();
	return _sprite->GetTextureId();
}

void SceneGraphImpl::AddSprite(SpriteInternal *_sprite)
{
	AddSprite(_sprite,GenerateKey(_sprite));
		
	m_sceneList.push_back(_sprite);
}

void SceneGraphImpl::RemoveSprite(SpriteInternal *_sprite)
{	
	RemoveSprite(_sprite,GenerateKey(_sprite));
	
	vector<SpriteInternal*>::iterator iterator = find(m_sceneList.begin(),m_sceneList.end(),_sprite);
	if(iterator != m_sceneList.end())
	{
		UnorderedRemove(m_sceneList,iterator);
	}		
}

void SceneGraphImpl::AddSprite(SpriteInternal *_sprite,int _key)
{	
	//unordered_map<int,vector<SpriteInternal*> > &bucket = m_scene_graph[_sprite->GetZ()];
	/*if(bucket.count(_key) == 0)
	{
		bucket.insert(make_pair(_key, vector<SpriteInternal*>()));
	}
	bucket[_key].push_back(_sprite);*/
	m_scene_graph[_sprite->GetZ()][_key].push_back(_sprite);
}

void SceneGraphImpl::RemoveSprite(SpriteInternal *_sprite,int _key)
{
	if(m_scene_graph.count(_sprite->GetZ()) == 0)
		return;
	map<int,vector<SpriteInternal*> > &bucket = m_scene_graph[_sprite->GetZ()];
	if(bucket.count(_key) == 0)
		return;
	vector<SpriteInternal*> &sprites = bucket[_key];
	vector<SpriteInternal*>::iterator iterator = find(sprites.begin(),sprites.end(),_sprite);
	if(iterator != sprites.end())
	{
		UnorderedRemove(sprites,iterator);
	}
	if(sprites.empty())
	{
		bucket.erase(_key);
	}
	if(bucket.empty())
		m_scene_graph.erase(_sprite->GetZ());
}

int SceneGraphImpl::Size()
{
	return m_sceneList.size();
}

void SceneGraphImpl::Render()
{
	vector<SpriteInternal*>::iterator sprite_iterator = m_sceneList.begin();
	vector<SpriteInternal*>::iterator end_sprite_iterator = m_sceneList.end();
	while(sprite_iterator != end_sprite_iterator)
	{		
		(*sprite_iterator)->Update();
		if(GenerateKey((*sprite_iterator)) != (*sprite_iterator)->GetOldTextureId())
		{
			RemoveSprite((*sprite_iterator),(*sprite_iterator)->GetOldTextureId());
			AddSprite((*sprite_iterator),GenerateKey((*sprite_iterator)));
		}
		++sprite_iterator;	
	}		
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glEnable(GL_TEXTURE_2D);
	
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);	
	
	vector<Vertex> vertices;
	vector<GLushort> indices;
	
	
	map<int,map<int,vector<SpriteInternal*> > >::iterator sceneBegin = m_scene_graph.begin();
	map<int,map<int,vector<SpriteInternal*> > >::iterator sceneEnd = m_scene_graph.end();
	while(sceneBegin != sceneEnd)
	{
		map<int,std::vector<SpriteInternal*> >::iterator iterator = sceneBegin->second.begin();
		map<int,std::vector<SpriteInternal*> >::iterator end = sceneBegin->second.end();
		while(iterator != end)
		{
			//int texture = iterator->first;
			//assert(glIsTexture(iterator->first));
			glBindTexture(GL_TEXTURE_2D,iterator->first);
			//checkEGLErrors();
			//glBindTexture(GL_TEXTURE_2D,3);
			vertices.clear();
			indices.clear();	
			std::vector<SpriteInternal*>::iterator sprite_iterator = iterator->second.begin();
			std::vector<SpriteInternal*>::iterator end_sprite_iterator = iterator->second.end();
			while(sprite_iterator != end_sprite_iterator)
			{
				SpriteInternal *sprite = (*sprite_iterator);
				if(sprite->Visible())
				{
					if(sprite->IsClipping())
					{
						vector<Vertex> vertices;
						vector<GLushort> indices;
						sprite->Render(vertices,indices);
						
						CR::Math::RectangleI &clip = sprite->GetClip();
						
						glEnable(GL_SCISSOR_TEST);
						glScissor(clip.Left(), clip.Top(), clip.Width(), clip.Height());
						
						glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &(vertices[0]));
						glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &(vertices[0].U));
						glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), &(vertices[0].Color));
						
						glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_SHORT, &(indices[0]));
						glDisable(GL_SCISSOR_TEST);					
						
					}
					else
						sprite->Render(vertices,indices);
				}
				++sprite_iterator;	
			}			
				
			if(!indices.empty())
			{
				assert(!vertices.empty());
				glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &(vertices[0]));
				glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &(vertices[0].U));
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), &(vertices[0].Color));
			
				glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_SHORT, &(indices[0]));
			}
			
			++iterator;
		}
		++sceneBegin;
	}
}

int SceneGraphImpl::NumGroups()
{
	return m_scene_graph.size();
}

void SceneGraphImpl::BeginFrame()
{
	ForEach(m_sceneList,mem_fun(&SpriteInternal::ClearVisible));	
}	

