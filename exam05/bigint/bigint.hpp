#ifndef BIGINT
#define BIGINT

#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>

class bigint
{
	private:
		std::string number;
	public:
		bigint();
		bigint(unsigned int num);
		bigint(const bigint& source);

		std::string &accessStr();
		std::string getStr() const;
		bigint& operator=(const bigint& source);
		bigint operator+(const bigint&source) const;
		bigint& operator+=(const bigint &source);
		bigint& operator++();
		bigint operator++(int);

		bigint operator<<(unsigned int n) const;
		bigint operator>>(unsigned int n) const;
		bigint& operator<<=(unsigned int n) ;
		bigint& operator>>=(unsigned int n) ;

		bigint operator<<(const bigint& other) const;
		bigint operator>>(const bigint& other) const;
		bigint& operator<<=(const bigint& other) ;
		bigint& operator>>=(const bigint& other) ;

		bool operator==(const bigint& other) const;
		bool operator!=(const bigint& other) const;
		bool operator>(const bigint& other) const;
		bool operator<(const bigint& other) const;
		bool operator>=(const bigint& other) const;
		bool operator<=(const bigint& other) const;
};

std::ostream& operator<<(std::ostream& output, const bigint& obj);

#endif
