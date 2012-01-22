#include "StdAfx.h"
#include "MusicHandler.h"
#include "MusicCompiler.h"

using namespace CR::Compiler;

MusicHandler::MusicHandler(void)
{
}

MusicHandler::~MusicHandler(void)
{
}

INodeCompiler* MusicHandler::StartElement()
{
	return new MusicCompiler();
}