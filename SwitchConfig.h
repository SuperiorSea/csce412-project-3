#pragma once
#include <string>
#include <vector>
#include "IPAddress.h"

struct SwitchConfig {
    int num_p_balancers = 1;
    int num_s_balancers = 1;
    int servers_per_p_balancer = 1;
    int servers_per_s_balancer = 1;
    int num_wait_clock_cycles = 3;
    int min_request_time = 1;
    int max_request_time = 5;
    int total_clock_cycles = 2000;
    std::vector<IPRange> blocked_ranges;  // IP ranges to block
};

// loads the config file into a SwitchConfig struct
SwitchConfig loadSwitchConfig(const std::string& path);
