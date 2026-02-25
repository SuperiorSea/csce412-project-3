#include "Request.h"

// constructors
Request::Request()
 : in(), out(), time(0), job('P') {}

Request::Request(IPAddress& in, IPAddress& out, int time, char job)
 : in(in), out(out), time(time), job(job) {}