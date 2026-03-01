/**
 * @file LoadBalancer.cpp
 * @brief Implementation of the LoadBalancer class.
 */

#include "LoadBalancer.h"
#include "IPAddress.h"
#include "Color.h"
#include <iostream>
#include <random>

/**
 * @brief Constructor implementation.
 */
LoadBalancer::LoadBalancer(int initial_servers, int num_wait_clock_cycles,
                           const std::string& label)
 : label(label),
   last_scale_clock_cycle(0),
   num_wait_clock_cycles(num_wait_clock_cycles) {

    for (int i = 0; i < initial_servers; i++) {
        addServer();
    }
    updateScalingThresholds();
}

/**
 * @brief Adds a new WebServer instance.
 *
 * Assigns a sequential ID and updates scaling thresholds.
 */
void LoadBalancer::addServer() {
    int new_id = servers.size() + 1;
    servers.emplace_back(new_id);
    updateScalingThresholds();

    std::cout << Color::GREEN << "[LOAD BALANCER ACTION";
    if (!label.empty()) std::cout << " " << label;
    std::cout << "] Added server with ID: " << new_id
              << " | Total servers: " << servers.size()
              << Color::RESET << "\n";
}

/**
 * @brief Removes the most recently added WebServer.
 */
void LoadBalancer::removeServer() {
    if (!servers.empty()) {
        int removed_id = servers.back().getId();
        servers.pop_back();
        updateScalingThresholds();

        std::cout << Color::YELLOW << "[LOAD BALANCER ACTION";
        if (!label.empty()) std::cout << " " << label;
        std::cout << "] Removed server with ID: " << removed_id
                  << " | Total servers: " << servers.size()
                  << Color::RESET << "\n";
    }
}

/**
 * @brief Updates scaling thresholds based on server count.
 *
 * Thresholds are proportional to number of servers.
 */
void LoadBalancer::updateScalingThresholds() {
    min_queue_size_for_scaling = 50 * servers.size();
    max_queue_size_for_scaling = 80 * servers.size();
}

/**
 * @brief Assigns queued requests to available servers.
 */
void LoadBalancer::assignRequests(int current_cycle) {
    for (WebServer& server : servers) {
        if (!server.isBusy(current_cycle) && !request_queue.empty()) {
            Request& r = request_queue.front();
            server.assignRequest(r, current_cycle);
            request_queue.pop();

            std::cout << Color::YELLOW << "[LOAD BALANCER ACTION";
            if (!label.empty()) std::cout << " " << label;
            std::cout << "] Assigned request to server "
                      << server.getId()
                      << " at cycle " << current_cycle
                      << Color::RESET << "\n";
        }
    }
}

/**
 * @brief Evaluates whether scaling up or down is necessary.
 */
void LoadBalancer::maybeScale(int current_cycle) {
    if (!(current_cycle - last_scale_clock_cycle < num_wait_clock_cycles)) {

        std::size_t queue_size = request_queue.size();

        if (queue_size > max_queue_size_for_scaling) {
            addServer();
            last_scale_clock_cycle = current_cycle;

        } else if (queue_size < min_queue_size_for_scaling &&
                   servers.size() > 1) {
            removeServer();
            last_scale_clock_cycle = current_cycle;
        }
    }
}

/**
 * @brief Adds a request to the internal queue.
 */
void LoadBalancer::addRequest(Request& request) {
    request_queue.push(request);
}

/**
 * @brief Executes one simulation cycle.
 */
void LoadBalancer::goThroughClockCycle(int current_cycle) {
    assignRequests(current_cycle);
    maybeScale(current_cycle);
}

/**
 * @brief Returns queue size.
 */
std::size_t LoadBalancer::getQueueSize() {
    return request_queue.size();
}

/**
 * @brief Returns number of servers.
 */
int LoadBalancer::getServerCount() {
    return static_cast<int>(servers.size());
}

/**
 * @brief Returns label identifier.
 */
std::string LoadBalancer::getLabel() {
    return label;
}