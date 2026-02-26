/**
 * @file IPAddress.h
 * @brief Simple IPv4 address representation stored as 32‑bit integer.
 *
 * Provides conversion from string, comparison operators, and accessors.
 */
#pragma once
#include <string>

/**
 * @class IPAddress
 * @brief Encapsulates an IPv4 address in host byte order.
 */
class IPAddress {
    private:
        // store the ip address as an unsigned int
        unsigned int address;

    public:
        /**
         * @brief Default constructed address (0.0.0.0).
         */
        IPAddress();

        /**
         * @brief Construct from a 32‑bit integer.
         * @param addr value in host byte order
         */
        IPAddress(unsigned int addr);

        /**
         * @brief Parse dotted‑decimal string to address.
         * @param addr string such as "192.168.0.1"
         * @throws std::invalid_argument on bad format/value
         */
        IPAddress(std::string addr);

        /**
         * @brief Get raw 32‑bit value of address.
         * @return integer representation
         */
        unsigned int getValue() const;

        /**
         * @brief Convert address to dotted‑decimal string.
         * @return string like "a.b.c.d"
         */
        std::string getString() const;

        /** comparison operators */
        bool operator<(const IPAddress& other) const;
        bool operator<=(const IPAddress& other) const;
        bool operator>(const IPAddress& other) const;
        bool operator>=(const IPAddress& other) const;
        bool operator==(const IPAddress& other) const;
        bool operator!=(const IPAddress& other) const;
};

/**
 * @struct IPRange
 * @brief Inclusive range of IPv4 addresses used for blocking.
 */
struct IPRange {
    IPAddress low;   /**< lower bound */
    IPAddress high;  /**< upper bound */

    IPRange(const IPAddress& l, const IPAddress& h) : low(l), high(h) {}
};

// IP range blocker
struct IPRange {
    IPAddress low;
    IPAddress high;

    IPRange(IPAddress& l, IPAddress& h) : low(l), high(h) {}
};
