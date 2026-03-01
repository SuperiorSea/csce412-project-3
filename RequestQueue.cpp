/**
 * @file RequestQueue.cpp
 * @brief Implementation of the RequestQueue wrapper class.
 */

#include "RequestQueue.h"

/**
 * @brief Pushes a request onto the queue.
 *
 * @param request Request to enqueue.
 */
void RequestQueue::push(Request& request) {
    queue.push(request);
}

/**
 * @brief Removes the front request from the queue.
 */
void RequestQueue::pop() {
    queue.pop();
}

/**
 * @brief Returns the request at the front of the queue.
 *
 * @return Reference to front Request.
 */
Request& RequestQueue::front() {
    return queue.front();
}

/**
 * @brief Checks whether the queue is empty.
 *
 * @return True if no requests are stored.
 */
bool RequestQueue::empty() {
    return queue.empty();
}

/**
 * @brief Returns the number of stored requests.
 *
 * @return Current queue size.
 */
std::size_t RequestQueue::size() {
    return queue.size();
}