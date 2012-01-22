#include "StdAfx.h"
#include "SoundsHandler.h"
#include "SoundsCompiler.h"

using namespace CR::Compiler;

SoundsHandler::SoundsHandler(void)
{
}

SoundsHandler::~SoundsHandler(void)
{
}

INodeCompiler* SoundsHandler::StartElement()
{
	return new SoundsCompiler();
}
