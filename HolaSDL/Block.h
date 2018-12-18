#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "ArkanoidObject.h"
#include "checkML.h"
#include <fstream>



class Block : public virtual ArkanoidObject
{
private:

	int _color;

	int _row;
	int _column;

	int _rowImage;
	int _columnImage;

	


public:
	Block(Vector2D& position, int width, int heigth, Texture* texture, int rowImage, int columnImage) :ArkanoidObject(position, width, heigth, texture) 
	{
		_color = 0;

		_row = _column = 0;

		_rowImage = rowImage;
		_columnImage = columnImage;
	};

	void setColor(int color); //establece el color 
	void setRowCols(int row, int cols);//establece en que fila y columna esta el bloque


	int getX() const { return _position.getX(); };
	int getY() const { return _position.getY(); };
	int getW() const { return _width; };
	int getH() const { return _heigth; };
	int getColor() const { return _color; }; //obtiene el color
	Vector2D getRowCols() const { return Vector2D{(double)_row,(double)_column}; }; // obtiene la fila y clumna del bloque


	virtual void loadFromFile(ifstream& levelFile);
	virtual void saveToFile(std::ofstream& file);
	virtual void render(); //heredada de ArkanoidObject
	virtual void update();//heredada de ArkanoidObject
	virtual void handleEvent();//heredada de ArkanoidObject

	~Block();
};

