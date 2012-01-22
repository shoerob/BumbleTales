#pragma once
#include "inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class MusicHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			MusicHandler(void);
			virtual ~MusicHandler(void);
			virtual std::wstring Handles() {return L"music";}
			virtual std::wstring Parent() {return L"data";}
			virtual void HandleAttribute(const std::wstring &name,const std::wstring& value) {}
			virtual CR::Compiler::INodeCompiler* StartElement();
		};
	}
}
