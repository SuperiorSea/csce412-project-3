#pragma once
#include "Request.h"
#include <cstddef>
#include <queue>

// just a queue wrapper class if want to add additional functionality later
class RequestQueue {
    private:
        std::queue<Request> queue;
    public:
        void push(Request& request);
        void pop();
        Request& front();
        bool empty();
        std::size_t size();
};