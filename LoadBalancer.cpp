#include "LoadBalancer.h"
#include "IPAddress.h"
#include <iostream>
#include <random>

// constructor
LoadBalancer::LoadBalancer(int num_servers, int total_clock_cycles, int num_wait_clock_cycles, int min_request_time, int max_request_time)
 : num_servers(num_servers), total_clock_cycles(total_clock_cycles), last_scale_clock_cycle(0), num_wait_clock_cycles(num_wait_clock_cycles), min_request_time(min_request_time), max_request_time(max_request_time) {
    for (int i = 0; i < num_servers; i++) {
        addServer();
    }

    // shouldn't hardcode these, but for testing
    min_queue_size_for_scaling = 50 * this->num_servers;
    max_queue_size_for_scaling = 80 * this->num_servers;
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

// make random request
Request LoadBalancer::makeRandomRequest() {
    // static RNG so consecutive calls produce different values
    static std::mt19937 rng(std::random_device{}());

    // random distributions
    std::uniform_int_distribution<int> ip_dist(0, 255);
    std::uniform_int_distribution<int> time_dist(min_request_time, max_request_time);
    std::uniform_int_distribution<int> job_dist(0, 1); // 0 for 'P', 1 for 'S'

    // lambda to generate random IP address string
    auto random_ip = [&]() {
        return std::to_string(ip_dist(rng)) + "." +
               std::to_string(ip_dist(rng)) + "." +
               std::to_string(ip_dist(rng)) + "." +
               std::to_string(ip_dist(rng));
    };

    // create request with random values
    IPAddress in(random_ip());
    IPAddress out(random_ip());
    int time = time_dist(rng);
    char job = (job_dist(rng) == 0) ? 'P' : 'S';

    // return request
    return Request(in, out, time, job);
}