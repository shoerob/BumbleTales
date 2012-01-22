#include "StdAfx.h"
#include "BuffersHandler.h"
#include "BuffersCompiler.h"

using namespace CR::Compiler;

BuffersHandler::BuffersHandler(void)
{
}

BuffersHandler::~BuffersHandler(void)
{
}

INodeCompiler* BuffersHandler::StartElement()
{
	return new BuffersCompiler();
}