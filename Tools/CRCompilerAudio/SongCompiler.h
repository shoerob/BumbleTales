#pragma once
#include "inodecompiler.h"

namespace CR
{
	namespace Compiler
	{
		class SongCompiler :
			public CR::Compiler::INodeCompiler
		{
		public:
			SongCompiler(void);
			virtual ~SongCompiler(void);
			virtual std::wstring IndexName() {return name;}
			virtual void CompileData(CR::Utility::BinaryWriter &writer);
			void FileName(std::wstring fileName) {this->fileName = fileName;}
			void Quality(int _quality) { _quality = min(10,_quality); _quality = max(0,_quality); m_quality = _quality;}
		private:
			void SetUpFileNames();
			void CheckFile();
			void BuildFinal();
			bool needsToUpdate;
			std::wstring fileName;
			std::wstring finalFileName;
			int m_quality;
		};
	}
}
