#pragma once
#include <string>

class IPAddress {
    private:
        // store the ip address as an unsigned int
        unsigned int address;

    public:
        // default constructor
        IPAddress();

        // constructor that takes int
        IPAddress(unsigned int addr);

        // create IP address from string
        IPAddress(std::string addr);

        // getters
        unsigned int getValue();
        std::string getString();

        // comparison operators
        bool operator<(const IPAddress& other) const;
        bool operator<=(const IPAddress& other) const;
        bool operator>(const IPAddress& other) const;
        bool operator>=(const IPAddress& other) const;
        bool operator==(const IPAddress& other) const;
        bool operator!=(const IPAddress& other) const;
};