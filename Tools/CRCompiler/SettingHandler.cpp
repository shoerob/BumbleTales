#include "boost\algorithm\string.hpp"
#include "SettingHandler.h"
#include "CompilerImpl.h"

using namespace CR;
using namespace CR::Compiler;
using namespace boost;

SettingHandler::SettingHandler(void)
{
}

SettingHandler::~SettingHandler(void)
{
}

void SettingHandler::HandleAttribute(const std::wstring &name,const std::wstring& value)
{
	if(to_lower_copy(name) == L"name")
		this->name = value;
	else if(to_lower_copy(name) == L"value")
		this->value = value;
}

void SettingHandler::EndElement()
{
	CompilerImpl::Instance().AddSetting(name,value);
}
