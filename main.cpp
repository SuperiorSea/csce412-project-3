/**
 * @file main.cpp
 * @brief Main application for the project
 */

#include <iostream>
#include <fstream>
#include "RequestQueue.h"
#include "WebServer.h"
#include "LoadBalancer.h"
#include "Switch.h"
#include "SwitchConfig.h"
#include <sstream>

// create a log file at global scope so it stays alive until the program exits
static std::ofstream logFile("switchlog.ansi");

int main() {
    // make sure the file opened successfully before proceeding
    if (!logFile) {
        std::cerr << "ERROR: could not open switchlog.ansi for writing\n";
        return 1;
    }
    // redirect standard output to the file (ANSI escape codes are preserved)
    std::cout.rdbuf(logFile.rdbuf());

    // load runtime config (falls back to sensible defaults)
    SwitchConfig cfg = loadSwitchConfig("switch.cfg");
    std::cout << "Switch config: P=" << cfg.num_p_balancers
              << " S=" << cfg.num_s_balancers
              << " servers(P/S)=" << cfg.servers_per_p_balancer << "/" << cfg.servers_per_s_balancer
              << " waitCycles=" << cfg.num_wait_clock_cycles
              << " timeRange=[" << cfg.min_request_time << "," << cfg.max_request_time << "]"
              << " totalCycles=" << cfg.total_clock_cycles << "\n";

    Switch sw(cfg.num_p_balancers,
              cfg.num_s_balancers,
              cfg.servers_per_p_balancer,
              cfg.servers_per_s_balancer,
              cfg.num_wait_clock_cycles,
              cfg.min_request_time,
              cfg.max_request_time,
              cfg.blocked_ranges);
    sw.start(cfg.total_clock_cycles);
    std::cout << "  Request time range: " << cfg.min_request_time << " - " << cfg.max_request_time << " cycles\n"
              << "  Blocked IP ranges: " << cfg.blocked_ranges.size() << "\n";
    for (const IPRange& r : cfg.blocked_ranges) {
        std::cout << "    " << r.low.getString() << " - " << r.high.getString() << "\n";
    }
    return 0;
}