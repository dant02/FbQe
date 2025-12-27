// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "log.h"
#include "Inc.h"

namespace FbQe {
    FB_BOOLEAN fUnloadFlag = FB_FALSE;
    FB_BOOLEAN* fTheirUnloadFlag;

    std::unique_ptr<Log> l;
    std::unique_ptr<IncFactory> fFactory;
    std::unique_ptr<GetCurrentTimestampUTC_Factory> fGetCurrentTimestampUTC;

    extern "C" __declspec(dllexport) FB_BOOLEAN* __cdecl firebird_udr_plugin(IStatus* status, FB_BOOLEAN* theirUnloadFlag, Firebird::IUdrPlugin* udrPlugin) {
        l = make_unique<Log>();
        l->write_line("Plugin init");

        fFactory = make_unique<IncFactory>();
        fGetCurrentTimestampUTC = make_unique<GetCurrentTimestampUTC_Factory>();

        l->write_line("Register functions");
        udrPlugin->registerFunction((ThrowStatusWrapper*)status, "get_int_eks", fFactory.get());
        udrPlugin->registerFunction((ThrowStatusWrapper*)status, "GetCurrentTimestampUTC", fGetCurrentTimestampUTC.get());
        fTheirUnloadFlag = theirUnloadFlag;

        l->write_line("Plugin init end");
        return &fUnloadFlag;
    }
}

