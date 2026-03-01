/**
 * @file Switch.h
 * @brief Defines the Switch class that routes generated requests to multiple load balancers.
 *
 * The Switch sits above multiple LoadBalancer instances and is responsible for:
 * - Generating random requests
 * - Blocking requests from specified IP ranges
 * - Routing requests to the least-busy load balancer of the correct job type
 * - Advancing all load balancers through each clock cycle
 * - Reporting status periodically
 */

#pragma once
#include "LoadBalancer.h"
#include "IPAddress.h"
#include <vector>
#include <random>

/**
 * @class Switch
 * @brief Top-level router that distributes requests to multiple load balancers.
 *
 * The Switch owns separate pools of load balancers for each job type:
 * - Processing ('P')
 * - Streaming ('S')
 *
 * It generates requests, filters them using blocked IP ranges, and forwards
 * allowed requests to the least-busy load balancer within the appropriate pool.
 */
class Switch {
private:
    /**
     * @brief Load balancers responsible for processing ('P') jobs.
     */
    std::vector<LoadBalancer> p_load_balancers;

    /**
     * @brief Load balancers responsible for streaming ('S') jobs.
     */
    std::vector<LoadBalancer> s_load_balancers;

    /**
     * @brief Minimum randomly-generated request processing time (clock cycles).
     */
    int min_request_time;

    /**
     * @brief Maximum randomly-generated request processing time (clock cycles).
     */
    int max_request_time;

    /**
     * @brief Ranges of source IP addresses that should be blocked.
     */
    std::vector<IPRange> blocked_ranges;

    /**
     * @brief Generates a random Request.
     *
     * If @p jobOverride is provided as 'P' or 'S', the request's job type will be forced.
     * Otherwise, the job type is chosen randomly.
     *
     * @param jobOverride Optional job type override ('P' or 'S'), or '\0' for random.
     * @return Newly generated Request instance.
     */
    Request makeRandomRequest(char jobOverride = '\0');

    /**
     * @brief Routes a request to the appropriate load balancer.
     *
     * If the request is blocked (based on its source IP), it will be dropped.
     * Otherwise, it is sent to the least-busy (smallest queue) load balancer
     * in the pool corresponding to its job type.
     *
     * @param request Request to route.
     */
    void addRequestToBalancer(Request& request);

    /**
     * @brief Advances all load balancers by one simulation clock cycle.
     *
     * Calls goThroughClockCycle(current_cycle) on every load balancer in both pools.
     *
     * @param current_cycle Current simulation clock cycle.
     */
    void goThroughClockCycleAllLoadBalancers(int current_cycle);

    /**
     * @brief Determines whether a request should be blocked.
     *
     * A request is blocked if its source IP falls within any configured blocked IP range.
     *
     * @param request Request to evaluate.
     * @return True if request should be blocked, false otherwise.
     */
    bool isBlocked(Request& request);

    std::size_t getTotalQueueSize();
    int getServerCountP();
    int getServerCountS();

public:
    /**
     * @brief Constructs the Switch and initializes all load balancers.
     *
     * Creates:
     * - @p num_p_balancers load balancers for 'P' jobs
     * - @p num_s_balancers load balancers for 'S' jobs
     *
     * Each load balancer is initialized with the requested number of servers and
     * a scaling cooldown period.
     *
     * @param num_p_balancers Number of processing ('P') load balancers.
     * @param num_s_balancers Number of streaming ('S') load balancers.
     * @param servers_per_p_balancer Initial servers per processing load balancer.
     * @param servers_per_s_balancer Initial servers per streaming load balancer.
     * @param num_wait_clock_cycles Cooldown cycles between scaling actions.
     * @param min_request_time Minimum request processing time (cycles).
     * @param max_request_time Maximum request processing time (cycles).
     * @param blocked_ranges Optional list of blocked IP ranges.
     */
    Switch(int num_p_balancers,
           int num_s_balancers,
           int servers_per_p_balancer,
           int servers_per_s_balancer,
           int num_wait_clock_cycles,
           int min_request_time,
           int max_request_time,
           const std::vector<IPRange>& blocked_ranges = {});

    /**
     * @brief Prints a status report showing queue sizes and server counts per load balancer.
     *
     * @param current_cycle Current simulation clock cycle.
     */
    void reportStatus(int current_cycle);

    /**
     * @brief Starts the simulation for a given number of clock cycles.
     *
     * The start sequence:
     * - Preloads each load balancer with 100 requests per server
     * - Runs the simulation loop:
     *   - Generates a random number of new requests per cycle
     *   - Routes requests via addRequestToBalancer()
     *   - Advances all load balancers
     *   - Reports status every 50 cycles
     *
     * @param total_clock_cycles Total number of cycles to simulate.
     */
    void start(int total_clock_cycles);
};