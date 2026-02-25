// simple color header for output formatting
#pragma once
#include <string>

namespace Color {
    static const std::string RESET  = "\033[0m";
    static const std::string RED    = "\033[31m";
    static const std::string GREEN  = "\033[32m";
    static const std::string YELLOW = "\033[33m";
    static const std::string BLUE   = "\033[34m";
    static const std::string MAGENTA= "\033[35m";
    static const std::string CYAN   = "\033[36m";
    static const std::string WHITE  = "\033[37m";
}
