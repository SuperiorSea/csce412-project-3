/**
 * @file SwitchConfig.cpp
 * @brief Implementation of configuration file loading for SwitchConfig.
 */

#include "SwitchConfig.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

/**
 * @brief Trims whitespace from both ends of a string.
 *
 * @param s Input string.
 * @return Trimmed string.
 */
std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

/**
 * @brief Loads configuration values from a file.
 *
 * Reads:
 * - Key-value pairs in the format key=value
 * - IP block ranges in the format:
 *     block <low_ip> - <high_ip>
 *
 * Ignores:
 * - Blank lines
 * - Comment lines beginning with '#'
 * - Malformed entries
 *
 * If the file cannot be opened, default configuration values are returned.
 *
 * @param path Path to configuration file (defaults to "switch.config_file_values").
 * @return Populated SwitchConfig object.
 */
SwitchConfig loadSwitchConfig(const std::string& path = "switch.config_file_values") {

    SwitchConfig config_file_values;
    std::ifstream in(path);

    // use default values if file not found
    if (!in) return config_file_values;

    std::string line;
    while (std::getline(in, line)) {

        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        // handle block ranges (format: block 1.1.1.1 - 100.1.1.1)
        if (line.find("block ") == 0) {
            std::string range_part = line.substr(6);
            range_part = trim(range_part);
            size_t dash_pos = range_part.find('-');

            if (dash_pos != std::string::npos) {
                try {
                    std::string low_str = trim(range_part.substr(0, dash_pos));
                    std::string high_str = trim(range_part.substr(dash_pos + 1));

                    IPAddress low(low_str);
                    IPAddress high(high_str);

                    config_file_values.blocked_ranges.emplace_back(low, high);
                } catch (...) {
                    // ignore malformed block ranges
                }
            }
            continue;
        }

        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;

        std::string key = trim(line.substr(0, eq));
        std::string val = trim(line.substr(eq + 1));

        try {
            int v = std::stoi(val);

            if (key == "num_p_balancers")
                config_file_values.num_p_balancers = v;
            else if (key == "num_s_balancers")
                config_file_values.num_s_balancers = v;
            else if (key == "servers_per_p_balancer")
                config_file_values.servers_per_p_balancer = v;
            else if (key == "servers_per_s_balancer")
                config_file_values.servers_per_s_balancer = v;
            else if (key == "num_wait_clock_cycles")
                config_file_values.num_wait_clock_cycles = v;
            else if (key == "min_request_time")
                config_file_values.min_request_time = v;
            else if (key == "max_request_time")
                config_file_values.max_request_time = v;
            else if (key == "total_clock_cycles")
                config_file_values.total_clock_cycles = v;

        } catch (...) {
            // ignore malformed numeric values
        }
    }

    return config_file_values;
}