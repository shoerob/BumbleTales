#include "StdAfx.h"
#include "INodeCompiler.h"

using namespace std;
using namespace CR::Compiler;
using namespace CR::Utility;

INodeCompiler::INodeCompiler(void)
{
}

INodeCompiler::INodeCompiler(const std::wstring &_name,const std::wstring &_guid) :
name(_name), guid(_guid)
{

}

INodeCompiler::~INodeCompiler(void)
{
}

void INodeCompiler::Compile(BinaryWriter &writer)
{
	long long begining;
	long long end;
	long long lengthLocation;
	long long childrenStartLocation;
	long long currentLocation;
	//writer.CompressingMode(false);
	begining = writer.Position();

	writer << Index();
	lengthLocation = writer.Position();
	writer << (long long)0 << (long)children.size();
	childrenStartLocation = writer.Position();
	writer << (long long)0;

	CompileData(writer);
	currentLocation = writer.Position();
	writer.Position(childrenStartLocation);
	writer << currentLocation;
	writer.Position(currentLocation);

	vector<INodeCompiler*>::iterator iterator = children.begin();
	while(iterator != children.end())
	{
		(*iterator)->Compile(writer);
		++iterator;
	}
	end = writer.Position();
	writer.Position(lengthLocation);
	writer << (long)(end-begining);
	writer.Position(end);
}

void INodeCompiler::AddChild(INodeCompiler* child)
{ 
	if(child != NULL)
		children.push_back(child);
}