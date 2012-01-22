// CRCompilerAudio.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CRCompilerAudio.h"
#include "BuffersHandler.h"
#include "BufferHandler.h"
#include "MusicHandler.h"
#include "SongHandler.h"
#include "SoundsHandler.h"
#include "SoundHandler.h"

using namespace std;
using namespace CR::Compiler;

vector<INodeHandler*> GetHandlers(void)
{
	vector<INodeHandler*> handlers;
	handlers.push_back(new BuffersHandler());
	handlers.push_back(new BufferHandler());
	handlers.push_back(new MusicHandler());
	handlers.push_back(new SongHandler());
	handlers.push_back(new SoundsHandler());
	handlers.push_back(new SoundHandler());
	return handlers;
}

void SetCompiler(CR::Compiler::ICompiler *compiler)
{
	Globals::Instance().Compiler(compiler);
}
