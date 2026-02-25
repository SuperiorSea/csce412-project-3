#include "LoadBalancer.h"
#include "IPAddress.h"
#include <iostream>
#include <random>

// constructor
LoadBalancer::LoadBalancer(int initial_servers, int num_wait_clock_cycles)
 : last_scale_clock_cycle(0), num_wait_clock_cycles(num_wait_clock_cycles){
    for (int i = 0; i < initial_servers; i++) {
        addServer();
    }
    updateScalingThresholds();
}

// helpers
void LoadBalancer::addServer() {
    int new_id = servers.size() + 1; // simple id assignment
    servers.emplace_back(new_id);
    updateScalingThresholds();
    std::cout << "[WEBSERVER ACTION] Added server with ID: " << new_id << " | Total servers: " << servers.size() << "\n";
}

void LoadBalancer::removeServer() {
    if (!servers.empty()) {
        int removed_id = servers.back().getId();
        servers.pop_back();
        updateScalingThresholds();
        std::cout << "[WEBSERVER ACTION] Removed server with ID: " << removed_id << " | Total servers: " << servers.size() << "\n";
    }
}

void LoadBalancer::updateScalingThresholds() {
    min_queue_size_for_scaling = 50 * servers.size();
    max_queue_size_for_scaling = 80 * servers.size();
}

// assign requests/scaling
void LoadBalancer::assignRequests(int current_cycle) {
    // for each webserver, if its not busy and theres a request in the queue, assigne it
    for (WebServer& server : servers) {
        if (!server.isBusy(current_cycle) && !request_queue.empty()) {
            Request& r = request_queue.front();
            server.assignRequest(r, current_cycle);
            request_queue.pop();
            std::cout << "[LOAD BALANCER ACTION] Assigned request to server " << server.getId() << " at cycle " << current_cycle << "\n";
        }
    }
}

void LoadBalancer::maybeScale(int current_cycle) {
    // if past threshold for checking again
    if (!(current_cycle - last_scale_clock_cycle < num_wait_clock_cycles)) {
        std::size_t queue_size = request_queue.size();
        // if queue too big, upscale, otherwise downscale
        if (queue_size > max_queue_size_for_scaling) {
            addServer();
            last_scale_clock_cycle = current_cycle;
        } else if (queue_size < min_queue_size_for_scaling && servers.size() > 1) {
            removeServer();
            last_scale_clock_cycle = current_cycle;
        }
    }
}

// add received request to queue
void LoadBalancer::addRequest(Request& request) {
    request_queue.push(request);
}

// actions to be performed each cycle: assign requests and maybe scale
void LoadBalancer::goThroughClockCycle(int current_cycle) {
    assignRequests(current_cycle);
    maybeScale(current_cycle);
}

// getter
std::size_t LoadBalancer::getQueueSize() {
    return request_queue.size();
}