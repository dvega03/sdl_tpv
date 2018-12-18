#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "MovingObject.h"
#include "checkML.h"
#include <list>
#include <fstream>

class Reward : public virtual MovingObject
{
protected:

	static const int ANIM_FRAME = 8;

	string type;

	int _rowImage;

	int _windowHeigth;

	int frame; 

public:
	Reward(Vector2D& position, int width, int heigth, Texture* texture, int windowHeigth) :MovingObject(position, width, heigth, texture), ArkanoidObject(position, width, heigth, texture)
	{

		_direction = Vector2D{ 0, 0.25 };

		_windowHeigth = windowHeigth;

		frame = 0;

	};


	virtual void loadFromFile(ifstream& levelFile);
	virtual void saveToFile(std::ofstream& file);

	virtual void render();//heredada de MovingObject
	virtual void update();//heredada de MovingObject

	virtual void action() = 0; //define que hace cada tipo de reward


	virtual ~Reward();
};

