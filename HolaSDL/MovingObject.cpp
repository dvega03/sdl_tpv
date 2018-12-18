#include "MovingObject.h"



MovingObject::MovingObject()
{
	_direction = Vector2D{0,0};
}

void MovingObject::loadFromFile(ifstream& levelFile)
{
	double x, y, dirX, dirY;

	levelFile >> x;
	levelFile >> y;
	levelFile >> _width;
	levelFile >> _heigth;
	levelFile >> dirX;
	levelFile >> dirY;

	_position = Vector2D{ (double)x,(double)y };
	_direction = Vector2D{ (double)dirX, (double)dirY };
}

void MovingObject::saveToFile(std::ofstream& file)
{
	file << _position.getX() << " " << _position.getY() << " " << _width << " " << _heigth << " " << _direction.getX() << " " << _direction.getY() << endl;
}


void MovingObject::render()
{
	ArkanoidObject::render();
}

void MovingObject::update()
{
	_position = _direction + _position;
}

void MovingObject::handleEvent()
{

}

MovingObject::~MovingObject()
{
}
