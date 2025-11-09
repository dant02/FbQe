// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Inc.h"

#include <iostream>
#include <fstream>

using namespace std;

EXTERN_C FB_BOOLEAN* firebird_udr_plugin(IStatus* status,  FB_BOOLEAN* theirUnloadFlag, Firebird::IUdrPlugin* udrPlugin)
{
    ofstream myfile;
    myfile.open("example.txt");
    myfile << "Writing this to a file.\n";

    auto fac =  new FbQe::IncFactory();

    auto st = (ThrowStatusWrapper*)status;

    udrPlugin->registerFunction(st, "GetInt", fac);

    FB_BOOLEAN result = FB_FALSE;
    return &result;
}