#include "LoadBalancer.h"
#include "IPAddress.h"
#include <iostream>

// constructor
LoadBalancer::LoadBalancer(int num_servers, int num_wait_clock_cycles, int min_request_time, int max_request_time)
 : last_scale_clock_cycle(0), num_wait_clock_cycles(num_wait_clock_cycles), min_request_time(min_request_time), max_request_time(max_request_time) {
    for (int i = 0; i < num_servers; i++) {
        addServer();
    }
}

// helpers
void LoadBalancer::addServer() {
    int new_id = servers.size() + 1; // simple id assignment
    servers.emplace_back(new_id);
    std::cout << "[WEBSERVER ACTION] Added server with ID: " << new_id << " | Total servers: " << servers.size() << "\n";
}

void LoadBalancer::removeServer() {
    if (!servers.empty()) {
        int removed_id = servers.back().getId();
        servers.pop_back();
        std::cout << "[WEBSERVER ACTION] Removed server with ID: " << removed_id << " | Total servers: " << servers.size() << "\n";
    }
}