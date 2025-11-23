#pragma once

namespace FbQe {
    class Log {
    public:
        Log();
        void write_line(std::string aMessage);
        std::string time_now();
    private:
        std::ofstream fStream;
    };
}
