#pragma once
#include "inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class OutputPathHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			OutputPathHandler(void);
			virtual ~OutputPathHandler(void);
			virtual std::wstring Handles() {return L"output-path";}
			virtual std::wstring Parent() {return L"compiler-settings";}
			virtual void HandleAttribute(const std::wstring &name,const std::wstring& value);
			virtual CR::Compiler::INodeCompiler* StartElement() {return NULL;}
		};
	}
}
