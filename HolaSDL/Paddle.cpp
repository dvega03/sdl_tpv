#include "Paddle.h"

void Paddle::loadFromFile(ifstream& levelFile)
{
	int x, y, dirX, dirY;

	levelFile >> x;
	levelFile >> y;
	levelFile >> _width;
	levelFile >> _heigth;
	levelFile >> dirX;
	levelFile >> dirY;

	_position = Vector2D{ (double)x,(double)y };
	_direction = Vector2D{ (double)dirX, (double)dirY };
}

void Paddle::saveToFile(ofstream& level)
{
	level << _position.getX() << " " << _position.getY() << " " << _width << " " << _heigth << " " << _direction.getX() << " " << _direction.getY() << endl;
}




void Paddle::setIni()
{
	_position = _posIni;
	_direction = _direction;
}

void Paddle::changeWidth(float amount)
{
	_width = _width * amount;
}

void Paddle::render()
{
	MovingObject::render();
}

void Paddle::update()
{
	Vector2D provPosition = _direction + _position;;

	double point0 = provPosition.getX();
	double point1 = provPosition.getX() + _width;
	
	if (point0 > _limits && point1 < _windowWidth - _limits)
	{
		MovingObject::update();
	}
}

void Paddle::handleEvent(SDL_Event& event)
{

	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_LEFT) _direction = Vector2D{ -1,0 };
		else if (event.key.keysym.sym == SDLK_RIGHT) _direction = Vector2D{ 1,0 };
	}
	else if (event.type == SDL_KEYUP)
	{
		_direction = Vector2D{ 0,0 };
	}
}

bool Paddle::handleCollisions(SDL_Rect* ballRect, Vector2D& ballVel, Vector2D& collVector, int windowWidth)
{
	bool collisionState = false;

	//BallPoints
	Vector2D p0 = { static_cast<double>(ballRect->x), static_cast<double>(ballRect->y) }; // top-left
	Vector2D p1 = { static_cast<double>(ballRect->x) + static_cast<double>(ballRect->w), static_cast<double>(ballRect->y) }; // top-right
	Vector2D p2 = { static_cast<double>(ballRect->x), static_cast<double>(ballRect->y) + static_cast<double>(ballRect->h) }; // bottom-left
	Vector2D p3 = { static_cast<double>(ballRect->x) + static_cast<double>(ballRect->w), static_cast<double>(ballRect->y) + static_cast<double>(ballRect->h) }; // bottom-right
	//PaddlePoints
	Vector2D paddle_p0 = { _position.getX(), _position.getY() }; //top-left
	Vector2D paddle_p1 = { _position.getX() + _width / 5, _position.getY() }; //top-left + w/3
	Vector2D paddle_p2 = { _position.getX() + _width / 5 * 4, _position.getY() }; //top-left
	Vector2D paddle_p3 = { _position.getX() + _width, _position.getY() }; //top-right
	Vector2D paddle_p4 = { _position.getX() + _width, _position.getY() + _heigth };
	Vector2D paddle_p5 = { _position.getX(), _position.getY() + _heigth };

	SDL_Rect paddleRect;

	paddleRect.x = _position.getX(); paddleRect.y = _position.getY();
	paddleRect.w = _width; paddleRect.h = _heigth;

	paddleRectPointer = &paddleRect;

	SDL_Rect result;

	resultPointer = &result;

	if (SDL_IntersectRect(ballRect, paddleRectPointer, resultPointer))
	{
		if (!insidePaddle)
		{
			if (p2.getX() < paddle_p3.getX() && p3.getX() >= paddle_p3.getX())//antes de paddle_p0
			{
				if (resultPointer->w >= resultPointer->h)
				{
					collVector = Vector2D{ 0.5,-1}.normalize();
					collisionState = true;
				}
				else
				{
					collVector = Vector2D{ 1,0 }.normalize();
					collisionState = true;
				}
			}
			else if (p3.getX() <= paddle_p3.getX() && p2.getX() >= paddle_p0.getX()) //Entre paddle_p0 y paddle_p3
			{
				if (p2.getX() >= paddle_p2.getX())
				{
					collVector = Vector2D{ 0.5 ,-1 }.normalize();
					collisionState = true;
				}
				else if (p2.getX() < paddle_p2.getX() && p3.getX() >= paddle_p2.getX())
				{
					if ((p3.getX() - paddle_p2.getX()) > (paddle_p2.getX() - p2.getX()))
					{
						collVector = Vector2D{ 0.5 , -1 }.normalize();
						collisionState = true;
					}
					else
					{
						collVector = Vector2D{ 0,-1 }.normalize();
						collisionState = true;
					}
				}
				else if (p2.getX() >= paddle_p1.getX() && p3.getX() < paddle_p2.getX())
				{
					collVector = Vector2D{ 0,-1 }.normalize();
					collisionState = true;
				}
				else if (p2.getX() < paddle_p1.getX() && p3.getX() >= paddle_p1.getX())
				{
					if ((p3.getX() - paddle_p1.getX()) > (paddle_p1.getX() - p2.getX()))
					{
						collVector = Vector2D{ 0,-1 }.normalize();
						collisionState = true;
					}
					else
					{
						collVector = Vector2D{ -0.5 ,-1 }.normalize();
						collisionState = true;
					}
				}
				else
				{
					collVector = Vector2D{ -0.5 , -1 }.normalize();
					collisionState = true;
				}
			}
			else if (p2.getX() < paddle_p0.getX() && p3.getX() < paddle_p1.getX()) //despues de paddle_p3
			{
				if (resultPointer->w >= resultPointer->h)
				{
					collVector = Vector2D{ -0.5 , -1 }.normalize();
					collisionState = true;
				}
				else
				{
					collVector = Vector2D{ -1,0 }.normalize();
					collisionState = true;
				}
			}
			insidePaddle = true;

		}
	}
	else insidePaddle = false;

	return collisionState;
}

Paddle::~Paddle()
{
}
