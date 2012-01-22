#pragma once
#include "inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class AssetSectionHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			AssetSectionHandler(void);
			virtual ~AssetSectionHandler(void);
			virtual std::wstring Handles() {return L"asset-section";}
			virtual std::wstring Parent() {return L"compiler-settings";}
			virtual void HandleAttribute(const std::wstring &name,const std::wstring& value);
			virtual CR::Compiler::INodeCompiler* StartElement() {return NULL;}
		};
	}
}
