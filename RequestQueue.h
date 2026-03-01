/**
 * @file RequestQueue.h
 * @brief Wrapper class around std::queue for handling Request objects.
 *
 * This class encapsulates a standard FIFO queue of Request objects.
 * It allows for future extension (e.g., logging, metrics, priority handling)
 * without modifying the rest of the system.
 */

#pragma once
#include "Request.h"
#include <cstddef>
#include <queue>

/**
 * @class RequestQueue
 * @brief FIFO queue abstraction for managing incoming requests.
 *
 * Internally uses std::queue<Request> to store and manage requests.
 * Designed as a wrapper to allow additional functionality later
 * (e.g., monitoring queue length, filtering, statistics collection).
 */
class RequestQueue {
private:

    /**
     * @brief Underlying STL queue storing Request objects.
     */
    std::queue<Request> queue;

public:

    /**
     * @brief Adds a request to the back of the queue.
     *
     * @param request Request object to be added.
     */
    void push(Request& request);

    /**
     * @brief Removes the request at the front of the queue.
     *
     * Behavior is undefined if the queue is empty.
     */
    void pop();

    /**
     * @brief Returns a reference to the front request.
     *
     * @return Reference to the first Request in the queue.
     * @warning Calling this on an empty queue results in undefined behavior.
     */
    Request& front();

    /**
     * @brief Checks whether the queue is empty.
     *
     * @return True if empty, false otherwise.
     */
    bool empty();

    /**
     * @brief Returns the number of requests currently in the queue.
     *
     * @return Size of the queue.
     */
    std::size_t size();
};