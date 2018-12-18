#pragma once
#include "Reward.h"
#include "checkML.h"

class Game;//forwarding declaration de la clase Game
class Paddle;//forwarding declaration de la clase Paddle

class Reward_TypeR : public Reward 
{
private:
	Game* _game;
	Paddle* _paddle;

public:
	Reward_TypeR(Vector2D& position, int width, int heigth, Texture* texture, Game* game, Paddle* paddle, int windowHeigth) :Reward(position, width, heigth, texture, windowHeigth), MovingObject(position, width, heigth, texture), ArkanoidObject(position, width, heigth, texture)
	{
		type = 'R';
		_rowImage = 4;
		_game = game;
		_paddle = paddle;
	};

	virtual void update();//heredada de Reward
	virtual void action();//heredada de Reward
	~Reward_TypeR();
};

