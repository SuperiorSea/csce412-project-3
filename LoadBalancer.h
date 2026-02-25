#pragma once
#include "WebServer.h"
#include "RequestQueue.h"
#include <vector>

class LoadBalancer {
    private:
        // for the servers and queue
        std::vector<WebServer> servers;
        RequestQueue request_queue;

        // optional label used in log messages (e.g. "P" or "S")
        std::string label;

        // for initialization
        int num_servers;
        int total_clock_cycles;

        // for scaling, track the last clock cycle we scaled, and how many cycles we have to wait until scaling again
        int last_scale_clock_cycle;
        int num_wait_clock_cycles;

        // for scaling
        size_t min_queue_size_for_scaling;
        size_t max_queue_size_for_scaling;

        // helpers
        void addServer();
        void removeServer();
        void updateScalingThresholds();

        // assigning requests/scaling
        void assignRequests(int current_cycle);
        void maybeScale(int current_cycle);

    public:
        // constructor
        LoadBalancer(int initial_servers, int num_wait_clock_cycles,
                     const std::string& label = "");

        // add received request to queue
        void addRequest(Request& request);

        // actions to be performed each cycle: assign requests and maybe scale
        void goThroughClockCycle(int current_cycle);

        // getters
        std::size_t getQueueSize();
        int getServerCount();
        std::string getLabel();
};