/**
 * @file SwitchConfig.h
 * @brief Defines the SwitchConfig structure and configuration loader.
 *
 * This file provides:
 * - A configuration structure used to initialize the Switch
 * - A function to load configuration values from a file
 *
 * The configuration file supports:
 * - Key-value pairs (key=value)
 * - IP block ranges using the format:
 *     block 1.1.1.1 - 100.1.1.1
 * - Comments beginning with '#'
 */

#pragma once
#include <string>
#include <vector>
#include "IPAddress.h"

/**
 * @struct SwitchConfig
 * @brief Stores configuration values for initializing a Switch instance.
 *
 * Contains:
 * - Load balancer counts
 * - Server counts
 * - Scaling parameters
 * - Request timing limits
 * - Total simulation length
 * - IP ranges to block
 *
 * Default values are provided and will be used if the configuration file
 * is missing or incomplete.
 */
struct SwitchConfig {

    /** @brief Number of processing ('P') load balancers. */
    int num_p_balancers = 1;

    /** @brief Number of streaming ('S') load balancers. */
    int num_s_balancers = 1;

    /** @brief Initial servers per processing load balancer. */
    int servers_per_p_balancer = 1;

    /** @brief Initial servers per streaming load balancer. */
    int servers_per_s_balancer = 1;

    /** @brief Cooldown cycles between scaling operations. */
    int num_wait_clock_cycles = 3;

    /** @brief Minimum randomly generated request processing time. */
    int min_request_time = 1;

    /** @brief Maximum randomly generated request processing time. */
    int max_request_time = 5;

    /** @brief Total simulation clock cycles to run. */
    int total_clock_cycles = 2000;

    /** @brief List of IP address ranges that should be blocked. */
    std::vector<IPRange> blocked_ranges;
};

/**
 * @brief Loads configuration values from a file into a SwitchConfig structure.
 *
 * If the file does not exist, default values are returned.
 *
 * Supported configuration format:
 * @code
 * num_p_balancers=2
 * num_s_balancers=1
 * block 192.168.1.1 - 192.168.1.255
 * @endcode
 *
 * @param path Path to configuration file.
 * @return Populated SwitchConfig structure.
 */
SwitchConfig loadSwitchConfig(const std::string& path);