#include <QtCore/QCoreApplication>
#include "CompilerImpl.h"
#include "stringUtil.h"
#include <QFileInfo>

using namespace boost;
//using namespace boost::filesystem;
using namespace CR;
using namespace CR::Compiler;
using namespace std;
using namespace CR::Utility;

int main(int argc, char* argv[])
{

    //QCoreApplication a(argc, argv);

    Convert stringConvertor;

        if(argc < 2)
        {
                //MessageBox(NULL,L"No input file specified",L"Error",MB_OK);
                return -1;
        }
        QFileInfo exe(argv[0]);

        QFileInfo data(argv[1]);
        CompilerImpl::Instance().Init(exe.absolutePath ().toStdWString(),
                                      data.absolutePath().toStdWString(),data.fileName().toStdWString());

        for(int i = 2;i < argc;i++)
        {
                wstring arg(stringConvertor(argv[i]));
                vector<wstring> args;
                split(args,arg,is_any_of(L"="));
                if(args.size() == 1)
                        args.push_back(L"");
                CompilerImpl::Instance().AddSetting(args[0],args[1]);
        }

        CompilerImpl::Instance().Run();

       // return a.exec();
}
