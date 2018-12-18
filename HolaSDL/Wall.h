#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "ArkanoidObject.h"
#include "checkML.h"
#include <fstream>

class Wall : public virtual ArkanoidObject
{
private:

	//collisions
	SDL_Rect wallRect;
	const SDL_Rect* wallRectPointer;
	SDL_Rect* resultPunt;

public:

	Wall(Vector2D& position, int width, int heigth, Texture* texture) :ArkanoidObject(position, width, heigth, texture)
	{
		_width = _texture->getW();
		if (width != -1)
		{
			_width = width;
		}

		_heigth = _texture->getH();
		if (heigth != -1)
		{
			_heigth = heigth;
		}


		wallRect.x = _position.getX(); wallRect.y = _position.getY();
		wallRect.w = _width; wallRect.h = _heigth;
	
	};

	int getW() const { return _width; };
	int getH() const { return _heigth; };

	virtual void loadFromFile(ifstream& levelFile);
	virtual void saveToFile(ofstream& file);

	virtual void render(); //heredada de ArkanoidObject
	virtual void update();//heredada de ArkanoidObject
	virtual void handleEvent();//heredada de ArkanoidObject

	bool handleCollision(SDL_Rect*& ballRect, Vector2D& ballVel, Vector2D& collVector, int windowWidth); //maneja las colisiones de la Pared

	~Wall();
};

