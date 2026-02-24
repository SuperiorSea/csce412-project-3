#pragma once
#include <WebServer.h>
#include <RequestQueue.h>
#include <vector>

class LoadBalancer {
    private:
        // for the servers and queue
        std::vector<WebServer> servers;
        RequestQueue request_queue;

        // for scaling, track the last clock cycle we scaled, and how many cycles we have to wait until scaling again
        int last_scale_clock_cycle;
        int num_wait_clock_cycles;

        // for making random requests
        int min_request_time;
        int max_request_time;

        // helpers
        void addServer();
        void removeServer();

        // make random request
        Request makeRandomRequest();
    public:
        // constructor
        LoadBalancer(int num_servers, int num_wait_clock_cycles, int min_request_time, int max_request_time);
}