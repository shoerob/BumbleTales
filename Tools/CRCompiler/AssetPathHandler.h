#pragma once
#include "inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class AssetPathHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			AssetPathHandler(void);
			virtual ~AssetPathHandler(void);
			virtual std::wstring Handles() {return L"asset-path";}
			virtual std::wstring Parent() {return L"compiler-settings";}
			virtual void HandleAttribute(const std::wstring &name,const std::wstring& value);
			virtual CR::Compiler::INodeCompiler* StartElement() {return NULL;}
		};
	}
}

