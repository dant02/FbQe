// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Inc.h"

using namespace std;

namespace FbQe
{
    FB_BOOLEAN fUnloadFlag = FB_FALSE;
    FB_BOOLEAN* fTheirUnloadFlag;

    IncFactory* fFactory;
    ofstream f;

    static std::string time_now()
    {
        // based on answer
        // https://stackoverflow.com/questions/16077299/how-to-print-current-time-with-milliseconds-using-c-c11/66291527#66291527
        using namespace std::chrono;
        using clock = system_clock;

        const auto current_time_point{ clock::now() };
        const auto current_time{ clock::to_time_t(current_time_point) };
        const auto current_localtime{ *std::localtime(&current_time) };
        const auto current_time_since_epoch{ current_time_point.time_since_epoch() };
        const auto current_milliseconds{ duration_cast<milliseconds> (current_time_since_epoch).count() % 1000 };

        std::ostringstream stream;
        stream << std::put_time(&current_localtime, "%F %T") << "." << std::setw(3) << std::setfill('0') << current_milliseconds;
        return stream.str();
    }

    static void log_write(std::string aMessage)
    {
        f << "\r\n" << time_now() << "\t" << aMessage;
        f.flush();
    }

    extern "C" __declspec(dllexport) FB_BOOLEAN* __cdecl firebird_udr_plugin(IStatus* status, FB_BOOLEAN* theirUnloadFlag, Firebird::IUdrPlugin* udrPlugin)
    {
        f.open("c:\\fb\\fbqe.log", std::ios_base::app);
        log_write("Plugin init");
        fFactory = new IncFactory(&f);

        log_write("Register functions");
        udrPlugin->registerFunction((ThrowStatusWrapper*)status, "get_int_eks", fFactory);
        fTheirUnloadFlag = theirUnloadFlag;
        
        log_write("Plugin init end");
        return &fUnloadFlag;
    }
}
