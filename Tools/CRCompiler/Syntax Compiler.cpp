// Syntax Graphics Compiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CompilerImpl.h"

using namespace boost;
using namespace boost::filesystem;          
using namespace CR;
using namespace CR::Compiler;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc < 2)
	{
		MessageBox(NULL,L"No input file specified",L"Error",MB_OK);
		return -1;
	}
	wpath exe(argv[0]);

	wpath data(argv[1]);
	CompilerImpl::Instance().Init(exe.branch_path().string(),data.branch_path().string(),data.leaf());

	for(int i = 2;i < argc;i++)
	{
		wstring arg(argv[i]);
		vector<wstring> args;
		split(args,arg,is_any_of(L"="));
		if(args.size() == 1)
			args.push_back(L"");
		CompilerImpl::Instance().AddSetting(args[0],args[1]);
	}

	CompilerImpl::Instance().Run();
	return 0;
}

