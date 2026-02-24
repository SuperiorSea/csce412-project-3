#pragma once
#include "Request.h"

class WebServer {
    private:
        int id;
        int busy_until; // clock cycle where server will be free
        Request current_request;
        bool has_current;
    public:
        // constructor
        explicit WebServer(int id);

        // getters
        int getId() const;
        int getBusyUntil() const;

        // checkers
        bool isBusy(int current_cycle) const;
        bool hasRequest() const;

        // assign a request
        void assignRequest(Request& request, int current_cycle);
};