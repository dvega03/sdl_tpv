#include "Reward_TypeR.h"
#include "Game.h"
#include "Paddle.h"


void Reward_TypeR::action()
{
	_game->lifes++;
	_paddle->setWidthIni();
}

void Reward_TypeR::update()
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

Reward_TypeR::~Reward_TypeR()
{
}
