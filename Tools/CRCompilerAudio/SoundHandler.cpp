#include "StdAfx.h"
#include "SoundHandler.h"
#include "SoundCompiler.h"
#include "StringUtil.h"

using namespace CR::Compiler;
using namespace CR::Utility;
using namespace boost;

SoundHandler::SoundHandler(void)
{
}

SoundHandler::~SoundHandler(void)
{
}

void SoundHandler::HandleAttribute(const std::wstring &name,const std::wstring& value)
{
	if(name == L"name")
		compiler->Name(value);
	if(name == L"id")
		compiler->Index(value);
	else if(name == L"buffer")
		compiler->Buffer(Guid(value));
	else if(name == L"gain")
		compiler->Gain(lexical_cast<float>(value));
	else if(name == L"positional")
	{
		if(CaseInsensitiveCompare(value,L"true"))
			compiler->Positional(true);
		else
			compiler->Positional(false);
	}
}

INodeCompiler* SoundHandler::StartElement()
{
	compiler = new SoundCompiler();
	return compiler;
}