#include "IPAddress.h"
#include <sstream>
#include <stdexcept>

// constructors

IPAddress::IPAddress() : address(0) {}

IPAddress::IPAddress(unsigned int addr) : address(addr) {}

IPAddress::IPAddress(std::string addr) {

    // convert the string to an unsigned int
    unsigned int result = 0;

    // split the string by dots
    std::istringstream input(addr);
    int a, b, c, d;
    char dot1, dot2, dot3;

    // feed into the stream and validate
    if (!(input >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d)) {
        throw std::invalid_argument("Invalid IP address format");
    }
    if (dot1 != '.' || dot2 != '.' || dot3 != '.') {
        throw std::invalid_argument("Invalid IP address format");
    }
    if (a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255) {
        throw std::invalid_argument("Invalid IP address value");
    }

    // combine the four partial ints into the true value, and store it
    result = (a << 24) | (b << 16) | (c << 8) | d;
    address = result;
}

// methods

unsigned int IPAddress::get_value() {
    return address;
}

bool IPAddress::operator<(const IPAddress& other) const {
    return address < other.address;
}

bool IPAddress::operator<=(const IPAddress& other) const {
    return address <= other.address;
}

bool IPAddress::operator>(const IPAddress& other) const {
    return address > other.address;
}

bool IPAddress::operator>=(const IPAddress& other) const {
    return address >= other.address;
}

bool IPAddress::operator==(const IPAddress& other) const {
    return address == other.address;
}

bool IPAddress::operator!=(const IPAddress& other) const {
    return address != other.address;
}