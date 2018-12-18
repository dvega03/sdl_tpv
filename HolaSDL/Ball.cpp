#include "Ball.h"
#include "Game.h"


void Ball::loadFromFile(ifstream& levelFile)
{
	MovingObject::loadFromFile(levelFile);
}
  
void Ball::saveToFile(ofstream& file)
{
	MovingObject::saveToFile(file);
}

void Ball::render()
{
	MovingObject::render();
}

void Ball::update()
{
	MovingObject::update();
	Vector2D collVector;

	if (_game->collides(ArkanoidObject::getRect(), _direction, collVector))
	{
		_direction = _direction - (collVector * (_direction * 2 * collVector));
		MovingObject::update();
	}
}

void Ball::setIni()
{
	_position = _posIni;
	_direction = _dirIni;
}

Ball::~Ball()
{
}
