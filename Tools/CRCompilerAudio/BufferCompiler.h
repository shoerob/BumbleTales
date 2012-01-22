#pragma once
#include "inodecompiler.h"

namespace CR
{
	namespace Compiler
	{
		class BufferCompiler :
			public CR::Compiler::INodeCompiler
		{
		public:
			BufferCompiler(void);
			virtual ~BufferCompiler(void);
			virtual std::wstring IndexName() {return name;}
			virtual void CompileData(CR::Utility::BinaryWriter &writer);
			void FileName(const std::wstring &fileName) {this->fileName = fileName;}
			void CompressionType(const std::wstring &_compressionType);
			void Quality(int _quality) { _quality = min(10,_quality); _quality = max(0,_quality); m_quality = _quality;}
		private:
			enum ECompressionType
			{
				OGG,
				SPEEX
			};
			void SetUpFileNames();
			void CheckFile();
			void BuildFinal();
			bool needsToUpdate;
			std::wstring fileName;
			std::wstring finalFileName;
			ECompressionType m_compressionType;
			int m_quality;
		};
	}
}
