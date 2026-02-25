#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

struct SwitchConfig {
    int num_p_balancers = 1;
    int num_s_balancers = 1;
    int servers_per_p_balancer = 1;
    int servers_per_s_balancer = 1;
    int num_wait_clock_cycles = 3;
    int min_request_time = 1;
    int max_request_time = 5;
    int total_clock_cycles = 2000;
};

inline static std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

inline SwitchConfig loadSwitchConfig(const std::string& path = "switch.config_file_values") {
    SwitchConfig config_file_values;
    std::ifstream in(path);

    // use default values if file not found
    if (!in) return config_file_values; 

    // collect the values from the config file
    std::string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = trim(line.substr(0, eq));
        std::string val = trim(line.substr(eq + 1));
        try {
            int v = std::stoi(val);
            if (key == "num_p_balancers") config_file_values.num_p_balancers = v;
            else if (key == "num_s_balancers") config_file_values.num_s_balancers = v;
            else if (key == "servers_per_p_balancer") config_file_values.servers_per_p_balancer = v;
            else if (key == "servers_per_s_balancer") config_file_values.servers_per_s_balancer = v;
            else if (key == "num_wait_clock_cycles") config_file_values.num_wait_clock_cycles = v;
            else if (key == "min_request_time") config_file_values.min_request_time = v;
            else if (key == "max_request_time") config_file_values.max_request_time = v;
            else if (key == "total_clock_cycles") config_file_values.total_clock_cycles = v;
        } catch (...) {
            // ignore bad values
        }
    }
    return config_file_values;
}
