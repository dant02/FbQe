// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "log.h"
#include "Inc.h"

namespace FbQe {
    FB_BOOLEAN fPluginUnloadFlag = FB_FALSE;
    FB_BOOLEAN* fEngineUnloadFlag;

    std::unique_ptr<Log> l;
    std::unique_ptr<IncFactory> fFactory;
    std::unique_ptr<GetCurrentTimestampUTC_Factory> fGetCurrentTimestampUTC;

    extern "C" __declspec(dllexport) FB_BOOLEAN* __cdecl firebird_udr_plugin(IStatus* aStatus, FB_BOOLEAN* aUnloadFlag, Firebird::IUdrPlugin* aPlugin) {
        fEngineUnloadFlag = aUnloadFlag;
        l = make_unique<Log>();
        l->write_line("Plugin init");

        fFactory = make_unique<IncFactory>();
        fGetCurrentTimestampUTC = make_unique<GetCurrentTimestampUTC_Factory>();

        l->write_line("Register functions");
        auto status = (ThrowStatusWrapper*)aStatus;
        aPlugin->registerFunction(status, "get_int_eks", fFactory.get());
        aPlugin->registerFunction(status, "GetCurrentTimestampUTC", fGetCurrentTimestampUTC.get());

        l->write_line("Plugin init end");
        return &fPluginUnloadFlag;
    }
}
