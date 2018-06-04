#include <signal.h>
#include <cstring>
#include <unistd.h>
#include "console_reader.h"

bool ConsoleReader::interrupted;

void ConsoleReader::registerInterruptHandler() {
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    sigemptyset(&action.sa_mask);
    action.sa_handler = [](int) {
        interrupted = true;
    };
    sigaction(SIGINT, &action, nullptr);
}

bool ConsoleReader::read(std::string& res) {
    res.clear();
    while (true) {
        size_t i;
        for (i = 0; i < buffer_bcount; i++) {
            if (buffer[i] == '\n')
                break;
        }
        if (i != buffer_bcount) {
            res = buffer.substr(0, i);
            buffer = buffer.substr(i + 1);
            return true;
        } else {
            res = buffer;
        }

        ssize_t r = ::read(0, &buffer[0], buffer.size());
        buffer_bcount = (size_t) std::max<ssize_t>(r, 0);
        if (r < 0)
            return false;
    }
}