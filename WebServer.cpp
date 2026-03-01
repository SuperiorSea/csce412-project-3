/**
 * @file WebServer.cpp
 * @brief Implementation of the WebServer class.
 */

#include "WebServer.h"

/**
 * @brief Constructor implementation.
 *
 * Initializes:
 * - busy_until to 0 (available immediately)
 * - current_request to default
 * - has_current to false
 *
 * @param id Unique identifier for this server.
 */
WebServer::WebServer(int id)
 : id(id), busy_until(0), current_request(), has_current(false) {}

/**
 * @brief Returns server ID.
 */
int WebServer::getId() const {
    return id;
}

/**
 * @brief Returns the cycle when the server becomes free.
 */
int WebServer::getBusyUntil() const {
    return busy_until;
}

/**
 * @brief Determines whether the server is currently busy.
 *
 * @param current_cycle Current simulation clock cycle.
 * @return True if current_cycle is less than busy_until.
 */
bool WebServer::isBusy(int current_cycle) const {
    return current_cycle < busy_until;
}

/**
 * @brief Checks whether the server has an assigned request.
 *
 * @return True if a request is currently assigned.
 */
bool WebServer::hasRequest() const {
    return has_current;
}

/**
 * @brief Assigns a request to this server.
 *
 * Sets:
 * - current_request
 * - busy_until based on processing time
 * - has_current flag
 *
 * @param request Request to process.
 * @param current_cycle Current simulation clock cycle.
 */
void WebServer::assignRequest(Request& request, int current_cycle) {
    current_request = request;
    busy_until = current_cycle + request.time;
    has_current = true;
}