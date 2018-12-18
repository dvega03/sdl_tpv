#include "Wall.h"

using namespace std;


void Wall::loadFromFile(ifstream& levelFile)
{
	int x = 0, y = 0;

	levelFile >> x;
	levelFile >> y;
	levelFile >> _width;
	levelFile >> _heigth;

	_position = Vector2D{ (double)x,(double)y};
}

void Wall::saveToFile(std::ofstream& file)
{
	file << _position.getX() << " " << _position.getY() << " " << _width << " " << _heigth << endl;
}


void Wall::render()
{
	ArkanoidObject::render();
}

bool Wall::handleCollision(SDL_Rect*& ballRect, Vector2D& ballVel, Vector2D& collVector, int windowWidth)
{

	wallRectPointer = &wallRect;

	SDL_Rect result;
	resultPunt = &result;

	
	if (SDL_IntersectRect(ballRect, wallRectPointer, resultPunt))
	{
		if (resultPunt->w > resultPunt->h) 
		{ 
			collVector = { 0, 1 };
			return true;
		}
		else
		{
			if (_position.getX() < (windowWidth / 2))
			{
				collVector = { 1,0 };
				return true;
			}
			else 
			{ 
				collVector = { -1,0 };
				return true;
			}
		}
	}

	return false;

}

void Wall::update() {}

void Wall::handleEvent() {}


Wall::~Wall()
{
}
