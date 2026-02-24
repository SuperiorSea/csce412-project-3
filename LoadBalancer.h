#pragma once
#include "WebServer.h"
#include "RequestQueue.h"
#include <vector>

class LoadBalancer {
    private:
        // for the servers and queue
        std::vector<WebServer> servers;
        RequestQueue request_queue;

        // for initialization
        int num_servers;
        int total_clock_cycles;

        // for scaling, track the last clock cycle we scaled, and how many cycles we have to wait until scaling again
        int last_scale_clock_cycle;
        int num_wait_clock_cycles;

        // for making random requests
        int min_request_time;
        int max_request_time;

        // for scaling
        int min_queue_size_for_scaling;
        int max_queue_size_for_scaling;

        // helpers
        void addServer();
        void removeServer();

        // make random request (public so it can be tested)
    public:
        Request makeRandomRequest();

        // constructor
        LoadBalancer(int num_servers, int total_clock_cycles, int num_wait_clock_cycles, int min_request_time, int max_request_time);
};