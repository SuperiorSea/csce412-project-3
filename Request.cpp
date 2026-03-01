/**
 * @file Request.cpp
 * @brief Implementation of the Request structure constructors.
 */

#include "Request.h"

/**
 * @brief Default constructor implementation.
 *
 * Initializes the request with:
 * - Default source and destination IPs
 * - Processing time of 0
 * - Default job type 'P'
 */
Request::Request()
 : in(), out(), time(0), job('P') {}

/**
 * @brief Parameterized constructor implementation.
 *
 * @param in Source IP address
 * @param out Destination IP address
 * @param time Processing time in clock cycles
 * @param job Job type ('P' for processing, 'S' for streaming)
 */
Request::Request(IPAddress& in, IPAddress& out, int time, char job)
 : in(in), out(out), time(time), job(job) {}