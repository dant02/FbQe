// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "log.h"
#include "Inc.h"

namespace FbQe {
    FB_BOOLEAN fUnloadFlag = FB_FALSE;
    FB_BOOLEAN* fTheirUnloadFlag;

    Log* l;
    IncFactory* fFactory;

    extern "C" __declspec(dllexport) FB_BOOLEAN* __cdecl firebird_udr_plugin(IStatus* status, FB_BOOLEAN* theirUnloadFlag, Firebird::IUdrPlugin* udrPlugin) {
        l = new Log();
        l->write_line("Plugin init");
        fFactory = new IncFactory(l);

        l->write_line("Register functions");
        udrPlugin->registerFunction((ThrowStatusWrapper*)status, "get_int_eks", fFactory);
        fTheirUnloadFlag = theirUnloadFlag;

        l->write_line("Plugin init end");
        return &fUnloadFlag;
    }
}