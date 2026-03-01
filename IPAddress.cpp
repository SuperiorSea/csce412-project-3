/**
 * @file IPAddress.cpp
 * @brief Implementation of the IPAddress class and related functionality.
 *
 * Provides definitions for constructors, comparison operators, and
 * conversion utilities declared in IPAddress.h.
 *
 * This file handles:
 * - Conversion between dotted-decimal string format and 32-bit integer format
 * - Comparison operations between IP addresses
 * - Retrieval of numeric and string representations
 *
 * Part of the load balancer simulation project.
 */

#include "IPAddress.h"
#include <sstream>
#include <stdexcept>

/**
 * @brief Default constructor implementation.
 */
IPAddress::IPAddress() : address(0) {}

/**
 * @brief Constructs IPAddress from unsigned integer.
 * @param addr 32-bit integer representing IPv4 address.
 */
IPAddress::IPAddress(unsigned int addr) : address(addr) {}

/**
 * @brief Constructs IPAddress from dotted-decimal string.
 *
 * Validates:
 * - Proper dot placement
 * - Each octet is between 0 and 255
 *
 * @param addr String representation of IPv4 address.
 * @throws std::invalid_argument if format or value is invalid.
 */
IPAddress::IPAddress(std::string addr) {

    unsigned int result = 0;

    std::istringstream input(addr);
    int a, b, c, d;
    char dot1, dot2, dot3;

    // Parse and validate structure
    if (!(input >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d)) {
        throw std::invalid_argument("Invalid IP address format");
    }

    if (dot1 != '.' || dot2 != '.' || dot3 != '.') {
        throw std::invalid_argument("Invalid IP address format");
    }

    if (a < 0 || a > 255 ||
        b < 0 || b > 255 ||
        c < 0 || c > 255 ||
        d < 0 || d > 255) {
        throw std::invalid_argument("Invalid IP address value");
    }

    // Combine octets into 32-bit integer
    result = (a << 24) | (b << 16) | (c << 8) | d;
    address = result;
}

/**
 * @brief Returns integer representation of the IP address.
 */
unsigned int IPAddress::getValue() const {
    return address;
}

/**
 * @brief Converts stored integer to dotted-decimal format.
 */
std::string IPAddress::getString() const {
    unsigned int a = (address >> 24) & 0xFF;
    unsigned int b = (address >> 16) & 0xFF;
    unsigned int c = (address >> 8) & 0xFF;
    unsigned int d = address & 0xFF;

    std::ostringstream oss;
    oss << a << '.' << b << '.' << c << '.' << d;
    return oss.str();
}

/**
 * @brief Less-than comparison.
 */
bool IPAddress::operator<(const IPAddress& other) const {
    return address < other.address;
}

/**
 * @brief Less-than-or-equal comparison.
 */
bool IPAddress::operator<=(const IPAddress& other) const {
    return address <= other.address;
}

/**
 * @brief Greater-than comparison.
 */
bool IPAddress::operator>(const IPAddress& other) const {
    return address > other.address;
}

/**
 * @brief Greater-than-or-equal comparison.
 */
bool IPAddress::operator>=(const IPAddress& other) const {
    return address >= other.address;
}

/**
 * @brief Equality comparison.
 */
bool IPAddress::operator==(const IPAddress& other) const {
    return address == other.address;
}

/**
 * @brief Inequality comparison.
 */
bool IPAddress::operator!=(const IPAddress& other) const {
    return address != other.address;
}