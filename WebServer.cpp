#include "WebServer.h"

// constructor
WebServer::WebServer(int id)
 : id(id), busy_until(0), current_request(), has_current(false) {}

// getters
int WebServer::getId() const {
    return id;
}

int WebServer::getBusyUntil() const {
    return busy_until;
}

// checkers
bool WebServer::isBusy(int current_cycle) const {
    return current_cycle < busy_until;
}

bool WebServer::hasRequest() const {
    return has_current;
}

// assign a request
void WebServer::assignRequest(Request& request, int current_cycle) {
    current_request = request;
    busy_until = current_cycle + request.time;
    has_current = true;
}