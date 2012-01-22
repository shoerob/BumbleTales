#pragma once
#include "inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class CompilerSettingsHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			CompilerSettingsHandler(void);
			virtual ~CompilerSettingsHandler(void);
			virtual std::wstring Handles() {return L"compiler-settings";}
			virtual std::wstring Parent() {return L"data";}
			virtual CR::Compiler::INodeCompiler* StartElement() {return NULL;}
		};
	}
}
