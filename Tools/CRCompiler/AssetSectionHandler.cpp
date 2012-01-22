#include "AssetSectionHandler.h"
#include "CompilerImpl.h"

using namespace CR;
using namespace CR::Compiler;
using namespace boost;

AssetSectionHandler::AssetSectionHandler(void)
{
}

AssetSectionHandler::~AssetSectionHandler(void)
{
}

void AssetSectionHandler::HandleAttribute(const std::wstring &name,const std::wstring& value)
{
	if(to_lower_copy(name) == L"section")
		CompilerImpl::Instance().AddAssetSection(value);
}
