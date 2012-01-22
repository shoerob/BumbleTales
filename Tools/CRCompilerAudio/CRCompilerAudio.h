// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CRCOMPILERAUDIO_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CRCOMPILERAUDIO_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CRCOMPILERAUDIO_EXPORTS
#define CRCOMPILERAUDIO_API __declspec(dllexport)
#else
#define CRCOMPILERAUDIO_API __declspec(dllimport)
#endif

#include "INodeHandler.h"
#include "ICompiler.h"
#include "Singleton.h"
#include <vector>

CRCOMPILERAUDIO_API std::vector<CR::Compiler::INodeHandler*> GetHandlers();
CRCOMPILERAUDIO_API void SetCompiler(CR::Compiler::ICompiler *compiler);

namespace CR
{
	namespace Compiler
	{
		class Globals : public CR::Utility::Singleton<Globals>
		{
			friend CR::Utility::Singleton<Globals>;
		public:
			CR::Compiler::ICompiler *Compiler() { return compiler;}
			void Compiler(CR::Compiler::ICompiler * compiler) { this->compiler = compiler;}
		private:
			Globals() {};
			virtual ~Globals() {};
			CR::Compiler::ICompiler *compiler;
		};
	}
}