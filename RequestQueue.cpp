#include "RequestQueue.h"

void RequestQueue::push(Request& request) {
    queue.push(request);
}

void RequestQueue::pop() {
    queue.pop();
}

Request& RequestQueue::front() {
    return queue.front();
}

bool RequestQueue::empty() {
    return queue.empty();
}

std::size_t RequestQueue::size() {
    return queue.size();
}