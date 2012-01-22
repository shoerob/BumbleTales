#include "StdAfx.h"
#include "SongHandler.h"
#include "SongCompiler.h"
#include "boost/lexical_cast.hpp"

using namespace CR::Compiler;
using boost::lexical_cast;
using boost::bad_lexical_cast;

SongHandler::SongHandler(void)
{
}

SongHandler::~SongHandler(void)
{
}

void SongHandler::HandleAttribute(const std::wstring &name,const std::wstring& value)
{
	if(name == L"name")
		compiler->Name(value);
	if(name == L"id")
		compiler->Index(value);
	else if(name == L"filename")
		compiler->FileName(value);
	else if(name == L"quality")
		compiler->Quality(lexical_cast<int>(value));
}

INodeCompiler* SongHandler::StartElement()
{
	compiler = new SongCompiler();
	return compiler;
}