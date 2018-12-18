#include "Reward_TypeE.h"
#include "Game.h"
#include "Paddle.h"


void Reward_TypeE::action()
{
	_paddle->changeWidth(1.25);
}

void Reward_TypeE::update()
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

Reward_TypeE::~Reward_TypeE()
{
}
