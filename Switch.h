#pragma once
#include "LoadBalancer.h"
#include "IPAddress.h"
#include <vector>
#include <random>

class Switch {
    private:
        // two diff load balancer vectors for P and S jobs
        std::vector<LoadBalancer> p_load_balancers;
        std::vector<LoadBalancer> s_load_balancers;

        // for making random requests
        int min_request_time;
        int max_request_time;

        // IP ranges to block
        std::vector<IPRange> blocked_ranges;

        // helpers
        Request makeRandomRequest(char jobOverride = '\0'); // optionally add a specific job type
        void addRequestToBalancer(Request& request);
        void goThroughClockCycleAllLoadBalancers(int current_cycle);
        bool isBlocked(Request& request);  // check if request should be blocked
    
    public:
        // constructor
        Switch(int num_p_balancers,
               int num_s_balancers,
               int servers_per_p_balancer,
               int servers_per_s_balancer,
               int num_wait_clock_cycles,
               int min_request_time,
               int max_request_time,
               const std::vector<IPRange>& blocked_ranges = {});
        
        // status report of switch
        void reportStatus(int current_cycle);
        
        // starts the program
        void start(int total_clock_cycles);
};