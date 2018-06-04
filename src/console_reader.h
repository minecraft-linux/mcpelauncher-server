#pragma once

#include <string>

class ConsoleReader {

private:
    static bool interrupted;

    std::string buffer;
    size_t buffer_bcount = 0;

public:
    static void registerInterruptHandler();

    ConsoleReader() {
        buffer.resize(4096);
    }

    bool read(std::string& res);

};