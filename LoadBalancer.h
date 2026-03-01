/**
 * @file LoadBalancer.h
 * @brief Defines the LoadBalancer class for distributing requests across WebServers.
 *
 * The LoadBalancer manages:
 * - A collection of WebServer instances
 * - A RequestQueue for incoming requests
 * - Dynamic scaling based on queue size
 * - Assignment of requests per clock cycle
 */

#pragma once
#include "WebServer.h"
#include "RequestQueue.h"
#include <vector>

/**
 * @class LoadBalancer
 * @brief Simulates a load balancer that distributes requests to servers.
 *
 * The LoadBalancer:
 * - Maintains a pool of WebServers
 * - Assigns requests in FIFO order
 * - Dynamically scales servers up or down
 * - Operates on discrete clock cycles
 */
class LoadBalancer {
private:

    /** @brief Collection of managed WebServer instances. */
    std::vector<WebServer> servers;

    /** @brief Queue storing incoming requests. */
    RequestQueue request_queue;

    /**
     * @brief Optional label for log messages.
     * Used to distinguish workload types (e.g., "P" or "S").
     */
    std::string label;

    /** @brief Initial number of servers. */
    int num_servers;

    /** @brief Total clock cycles (if tracked externally). */
    int total_clock_cycles;

    /** @brief Last clock cycle when scaling occurred. */
    int last_scale_clock_cycle;

    /**
     * @brief Minimum number of cycles to wait before scaling again.
     * Prevents rapid oscillation in server count.
     */
    int num_wait_clock_cycles;

    /** @brief Lower queue threshold for scaling down. */
    size_t min_queue_size_for_scaling;

    /** @brief Upper queue threshold for scaling up. */
    size_t max_queue_size_for_scaling;

    /** @brief Adds a new WebServer to the pool. */
    void addServer();

    /** @brief Removes the most recently added WebServer. */
    void removeServer();

    /** @brief Updates scaling thresholds based on current server count. */
    void updateScalingThresholds();

    /**
     * @brief Assigns queued requests to available servers.
     * @param current_cycle Current simulation clock cycle.
     */
    void assignRequests(int current_cycle);

    /**
     * @brief Determines whether scaling is necessary.
     * @param current_cycle Current simulation clock cycle.
     */
    void maybeScale(int current_cycle);

public:

    /**
     * @brief Constructs a LoadBalancer.
     *
     * @param initial_servers Number of servers to initialize.
     * @param num_wait_clock_cycles Cooldown period before scaling again.
     * @param label Optional identifier for logging.
     */
    LoadBalancer(int initial_servers, int num_wait_clock_cycles,
                 const std::string& label = "");

    /**
     * @brief Adds a new incoming request to the queue.
     *
     * @param request Request to enqueue.
     */
    void addRequest(Request& request);

    /**
     * @brief Executes one clock cycle of simulation.
     *
     * Performs:
     * - Request assignment
     * - Scaling evaluation
     *
     * @param current_cycle Current simulation clock cycle.
     */
    void goThroughClockCycle(int current_cycle);

    /**
     * @brief Returns current queue size.
     */
    std::size_t getQueueSize();

    /**
     * @brief Returns number of active servers.
     */
    int getServerCount();

    /**
     * @brief Returns label associated with this LoadBalancer.
     */
    std::string getLabel();
};