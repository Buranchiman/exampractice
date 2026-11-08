#include "bigint.hpp"

bigint::bigint()
{
	this->number = "0";
}

bigint::bigint(unsigned int num)
{
	std::stringstream ss;
	ss << num;
	this->number = ss.str();
}

bigint::bigint(const bigint& source)
{
	*this = source;
}

std::string& bigint::accessStr()
{
	return (number);
}

std::string bigint::getStr() const
{
	return (number);
}

bigint& bigint::operator=(const bigint& source)
{
	if (this == &source)
		return (*this) ;
	this->number = source.number;
	return (*this);
}

std::string reverse(std::string target)
{
	std::string res;
	unsigned int len = target.length();

	while (len > 0)
	{
		res.push_back(target[len -1]);
		len--;
	}
	return (res);
}

std::string addition (std::string str1, std::string str2)
{
	std::string nbr1 = reverse(str1);
	std::string nbr2 = reverse(str2);
	unsigned int len1 = nbr1.length();
	unsigned int len2 = nbr2.length();

	if (len1 > len2)
	{
		unsigned int diff = len1 - len2;

		for (int i =0; i < diff; i++)
			nbr2.push_back('0');
	}
	else
	{
		unsigned int diff = len2 - len1;

		for (int i =0; i < diff; i++)
			nbr1.push_back('0');
	}
	//std::cout << "a is " << nbr1 << " and b is " << nbr2 << std::endl;
	unsigned int len = nbr1.length();
	std::string result;
	int digit1;
	int digit2;
	int over = 0;
	for (int i = 0; i < len; i++)
	{
		digit1 = nbr1[i] - '0';
		digit2 = nbr2[i] - '0';
		int res = digit1 + digit2 + over;
		//std::cout << "digit 1:" << digit1 << " digit2: " << digit2 << " and res is " << res << std::endl;
		over = 0;
		if (res > 9)
		{
			result.push_back('0' + (res % 10));
			over = 1;
		}
		else
			result.push_back(res + '0');
	}
	if (over != 0)
		result.push_back(over + '0');
	return (reverse(result));
}

bigint bigint::operator+(const bigint&source) const
{
	bigint tmp(source);

	std::string res = addition(this->getStr(), source.getStr());
	tmp.accessStr() = res;
	return (tmp);
}

bigint& bigint::operator+=(const bigint &source)
{
	(*this) = (*this) + source;
	return *this;
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
	return(tmp);
}
bigint bigint::operator<<(unsigned int n) const
{
	bigint tmp = *this;
	std::string& tmpStr = tmp.accessStr();

	tmpStr.insert(tmpStr.end(), n, '0');
	//std::cout << "number after shift is" << tmp.getStr() << std::endl;
	return (tmp);
}

bigint bigint::operator>>(unsigned int n) const
{
	bigint tmp = *this;
	std::string& tmpStr = tmp.accessStr();
	unsigned int len = tmpStr.length();
	if (n >= len)
		tmpStr = "0";
	else
		tmpStr.erase(len - n, n);
	return (tmp);
}

bigint& bigint::operator>>=(unsigned int n)
{
	*this = (*this) >> n;
	return *this;
}

bigint& bigint::operator<<=(unsigned int n)
{
	*this = (*this) << n;
	return *this;
}

unsigned int stringtoUInt(std::string str)
{
	std::stringstream ss(str);
	unsigned int res;
	ss >> res;
	return (res);
}

bigint bigint::operator<<(const bigint& other) const
{
	bigint tmp(*this);
	unsigned int n = stringtoUInt(other.getStr());

	tmp <<= n;
	return (tmp);
}

bigint bigint::operator>>(const bigint& other) const
{
	bigint tmp(*this);
	unsigned int n = stringtoUInt(other.getStr());

	tmp >>= n;
	return (tmp);
}

bigint& bigint::operator<<=(const bigint& other)
{
	unsigned int n = stringtoUInt(other.getStr());

	*this <<= n;
	return (*this);
}

bigint& bigint::operator>>=(const bigint& other)
{
	unsigned int n = stringtoUInt(other.getStr());

	*this >>= n;
	return (*this);
}

bool bigint::operator==(const bigint& other) const
{
	if (this->getStr() == other.getStr())
		return (true);
	else
		return (false);
}

bool bigint::operator!=(const bigint& other) const
{
	return (!((*this) == other));
}

bool bigint::operator<(const bigint& other) const
{
	std::string str1 = this->getStr();
	std::string str2 = other.getStr();
	size_t len1 = str1.length();
	size_t len2 = str2.length();

	if (!len1 != len2)
		return (len1 < len2);
	return (this->getStr() < other.getStr());
}

bool bigint::operator>(const bigint& other) const
{
	return (!((*this) < other));
}

bool bigint::operator<=(const bigint& other) const
{
	return (*this < other || *this == other);
}

bool bigint::operator>=(const bigint& other) const
{
	return (*this > other || *this == other);
}

std::ostream& operator<<(std::ostream& output, const bigint& obj)
{
	output << obj.getStr();
	return(output);
}
