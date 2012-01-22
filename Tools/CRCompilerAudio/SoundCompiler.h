#pragma once
#include "inodecompiler.h"

namespace CR
{
	namespace Compiler
	{
		class SoundCompiler :
			public CR::Compiler::INodeCompiler
		{
		public:
			SoundCompiler(void);
			virtual ~SoundCompiler(void);
			virtual std::wstring IndexName() {return name;}
			virtual void CompileData(CR::Utility::BinaryWriter &writer);
			void Buffer(CR::Utility::Guid &_buffer) {m_buffer = _buffer;}
			void Gain(float _gain) {m_gain = _gain;}
			void Positional(bool _positional) {m_positional = _positional;}
		private:			
			CR::Utility::Guid m_buffer;
			float m_gain;
			bool m_positional;
		};
	}
}
