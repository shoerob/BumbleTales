#include "DataHandler.h"
#include "DataCompiler.h"
#include "CompilerImpl.h"

using namespace CR;
using namespace CR::Compiler;

DataHandler::DataHandler(void)
{
}

DataHandler::~DataHandler(void)
{
}

INodeCompiler* DataHandler::StartElement()
{
	DataCompiler *compiler = new DataCompiler();;
	CompilerImpl::Instance().SetTop(compiler);
	return compiler;
}
