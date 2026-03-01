#pragma once
#include <string>

/**
 * @class IPAddress
 * @brief Represents an IPv4 address.
 *
 * Stores an IPv4 address internally as a 32-bit unsigned integer.
 * Provides constructors for integer and string representations,
 * along with comparison operators and conversion utilities.
 */
class IPAddress {
private:
    /**
     * @brief 32-bit representation of the IPv4 address.
     *
     * Stored in network byte order:
     * a.b.c.d → (a << 24) | (b << 16) | (c << 8) | d
     */
    unsigned int address;

public:
    /**
     * @brief Default constructor.
     *
     * Initializes the IP address to 0.0.0.0.
     */
    IPAddress();

    /**
     * @brief Constructs an IPAddress from a 32-bit integer.
     * @param addr Unsigned integer representation of the IP address.
     */
    IPAddress(unsigned int addr);

    /**
     * @brief Constructs an IPAddress from a dotted-decimal string.
     *
     * Example format: "192.168.1.1"
     *
     * @param addr String representation of IPv4 address.
     * @throws std::invalid_argument if format or values are invalid.
     */
    IPAddress(std::string addr);

    /**
     * @brief Returns the 32-bit integer representation of the IP address.
     * @return Unsigned integer value of the address.
     */
    unsigned int getValue() const;

    /**
     * @brief Returns the dotted-decimal string representation.
     * @return String formatted as "a.b.c.d".
     */
    std::string getString() const;

    /** @name Comparison Operators */
    ///@{

    /**
     * @brief Less-than comparison operator.
     */
    bool operator<(const IPAddress& other) const;

    /**
     * @brief Less-than-or-equal comparison operator.
     */
    bool operator<=(const IPAddress& other) const;

    /**
     * @brief Greater-than comparison operator.
     */
    bool operator>(const IPAddress& other) const;

    /**
     * @brief Greater-than-or-equal comparison operator.
     */
    bool operator>=(const IPAddress& other) const;

    /**
     * @brief Equality comparison operator.
     */
    bool operator==(const IPAddress& other) const;

    /**
     * @brief Inequality comparison operator.
     */
    bool operator!=(const IPAddress& other) const;

    ///@}
};

/**
 * @struct IPRange
 * @brief Represents a blocked or monitored range of IP addresses.
 *
 * Defines a range between a lower and upper IP address (inclusive).
 */
struct IPRange {

    /**
     * @brief Lower bound of the IP range.
     */
    IPAddress low;

    /**
     * @brief Upper bound of the IP range.
     */
    IPAddress high;

    /**
     * @brief Constructs an IP range.
     *
     * @param l Lower IP address.
     * @param h Upper IP address.
     */
    IPRange(IPAddress& l, IPAddress& h) : low(l), high(h) {}
};