#pragma once

#include "Block.h"
#include "ArkanoidObject.h"
#include <sstream>
#include "checkML.h"




class BlocksMap : public virtual ArkanoidObject
{

private:

	Block*** map;

	int _pxWindowWidth;
	int _pxWindowHeigth;

	int _pxCellWidth;
	int _pxCellHeigth;

	std::stringstream levelSS;
	
	

public:
	BlocksMap(int level, int windowWidth, int windowHeigth, Texture*& blockTexture, Vector2D& initialPoint);

	void virtual loadFromFile(ifstream& levelFile);

	void virtual saveToFile(ofstream& file);

	void loadMap(ifstream& stream);//carga un mapa a partir de un archivo

	void loadLevel(int level);//carga un mapa a partir de un nivel especificado

	void setColor(int color, int& imagePosX, int& imagePosY); //establece el color de un bloque sabiendo de que color es el bloque y devolviendo las filas y columnas en la imagen de bloques

	virtual void render();//heredada de ArkanoidObject

	virtual void update();//heredada de ArkanoidObject

	virtual void handleEvent();//heredada de ArkanoidObject

	int totalBlocks();//devuelve la cantidad de bloques totales

	Block* findBlock(Vector2D& v, SDL_Rect& ballRect);//devuelve un bloque sabiendo la posicion en la que se encuentra

	void destroyBlock(Block* b);//destruye un bloque 

	Block* handleCollisions(SDL_Rect& ballRect, Vector2D& ballVel, Vector2D& collVector);//maneja las colisiones de los bloques

	void deleteMap();//elimina el mapa

	~BlocksMap();
};

