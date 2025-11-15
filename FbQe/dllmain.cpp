// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Inc.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace FbQe {

    bool fUnloadFlag = false;

    EXTERN_C __declspec(dllexport) bool* __cdecl firebird_udr_plugin(IStatus* status, bool* theirUnloadFlag, Firebird::IUdrPlugin* udrPlugin)
    {
        ofstream f;
        f.open("c:\\fb\\example.txt");
        f << "Plugin loaded.\r\n";

        auto fac =  new FbQe::IncFactory();
        auto tsw = new ThrowStatusWrapper(status);

        f << "\r\nRegister functions";
        f.flush();
        udrPlugin->registerFunction(tsw, "GetInt", fac);

        f << "\r\nReturn";
        f.flush();

        return &fUnloadFlag;
    }

}