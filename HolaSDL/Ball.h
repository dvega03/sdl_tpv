#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "MovingObject.h"
#include <fstream>



class Game;//forwarding declaration de la clase Game

class Ball : public MovingObject
{
private:

	Vector2D _posIni;
	Vector2D _dirIni;

	Game* _game;//puntero a game

public:

	Ball(Vector2D& position, int width, int heigth, Texture* texture, Game* game) :MovingObject(position, width, heigth, texture), ArkanoidObject(position,width,heigth,texture)
	{
		_width = _width / 6;
		_heigth = _heigth / 6;

		_direction = Vector2D{ 0,-1 };

		_game = game;

		_posIni = _position;
		_dirIni = _direction;
		
	};

	int getX() { return (int)_position.getX(); };
	int getY() { return (int)_position.getY(); };

	virtual void loadFromFile(ifstream& levelFile);
	virtual void saveToFile(ofstream& file);

	virtual void render();//heredada de ArkanoidObject
	virtual void update();//heredada de ArkanoidObject

	void setIni();//establece los valores iniciales

	~Ball();
};

