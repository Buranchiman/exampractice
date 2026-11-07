#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

class bigint
{
    private:
        std::string _number;
    public:
        bigint();
        bigint(unsigned int num);
        bigint(const bigint& other);
        bigint& operator=(const bigint& other);
        ~bigint();

        std::string getStr() const;
        std::string& accesStr();
        bigint operator+(const bigint add) const;
        bigint& operator+=(const bigint add);

        bigint& operator++();
        bigint operator++(int);

        bigint operator<<(unsigned int shift) const;
        bigint operator>>(unsigned int shift) const;
        
        bigint& operator<<=(unsigned int shift);
        bigint& operator>>=(unsigned int shift);

        bigint operator<<(const bigint shift) const;
        bigint operator>>(const bigint shift) const;
        
        bigint& operator<<=(const bigint shift);
        bigint& operator>>=(const bigint shift);

        bool operator==(const bigint other) const;
        bool operator!=(const bigint other) const;
        bool operator<(const bigint other) const;
        bool operator>(const bigint other) const;
        bool operator<=(const bigint other) const;
        bool operator>=(const bigint other) const;
};

std::ostream& operator<<(std::ostream &stream, const bigint &bigint);