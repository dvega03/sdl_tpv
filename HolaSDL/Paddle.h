#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "MovingObject.h"
#include <fstream>

class Paddle :public MovingObject
{

private:

	int _iniWidth = _width;

	int _windowWidth;

	int _limits;

	SDL_Rect paddleRect;
	SDL_Rect* ballRectPointer;
	SDL_Rect* paddleRectPointer;
	SDL_Rect* resultPointer;

	bool insidePaddle;

	Vector2D _posIni;
	Vector2D _dirIni;


public:

	Paddle(Vector2D& position, int width, int heigth, Texture* texture, int windowWidth, int limits) :MovingObject(position, width, heigth, texture) , ArkanoidObject(position, width, heigth, texture)
	{
		
		_posIni = _position;
		_dirIni = _direction;

		_windowWidth = windowWidth;
		_limits = limits;
	};

	virtual void loadFromFile(ifstream& levelFile);
	virtual void saveToFile(ofstream& level);

	void setIni();// establece los valores iniciales
	void changeWidth(float amount);// cambia el ancho de la plataforma
	void setWidthIni() { _width = _iniWidth; }; //establece el ancho inicial
	void render();//heredada de MovinObject
	void update();//heredada de MovingObject
	void handleEvent(SDL_Event& event);//heredada de MovingObject
	bool handleCollisions(SDL_Rect* ballRect, Vector2D& ballVel, Vector2D& collVector, int windowWidth);//controla las colisiones del Paddle
	

	~Paddle();
};