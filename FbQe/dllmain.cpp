// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Inc.h"

using namespace std;

namespace FbQe {

    FB_BOOLEAN fUnloadFlag = FB_FALSE;
    FB_BOOLEAN* fTheirUnloadFlag;

    FbQe::IncFactory* fFactory;
    ofstream f;

    EXTERN_C __declspec(dllexport) FB_BOOLEAN* __cdecl firebird_udr_plugin(IStatus* status, FB_BOOLEAN* theirUnloadFlag, Firebird::IUdrPlugin* udrPlugin)
    {
        f.open("c:\\fb\\example.txt");
        f << "Plugin loaded.\r\n";
        fFactory = new FbQe::IncFactory(&f);

        f << "\r\nRegister functions";
        f.flush();

        udrPlugin->registerFunction((ThrowStatusWrapper*)status, "get_int_eks", fFactory);

        f << "\r\nReturn";
        f.flush();

        fTheirUnloadFlag = theirUnloadFlag;
        return &fUnloadFlag;
    }

}