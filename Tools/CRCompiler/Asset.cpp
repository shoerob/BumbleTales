#include "Asset.h"
#include "..\..\Engines\Utility\FunctionObjects.h"
#include "CompilerImpl.h"
#include "boost/bind.hpp"
#include "boost/format.hpp"

using namespace std;
using namespace CR;
using namespace CR::Utility;
using namespace CR::Compiler;
using namespace boost;

Asset::Asset(void)
{
}

Asset::~Asset(void)
{
	ForEach(children,DeleteFO());
}

void Asset::GenerateFile(wofstream &_outputFile)
{
        _outputFile << L"//Do not modify. This file was created by the Syntax Compiler" << endl << endl;
	_outputFile << L"#pragma once" << endl <<endl;	
	_outputFile << L"#include \"Guid.h\"" << endl <<endl;	
	_outputFile << L"namespace CR" << endl;
	_outputFile << L"{" << endl;
	_outputFile << L"\tnamespace AssetList" << endl;
	_outputFile << L"\t{" << endl;
	
	Asset *data = this->children[0];
	vector<Asset*>::iterator iterator = data->children.begin();
	while(iterator != data->children.end())
	{
		if(CompilerImpl::Instance().ContainsSection((*iterator)->name))
		{
			(*iterator)->OutputAsset(_outputFile,L"\t");
		}
		iterator++;
	}

	_outputFile << L"\t}" << endl;
	_outputFile << L"}" << endl;
}

void Asset::OutputAsset(std::wofstream &_outputFile,std::wstring _tabs)
{
	_tabs += L"\t";
	_outputFile << _tabs.c_str() << L"namespace " << name.c_str() << endl;
	_outputFile << _tabs.c_str()  << L"{" << endl;
	_outputFile << _tabs.c_str() << L"\t" << wformat(L"const CR::Utility::Guid ID(0x%x,0x%x,0x%x,0x%x);") %
		id.Data1() % id.Data2() % id.Data3() % id.Data4();
	_outputFile << endl;
	ForEach(children,boost::bind(&Asset::OutputAsset,_1,ref(_outputFile),_tabs));
	_outputFile << endl << _tabs.c_str()  << L"}" << endl;
}
