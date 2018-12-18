#include "Reward_TypeL.h"
#include "Game.h"
#include "Paddle.h"




void Reward_TypeL::action()
{
	_game->manageLevel();
	_paddle->setWidthIni();
}

void Reward_TypeL::update()
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


Reward_TypeL::~Reward_TypeL()
{
}
