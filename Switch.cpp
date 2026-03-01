/**
 * @file Switch.cpp
 * @brief Implementation of the Switch class.
 */

#include "Switch.h"
#include "IPAddress.h"
#include <iostream>
#include <random>
#include "Color.h"

/**
 * @brief Static random engine used across all methods to avoid re-seeding every call.
 */
static std::mt19937 generator(std::random_device{}());

/**
 * @brief Constructs the Switch and initializes its load balancer pools.
 */
Switch::Switch(int num_p_balancers,
               int num_s_balancers,
               int servers_per_p_balancer,
               int servers_per_s_balancer,
               int num_wait_clock_cycles,
               int min_request_time,
               int max_request_time,
               const std::vector<IPRange>& blocked_ranges)
 : min_request_time(min_request_time),
   max_request_time(max_request_time),
   blocked_ranges(blocked_ranges) {

    // initialize load balancers
    for (int i = 0; i < num_p_balancers; i++) {
        std::string label = std::to_string(i+1) + "P";
        p_load_balancers.emplace_back(servers_per_p_balancer, num_wait_clock_cycles, label);
    }
    for (int i = 0; i < num_s_balancers; i++) {
        std::string label = std::to_string(i+1) + "S";
        s_load_balancers.emplace_back(servers_per_s_balancer, num_wait_clock_cycles, label);
    }
}

/**
 * @brief Generates a random Request, optionally forcing its job type.
 */
Request Switch::makeRandomRequest(char jobOverride) {
    // random distributions
    std::uniform_int_distribution<int> ip_dist(0, 255);
    std::uniform_int_distribution<int> time_dist(min_request_time, max_request_time);
    std::uniform_int_distribution<int> job_dist(0, 1); // 0 for 'P', 1 for 'S'

    // lambda to generate random IP address string
    auto random_ip = [&]() {
        return std::to_string(ip_dist(generator)) + "." +
               std::to_string(ip_dist(generator)) + "." +
               std::to_string(ip_dist(generator)) + "." +
               std::to_string(ip_dist(generator));
    };

    // create request with random values
    IPAddress in(random_ip());
    IPAddress out(random_ip());
    int time = time_dist(generator);
    char job = (job_dist(generator) == 0) ? 'P' : 'S';
    if (jobOverride == 'P' || jobOverride == 'S') job = jobOverride;

    // return request
    Request r(in, out, time, job);
    std::cout << Color::MAGENTA << "Generated Request: "
              << r.in.getString() << " -> " << r.out.getString()
              << " | time=" << r.time << " | job=" << r.job
              << Color::RESET << "\n";
    return r;
}

/**
 * @brief Routes a request to the least-busy load balancer of the correct type.
 *
 * Drops the request if it is blocked.
 */
void Switch::addRequestToBalancer(Request& request) {
    // check if this request should be blocked
    if (isBlocked(request)) {
        std::cout << Color::RED << "[SWITCH ACTION] Blocked IP: "
                  << request.in.getString()
                  << Color::RESET << "\n";
        return;
    }

    // check which balancer vector to use
    std::vector<LoadBalancer>& balancers = (request.job == 'P') ? p_load_balancers : s_load_balancers;

    // initialize to first balancer
    LoadBalancer* least_busy_balancer = &balancers[0];
    std::size_t min_queue_size = least_busy_balancer->getQueueSize();

    // iterate through and find balancer with smallest queue
    for (LoadBalancer& lb : balancers) {
        size_t queue_size = lb.getQueueSize();
        if (queue_size < min_queue_size) {
            min_queue_size = queue_size;
            least_busy_balancer = &lb;
        }
    }

    // add request to balancer with smallest queue
    if (least_busy_balancer != nullptr) {
        least_busy_balancer->addRequest(request);
    }
}

/**
 * @brief Calculates the total number of queued requests across all load balancers.
 *
 * Iterates through all Processing (P) and Streaming (S) load balancers
 * managed by the Switch and sums their individual queue sizes.
 *
 * @return Total number of pending requests across the entire system.
 */
std::size_t Switch::getTotalQueueSize() {
    std::size_t total = 0;

    for (LoadBalancer& lb : p_load_balancers) {
        total += lb.getQueueSize();
    }

    for (LoadBalancer& lb : s_load_balancers) {
        total += lb.getQueueSize();
    }

    return total;
}


/**
 * @brief Calculates the total number of Processing (P) servers.
 *
 * Iterates through all Processing load balancers and sums the number
 * of servers managed by each.
 *
 * @return Total count of P-type WebServers.
 */
int Switch::getServerCountP() {
    int total = 0;

    for (LoadBalancer& lb : p_load_balancers) {
        total += lb.getServerCount();
    }

    return total;
}


/**
 * @brief Calculates the total number of Streaming (S) servers.
 *
 * Iterates through all Streaming load balancers and sums the number
 * of servers managed by each.
 *
 * @return Total count of S-type WebServers.
 */
int Switch::getServerCountS() {
    int total = 0;

    for (LoadBalancer& lb : s_load_balancers) {
        total += lb.getServerCount();
    }

    return total;
}

/**
 * @brief Checks whether a request's source IP is within any blocked IP range.
 */
bool Switch::isBlocked(Request& request) {
    // check if the request's source IP is in any blocked range
    for (const auto& range : blocked_ranges) {
        unsigned int in_val = request.in.getValue();
        unsigned int low_val = range.low.getValue();
        unsigned int high_val = range.high.getValue();

        if (in_val >= low_val && in_val <= high_val) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Runs one clock cycle for each load balancer in both pools.
 */
void Switch::goThroughClockCycleAllLoadBalancers(int current_cycle) {
    // run a clock cycle for each load balancer
    for (LoadBalancer& lb : p_load_balancers) {
        lb.goThroughClockCycle(current_cycle);
    }
    for (LoadBalancer& lb : s_load_balancers) {
        lb.goThroughClockCycle(current_cycle);
    }
}

/**
 * @brief Prints a status report of all load balancers.
 *
 * Displays server count and queue size for each load balancer, separated by job type.
 */
void Switch::reportStatus(int current_cycle) {
    // helper that writes the same text to both cout (log) and cerr (console)
    auto emit = [&](const std::string &text) {
        std::cout << text;
        std::cerr << text;
    };

    emit(Color::TURQUOISE + std::string("[SWITCH] Status report at cycle ")
         + std::to_string(current_cycle) + "\n");

    for (LoadBalancer& lb : p_load_balancers) {
        emit("  Balancer " + lb.getLabel()
             + " (P) servers=" + std::to_string(lb.getServerCount())
             + " queue=" + std::to_string(lb.getQueueSize()) + "\n");
    }
    for (LoadBalancer& lb : s_load_balancers) {
        emit("  Balancer " + lb.getLabel()
             + " (S) servers=" + std::to_string(lb.getServerCount())
             + " queue=" + std::to_string(lb.getQueueSize()) + "\n");
    }
    emit(Color::RESET);
}

/**
 * @brief Starts the simulation, preloads requests, and runs for the given number of cycles.
 */
void Switch::start(int total_clock_cycles) {

    // summary statistics
    std::size_t starting_queue_size = 0;
    std::size_t ending_queue_size = 0;
    int total_requests_generated = 0;
    int total_requests_blocked = 0;
    int starting_servers_p = getServerCountP();
    int starting_servers_s = getServerCountS();
    int total_starting_servers = starting_servers_p + starting_servers_s;
    int ending_servers_p = 0;
    int ending_servers_s = 0;
    int total_ending_servers = 0;

    // preload each balancer with 100 requests per server
    std::cout << Color::CYAN << "[SWITCH] Preloading requests at start..." << Color::RESET << "\n";
    for (LoadBalancer& lb : p_load_balancers) {
        int servers = lb.getServerCount();
        int requests_to_create = 100 * servers;
        std::cout << Color::CYAN << "  Balancer " << lb.getLabel()
                  << " (type P) has " << servers << " server(s); adding "
                  << requests_to_create << " requests" << Color::RESET << "\n";
        for (int i = 0; i < requests_to_create; ++i) {
            Request r = makeRandomRequest('P');
            lb.addRequest(r);
        }
    }
    for (LoadBalancer& lb : s_load_balancers) {
        int servers = lb.getServerCount();
        int requests_to_create = 100 * servers;
        std::cout << Color::CYAN << "  Balancer " << lb.getLabel()
                  << " (type S) has " << servers << " server(s); adding "
                  << requests_to_create << " requests" << Color::RESET << "\n";
        for (int i = 0; i < requests_to_create; ++i) {
            Request r = makeRandomRequest('S');
            lb.addRequest(r);
        }
    }

    // get starting queue size
    starting_queue_size = getTotalQueueSize();

    // go through clock cycles
    for (int cycle = 1; cycle <= total_clock_cycles; ++cycle) {
        // generate random number of requests
        std::uniform_int_distribution<int> request_count_dist(0, 5);
        int num_requests = request_count_dist(generator);
        for (int i = 0; i < num_requests; ++i) {
            Request r = makeRandomRequest();
            total_requests_generated++;
            if (isBlocked(r)) {
                total_requests_blocked++;
            }
            addRequestToBalancer(r);
        }
        goThroughClockCycleAllLoadBalancers(cycle);

        // report every 50 cycles
        if (cycle % 50 == 0) {
            reportStatus(cycle);
        }

        std::cout << Color::BLUE << "--- End of cycle " << cycle << " ---"
                  << Color::RESET << "\n";
    }

    // get ending stats size
    ending_queue_size = getTotalQueueSize();
    ending_servers_p = getServerCountP();
    ending_servers_s = getServerCountS();
    total_ending_servers = ending_servers_p + ending_servers_s;

    // print summary statistics
    std::cout << Color::GREEN << "\n[SWITCH] Simulation complete!\n"
              << "  Total requests generated: " << total_requests_generated << "\n"
              << "  Total requests blocked: " << total_requests_blocked << "\n"
              << "  Starting queue size: " << starting_queue_size << "\n"
              << "  Ending queue size: " << ending_queue_size << "\n"
              << "  Starting servers (P): " << starting_servers_p << "\n"
              << "  Starting servers (S): " << starting_servers_s << "\n"
              << "  Total starting servers: " << total_starting_servers << "\n"
              << "  Ending servers (P): " << ending_servers_p << "\n"
              << "  Ending servers (S): " << ending_servers_s << "\n"
                << "  Total ending servers: " << total_ending_servers << "\n";
}
