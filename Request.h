#pragma once
#include "IPAddress.h"

// defining request struct
struct Request {
    IPAddress in;
    IPAddress out;
    int time; // number of clock cycles to process the request
    char job; // either "P" or "S"

    // constructors
    Request();
    Request(IPAddress& in, IPAddress& out, int time, char job);
};