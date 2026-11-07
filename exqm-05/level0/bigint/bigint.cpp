#include "bigint.hpp"

bigint::bigint() : _number("0") {}
bigint::bigint(unsigned int num)
{
    std::stringstream ss;

    ss << num;
    _number = ss.str();
}
bigint::bigint(const bigint& other) : _number(other._number) {}

bigint& bigint::operator=(const bigint& other)
{
    if (this != &other)
        this->_number = other._number;
    return (*this);
}

std::string reverse(const std::string str)
{
    std::string tmp;
    for (size_t len = str.length(); len > 0; len--)
    { 
        tmp.push_back(str[len - 1]);
    }
    return (tmp);
}

std::string bigint::getStr() const
{
    return (_number);
}

std::string& bigint::accesStr()
{
    return (_number);
}

std::string addition(const std::string nb1, const std::string nb2)
{
    std::string rev1 = reverse(nb1);
    std::string rev2 = reverse(nb2);
    size_t len1 = rev1.length();
    size_t len2 = rev2.length();

    if (len1 > len2)
    {
        for (size_t diff = len1 - len2; diff > 0;diff--)
            rev2.push_back('0'); 
    }
    else if (len1 < len2)
    {
        for (size_t diff = len2 - len1; diff > 0;diff--)
            rev1.push_back('0'); 
    }
    std::string res;
    unsigned int carry = 0;
    size_t len_max = rev1.length();
    unsigned int digit1;
    unsigned int digit2;
    unsigned int tmp = 0;
    //std::cout << "rev1 after fill is " << rev1 << " rev2 is " << rev2 <<std::endl;
    for (size_t i = 0; i < len_max; i++)
    {
        digit1 = rev1[i] - '0';
        digit2 = rev2[i] - '0';
        tmp = digit1 + digit2 + carry;
        //std::cout << "before addition d1=" << digit1 << " d2=" << digit2 << " and res is " << tmp << std::endl;
        carry = 0;
        if (tmp > 9)
        {
            carry = 1;
            res.push_back((tmp % 10) + '0');
        }
        else
            res.push_back(tmp + '0');
    }
    if (carry != 0)
        res.push_back(carry + '0');
    return (reverse(res));
}

bigint bigint::operator+(const bigint add) const
{
    bigint tmp;

    tmp._number = addition(_number, add._number);
    return (tmp);
}

bigint& bigint::operator+=(const bigint add)
{
    _number = addition(_number, add._number);
    return (*this);
}

bigint& bigint::operator++()
{
    *this += bigint(1);
    return (*this);
}
bigint bigint::operator++(int)
{
    bigint tmp(*this);
    ++(*this);
    return (tmp);
}

bigint bigint::operator<<(unsigned int shift) const
{
    bigint tmp(*this);
    std::string &str =tmp._number;
    if (_number == "0")
        return (*this);
    for (unsigned int i = 0; i <shift; i++)
    {
        str.insert(str.end(), '0');
    }
    return (tmp);
}

bigint bigint::operator>>(unsigned int shift) const
{
    bigint tmp(*this);
    std::string &str =tmp._number;
    size_t len = str.length();

    if (shift >= len)
        str = "0";
    else
        str.erase(len - shift, shift);
    return (tmp);
}

bigint& bigint::operator<<=(unsigned int shift)
{
    (*this) = (*this) << shift;
    return (*this);
}

bigint& bigint::operator>>=(unsigned int shift)
{
    (*this) = (*this) >> shift;
    return (*this);
}

unsigned int bigintToUint(const bigint &big)
{
    std::stringstream ss(big.getStr());
    unsigned int res;
    ss >> res;
    return (res);
}

bigint bigint::operator<<(const bigint shift) const
{
    return ((*this) << bigintToUint(shift));
}

bigint bigint::operator>>(const bigint shift) const
{
    return ((*this) >> bigintToUint(shift));
}

bigint& bigint::operator<<=(const bigint shift)
{
    return ((*this) <<= bigintToUint(shift));
}

bigint& bigint::operator>>=(const bigint shift)
{
    return ((*this) >>= bigintToUint(shift));
}

bool bigint::operator==(const bigint other) const
{
    return (_number == other.getStr());
}

bool bigint::operator!=(const bigint other) const
{
    return (!((*this) == other));
}

bool bigint::operator<(const bigint other) const
{
    size_t len1 = _number.length();
    size_t len2 = other._number.length();

    if (len1 < len2)
        return (true);
    else if (len1 > len2)
        return (false);
    else
        return (_number < other.getStr());
}

bool bigint::operator>(const bigint other) const
{
    return (other < (*this));
}

bool bigint::operator<=(const bigint other) const
{
    return ((*this) == other || (*this) < other);
}

bool bigint::operator>=(const bigint other) const
{
    return ((*this) == other || (*this) > other);
}

std::ostream& operator<<(std::ostream &stream, const bigint &bigint)
{
    stream << bigint.getStr();
    return (stream);
}

bigint::~bigint() {}