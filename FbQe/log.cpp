#include "pch.h"
#include "log.h"

namespace FbQe {
    Log::Log() {
        auto f = &(this->fStream);
        f->open("c:\\fb\\fbqe.log", std::ios_base::app);
    }

    void Log::write_line(std::string aMessage) {
        auto f = &(this->fStream);
        *f << "\r\n";
        write_time_now();
        *f << "\t" << aMessage;
        f->flush();
    }

    void Log::write_time_now() {
        // based on answer
        // https://stackoverflow.com/questions/16077299/how-to-print-current-time-with-milliseconds-using-c-c11/66291527#66291527
        using namespace std::chrono;
        using clock = system_clock;

        const auto current_time_point{ clock::now() };
        const auto current_time{ clock::to_time_t(current_time_point) };
        const auto current_localtime{ *std::localtime(&current_time) };
        const auto current_time_since_epoch{ current_time_point.time_since_epoch() };
        const auto current_milliseconds{ duration_cast<milliseconds> (current_time_since_epoch).count() % 1000 };

        auto f = &(this->fStream);
        *f << std::put_time(&current_localtime, "%F %T") << "." << std::setw(3) << std::setfill('0') << current_milliseconds;
    }
}