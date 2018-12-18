#include "Vector2D.h"
#include <math.h>



Vector2D::Vector2D()
{
	_x = _y = 0;
}

Vector2D::Vector2D(double x, double y)
{
	_x = x;
	_y = y;
}

Vector2D Vector2D::operator+(Vector2D& v)
{
	return Vector2D{ _x + v.getX(), _y + v.getY() };
}

Vector2D Vector2D::operator-(Vector2D& v)
{
	return Vector2D{_x - v.getX(), _y - v.getY()};
}

double Vector2D::operator*(Vector2D& v)
{
	return _x * v.getX() + _y * v.getY();
}

Vector2D Vector2D::operator*(double d)
{
	return Vector2D{_x * d, _y * d};
}

double Vector2D::length()
{
	return sqrt(_x*_x + _y*_y);
}

Vector2D Vector2D::normalize()
{
	return Vector2D{_x/length(), _y/length()};
}


Vector2D::~Vector2D()
{
}
