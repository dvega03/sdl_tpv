#pragma once
class Vector2D
{

private:

	double _x;
	double _y;

public:
	Vector2D();
	Vector2D(double x, double y);

	double getX() const { return _x; };
	double getY() const { return _y; };

	Vector2D operator+(Vector2D& v);
	Vector2D operator-(Vector2D& v);
	double operator*(Vector2D& v);

	Vector2D operator*(double d);


	double length();

	Vector2D normalize();

	~Vector2D();
};

