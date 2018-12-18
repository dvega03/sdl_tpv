#pragma once
#include "ArkanoidObject.h"
#include "checkML.h"
#include <fstream>

class MovingObject: public virtual ArkanoidObject
{

protected:

	Vector2D _direction;


public:

	MovingObject();

	MovingObject(Vector2D& position, int width, int heigth, Texture* texture) :ArkanoidObject(position,width,heigth,texture) 
	{
		_direction = Vector2D(0, 0);
	};

	virtual void loadFromFile(ifstream& levelFile);
	virtual void saveToFile(std::ofstream& file);

	virtual void render();//heredada de ArkanoidObject
	virtual void update();//heredada de ArkanoidObject
	virtual void handleEvent();//heredada de ArkanoidObject

	virtual ~MovingObject();
};

