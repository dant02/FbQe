#pragma once

namespace FbQe {
    class Log {
    public:
        Log();
        void write_line(std::string aMessage);
    private:
        std::ofstream fStream;
        void write_time_now();
    };
}
