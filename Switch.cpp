#include "Switch.h"
#include "IPAddress.h"
#include <iostream>
#include <random>

// static random engine used across all methods to avoid re-seeding every call
static std::mt19937 generator(std::random_device{}());

// constructor
Switch::Switch(int num_p_balancers,
               int num_s_balancers,
               int servers_per_p_balancer,
               int servers_per_s_balancer,
               int num_wait_clock_cycles,
               int min_request_time,
               int max_request_time)
 : min_request_time(min_request_time), max_request_time(max_request_time) {
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

// helpers
Request Switch::makeRandomRequest() {
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

    // return request
    return Request(in, out, time, job);
}

void Switch::addRequestToBalancer(Request& request) {
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

void Switch::goThroughClockCycleAllLoadBalancers(int current_cycle) {
    // run a clock cycle for each load balancer
    for (LoadBalancer& lb : p_load_balancers) {
        lb.goThroughClockCycle(current_cycle);
    }
    for (LoadBalancer& lb : s_load_balancers) {
        lb.goThroughClockCycle(current_cycle);
    }
}

void Switch::start(int total_clock_cycles) {
    std::default_random_engine generator;
    for (int cycle = 0; cycle < total_clock_cycles; ++cycle) {
        // generate random number of requests
        std::uniform_int_distribution<int> request_count_dist(0, 5);
        int num_requests = request_count_dist(generator);
        for (int i = 0; i < num_requests; ++i) {
            Request r = makeRandomRequest();
            std::cout << r.in.getValue() << " -> " << r.out.getValue() << " | time=" << r.time << " | job=" << r.job << "\n";
            addRequestToBalancer(r);
        }
        goThroughClockCycleAllLoadBalancers(cycle);
        std::cout << "--- End of cycle " << cycle << " ---\n";
    }
}