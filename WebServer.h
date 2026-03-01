/**
 * @file WebServer.h
 * @brief Defines the WebServer class used in the load balancer simulation.
 *
 * A WebServer represents an individual server instance that processes
 * incoming requests. It tracks its busy state and the clock cycle
 * at which it will become available.
 */

#pragma once
#include "Request.h"

/**
 * @class WebServer
 * @brief Represents a simulated web server handling requests.
 *
 * Each WebServer:
 * - Has a unique identifier
 * - Processes one request at a time
 * - Tracks when it will become available
 * - Maintains its current assigned request
 */
class WebServer {
private:

    /**
     * @brief Unique identifier for the server.
     */
    int id;

    /**
     * @brief Clock cycle when the server will finish processing
     * the current request and become free.
     */
    int busy_until;

    /**
     * @brief Currently assigned request.
     */
    Request current_request;

    /**
     * @brief Indicates whether the server currently has a request.
     */
    bool has_current;

public:

    /**
     * @brief Constructs a WebServer with a given ID.
     *
     * @param id Unique identifier for the server.
     */
    explicit WebServer(int id);

    /**
     * @brief Returns the server's ID.
     *
     * @return Server identifier.
     */
    int getId() const;

    /**
     * @brief Returns the clock cycle when the server becomes free.
     *
     * @return Busy-until clock cycle.
     */
    int getBusyUntil() const;

    /**
     * @brief Determines if the server is currently busy.
     *
     * @param current_cycle Current simulation clock cycle.
     * @return True if still processing a request.
     */
    bool isBusy(int current_cycle) const;

    /**
     * @brief Checks whether the server has a request assigned.
     *
     * @return True if a request is currently assigned.
     */
    bool hasRequest() const;

    /**
     * @brief Assigns a request to the server.
     *
     * Updates the server’s busy time based on the request's
     * processing time.
     *
     * @param request Request to assign.
     * @param current_cycle Current simulation clock cycle.
     */
    void assignRequest(Request& request, int current_cycle);
};