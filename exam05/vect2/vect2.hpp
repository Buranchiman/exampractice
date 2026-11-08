#pragma once

#include <iostream>

class vect2
{
private:
	int x;
	int y;
public:
	vect2();
	vect2(int first, int second);
	vect2(const vect2 &other);
	vect2 &operator=(const vect2 &src);

	int operator[](const int index) const;
	int& operator[](const int index);
	vect2 operator-() const;

	vect2 operator*(const int num) const;
	vect2& operator*(const int num);
	vect2& operator*=(const int num);

	vect2 operator+(const vect2 vec) const;
	vect2 operator-(const vect2 vec) const;
	vect2 operator*(const vect2 vec) const;

	vect2& operator++();
	vect2 operator++(int);
	vect2& operator--();
	vect2 operator--(int);

	vect2& operator+=(const vect2 vec);
	vect2& operator-=(const vect2 vec);
	vect2& operator*=(const vect2 vec);

	bool operator==(const vect2 vec) const;
	bool operator!=(const vect2 vec) const;

	~vect2();
};

vect2 operator*(const int num, const vect2 vec);

std::ostream &operator<<(std::ostream &stream, const vect2 &vec);
