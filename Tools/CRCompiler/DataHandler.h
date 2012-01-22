#pragma once
#include "inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class DataHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			DataHandler(void);
			virtual ~DataHandler(void);
			virtual std::wstring Handles() {return L"data";}
			virtual std::wstring Parent() {return L"";}
			virtual INodeCompiler* StartElement();
		};
	}
}
