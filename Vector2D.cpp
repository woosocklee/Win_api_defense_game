#include "pch.h"
#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D()
{
	this->x = 0;
	this->y = 0;
}

Vector2D::Vector2D(double x, double y)
{
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D(const Vector2D& vec)
{
	*this = vec;
}

Vector2D Vector2D::operator+(const Vector2D& otherV) const
{
	return Vector2D(this->x + otherV.x, this->y + otherV.y);
}

Vector2D Vector2D::operator-(const Vector2D& otherV) const
{
	return Vector2D(this->x - otherV.x, this->y - otherV.y);
}

double Vector2D::dot(const Vector2D& rhs)
{
	return this->x * rhs.x + this->y * rhs.y;
}

double Vector2D::cross(const Vector2D& rhs)
{
	return this->x * rhs.y - this->y * rhs.x;
}

Vector2D Vector2D::operator*(double n)
{
	this->x *= n;
	this->y *= n;
	return *this;
}

Vector2D Vector2D::operator/(double n)
{
	this->x /= n;
	this->y /= n;

	return *this;
}

Vector2D& Vector2D::operator=(const Vector2D& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

Vector2D Vector2D::rotate(double radian)
{
	this->x = this->x * cos(radian);
	this->y = this->y * sin(radian);
	return *this;
}

Vector2D Vector2D::rotate(const Vector2D& axis, double radian)
{
	Vector2D tempvec = { *this - axis };
	tempvec.rotate(radian);
	this->x = axis.x + tempvec.x;
	this->y = axis.y + tempvec.y;
	return *this;
}

Vector2D Vector2D::normalize()
{
	double thislen = this->getlength();
	Vector2D tempvec = Vector2D(this->x / thislen, this->y/thislen);

	return tempvec;
}

double Vector2D::getlength()
{
	return sqrt(this->getlengthsq());
}

double Vector2D::getlengthsq()
{
	return (this->x * this->x) + (this->y * this->y);
}

