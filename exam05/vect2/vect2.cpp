#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}

vect2::vect2(int first, int second) : x(first), y(second) {}
vect2::vect2(const vect2 &other) : x(other.x), y(other.y) {}
vect2::~vect2() {}

vect2 &vect2::operator=(const vect2 &src)
{
	if (this != &src)
	{
		x = src.x;
		y = src.y;
	}
	return (*this);
}

int vect2::operator[](const int index) const
{
	if (index == 0)
		return (x);
	else
		return (y);
}

int& vect2::operator[](const int index)
{
	if (index == 0)
		return (x);
	else
		return (y);
}

vect2 vect2::operator*(const int num) const
{
	vect2 tmp(*this);

	tmp.x *= num;
	tmp.y *= num;
	return (tmp);
}

vect2& vect2::operator*(const int num)
{
	x *= num;
	y *= num;
	return (*this);
}

vect2& vect2::operator*=(const int num)
{
	x *= num;
	y *= num;
	return (*this);
}

vect2 vect2::operator+(const vect2 vec) const
{
	vect2 tmp(*this);

	tmp.x += vec.x;
	tmp.y += vec.y;
	return (tmp);
}

vect2 vect2::operator-(const vect2 vec) const
{
	vect2 tmp(*this);

	tmp.x -= vec.x;
	tmp.y -= vec.y;
	return (tmp);
}
vect2 vect2::operator*(const vect2 vec) const
{
	vect2 tmp(*this);

	tmp.x *= vec.x;
	tmp.y *= vec.y;
	return (tmp);
}

vect2& vect2::operator+=(const vect2 vec)
{
	x += vec.x;
	y += vec.y;
	return (*this);
}

vect2& vect2::operator-=(const vect2 vec)
{
	x -= vec.x;
	y -= vec.y;
	return (*this);
}

vect2& vect2::operator*=(const vect2 vec)
{
	x *= vec.x;
	y *= vec.y;
	return (*this);
}

vect2& vect2::operator++()
{
	vect2 one(1, 1);
	*this += one;
	return (*this);
}

vect2 vect2::operator++(int)
{
	vect2 tmp(*this);

	++(*this);
	return (tmp);
}

vect2& vect2::operator--()
{
	vect2 one(1, 1);
	*this -= one;
	return (*this);
}

vect2 vect2::operator--(int)
{
	vect2 tmp(*this);

	--(*this);
	return (tmp);
}

bool vect2::operator==(const vect2 vec) const
{
	if (x != vec.x || y != vec.y)
		return (false);
	else
		return (true);
}
bool vect2::operator!=(const vect2 vec) const
{
	return (!((*this) == vec));
}

std::ostream &operator<<(std::ostream &stream, const vect2 &vec)
{
	stream << "{" << vec[0] << ", " << vec[1] << "}";
	return (stream);
}

vect2 vect2::operator-() const
{
	vect2 tmp(*this);
	tmp *= -1;
	return (tmp);
}

vect2 operator*(const int num, const vect2 vec)
{
	vect2 tmp(vec);

	tmp *= num;
	return (tmp);
}
