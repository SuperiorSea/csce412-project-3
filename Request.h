/**
 * @file Request.h
 * @brief Defines the Request structure used in the load balancer simulation.
 *
 * A Request represents a simulated web request containing:
 * - Source IP address
 * - Destination IP address
 * - Processing time (in clock cycles)
 * - Job type (Processing or Streaming)
 */

#pragma once
#include "IPAddress.h"

/**
 * @struct Request
 * @brief Represents a single web request handled by the load balancer.
 *
 * This struct models a request flowing through the system.
 * It includes identifying IP information, required processing time,
 * and the job classification.
 */
struct Request {

    /**
     * @brief Source IP address of the request.
     */
    IPAddress in;

    /**
     * @brief Destination IP address of the request.
     */
    IPAddress out;

    /**
     * @brief Number of clock cycles required to process the request.
     */
    int time;

    /**
     * @brief Job type identifier.
     *
     * 'P' = Processing workload  
     * 'S' = Streaming workload
     */
    char job;

    /**
     * @brief Default constructor.
     *
     * Initializes:
     * - in and out to default IPAddress (0.0.0.0)
     * - time to 0
     * - job type to 'P'
     */
    Request();

    /**
     * @brief Parameterized constructor.
     *
     * @param in Source IP address
     * @param out Destination IP address
     * @param time Number of clock cycles required
     * @param job Job type ('P' or 'S')
     */
    Request(IPAddress& in, IPAddress& out, int time, char job);
};