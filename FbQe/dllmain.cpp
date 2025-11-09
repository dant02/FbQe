// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

namespace FbQe {
    using namespace System;

    public ref class I18N {
    public:
        static DateTime GetCurrentUtcTimestamp() {
            return DateTime::UtcNow;
        }
    };
}