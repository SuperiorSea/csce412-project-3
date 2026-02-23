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

        // returns the address as an unsigned int
        unsigned int get_value();

        // comparison operators
        bool operator<(const IPAddress& other) const;
        bool operator<=(const IPAddress& other) const;
        bool operator>(const IPAddress& other) const;
        bool operator>=(const IPAddress& other) const;
        bool operator==(const IPAddress& other) const;
        bool operator!=(const IPAddress& other) const;
};