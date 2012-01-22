#include "StdAfx.h"
#include "BufferHandler.h"
#include "BufferCompiler.h"

using namespace CR::Compiler;
using namespace boost;

BufferHandler::BufferHandler(void)
{
}

BufferHandler::~BufferHandler(void)
{
}

void BufferHandler::HandleAttribute(const std::wstring &name,const std::wstring& value)
{
	if(name == L"name")
		compiler->Name(value);
	if(name == L"id")
		compiler->Index(value);
	else if(name == L"filename")
		compiler->FileName(value);
	else if(name == L"compression")
		compiler->CompressionType(value);
	else if(name == L"quality")
		compiler->Quality(lexical_cast<int>(value));
}

INodeCompiler* BufferHandler::StartElement()
{
	compiler = new BufferCompiler();
	return compiler;
}