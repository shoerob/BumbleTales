#pragma once
#include "inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class SoundsHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			SoundsHandler(void);
			virtual ~SoundsHandler(void);
			virtual std::wstring Handles() {return L"sounds";}
			virtual std::wstring Parent() {return L"data";}
			virtual void HandleAttribute(const std::wstring &name,const std::wstring& value) {}
			virtual CR::Compiler::INodeCompiler* StartElement();
		};
	}
}
