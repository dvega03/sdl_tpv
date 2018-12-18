#pragma once

#include "GameObject.h"
#include "Vector2D.h"
#include "checkML.h"


class ArkanoidObject : public virtual GameObject
{
protected:
	Vector2D _position;
	int _width;
	int _heigth;
	Texture* _texture;

public:
	ArkanoidObject();
	ArkanoidObject(Vector2D& position, int width, int heigth, Texture* texture);
	virtual void loadFromFile(ifstream& levelFile) = 0;//carga la informacion necesaria de un archivo
	virtual void saveToFile(std::ofstream& file) = 0;//guarda la informacion necesaria del objeto en un archivo
	virtual SDL_Rect getRect(); //obtiene el rectangulo que define este objeto
	virtual void render(); //heredada de GameObject
	virtual void update() = 0; //heredada de GameObject
	virtual void handleEvent() = 0; //heredada de GameObject
	virtual ~ArkanoidObject();
};

