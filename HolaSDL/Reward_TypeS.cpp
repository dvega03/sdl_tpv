#include "Reward_TypeS.h"
#include "Game.h"
#include "Paddle.h"


void Reward_TypeS::action()
{
	_paddle->changeWidth(0.75);
}

void Reward_TypeS::update()
{
	Reward::update();
	if (_position.getY() >= _windowHeigth)
	{
		_game->killObject(this);
	}

	if (SDL_HasIntersection(&ArkanoidObject::getRect(), &_paddle->getRect()))
	{
		action();
		_game->killObject(this);
	}
}

Reward_TypeS::~Reward_TypeS()
{
}
