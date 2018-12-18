#include "BlocksMap.h"
#include <fstream>

using namespace std;

BlocksMap::BlocksMap(int level, int windowWidth, int windowHeigth, Texture*& blockTexture, Vector2D& initialPoint)
{
	_position = initialPoint;
	_texture = blockTexture;

	_pxWindowWidth = windowWidth;
	_pxWindowHeigth = windowHeigth/3;

	loadLevel(level);

}

void BlocksMap::loadFromFile(ifstream& levelFile)
{
	loadMap(levelFile);
}

void BlocksMap::saveToFile(ofstream& file)
{
	file << _width << " ";
	file << _heigth << endl; 
	for (int i = 0; i < _heigth; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			if (map[i][j] == nullptr) file << 0;
			else file << map[i][j]->getColor();

			file << " ";

		}

		file << endl;
	}
}

void BlocksMap::loadMap(ifstream& stream)
{

	if (!stream.is_open()) throw "Error cargando el mapa.";
	else
	{
		stream >> _heigth;
		stream >> _width;
	}

	_pxCellWidth = ((_pxWindowWidth - (_position.getX() * 2))/ _width);
	_pxCellHeigth = (_pxWindowHeigth / _heigth);

	map = new Block**[_heigth];

	for (int i = 0; i < _heigth; i++)
	{
		map[i] = new Block*[_width];

		for (int j = 0; j < _width; j++)
		{
			int inputColor;

			stream >> inputColor;

			if (inputColor != 0)
			{
				int x = 0, y = 0;
				Vector2D blockPosition = Vector2D{ (double)(_position.getX() + 2 + _pxCellWidth * j), (double)(_position.getY() + _pxCellHeigth * i) };
				setColor(inputColor, x, y);
				map[i][j] = new Block(blockPosition, _pxCellWidth, _pxCellHeigth, _texture, y, x);
				map[i][j]->setColor(inputColor);
				map[i][j]->setRowCols(j,i);

				
			}
			else map[i][j] = nullptr;

		}

	}
}

void BlocksMap::loadLevel(int level)
{
	deleteMap();
	levelSS.str("");
	string number = "";
	if (level < 10)
	{
		number = "0";
		number += std::to_string(level);
	}
	else number += std::to_string(level);
	levelSS << "maps/level" << number << ".txt";

	ifstream input;
	input.open(levelSS.str());
	if (!input.is_open()) throw "Cant open file";
	else
	{
		loadMap(input);
	}

	input.close();
}

void BlocksMap::setColor(int color, int& imagePosX, int& imagePosY)
{
	switch (color)
	{
	default:
		break;

	case 1:
		imagePosX = 0;
		imagePosY = 0;
		break;
	case 2:
		imagePosX = 1;
		imagePosY = 0;
		break;
	case 3:
		imagePosX = 2;
		imagePosY = 0;
		break;
	case 4:
		imagePosX = 0;
		imagePosY = 1;
		break;
	case 5:
		imagePosX = 1;
		imagePosY = 1;
		break;
	case 6:
		imagePosX = 2;
		imagePosY = 2;
		break;
	}
}

void BlocksMap::render()
{
	for (int i = 0; i < _heigth; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			if (map[i][j] != nullptr)
			{
				map[i][j]->render();
			}
		}
	}
}

void BlocksMap::update() {}

void BlocksMap::handleEvent() {}


int BlocksMap::totalBlocks()
{
	int cont = 0;

	for (int i = 0; i < _heigth; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			if (map[i][j] != nullptr)
			{
				cont++;
			}
		}
	}

	return cont;
}

Block* BlocksMap::findBlock(Vector2D& v, SDL_Rect& ballRect)
{
	SDL_Rect* ballRectPointer = &ballRect;


	int x =  (int)trunc((v.getX() / _pxCellWidth));
	int y = (int)trunc((v.getY() / _pxCellHeigth));
	if ((x >= 0 && x < _width) && (y >= 0 && y < _heigth))
	{

		if (map[y][x] != nullptr)
		{
			SDL_Rect blockRect;
			blockRect.x = map[y][x]->getX(); blockRect.y = map[y][x]->getY();
			blockRect.w = map[y][x]->getW(); blockRect.h = map[y][x]->getH();

			SDL_Rect* blockRectPointer = &ballRect;

			if (SDL_HasIntersection(blockRectPointer, ballRectPointer))
			{
				return map[y][x];
			}
		}
	}
	
	return nullptr;
}

void BlocksMap::destroyBlock(Block* b)
{
	map[(int)b->getRowCols().getY()][(int)b->getRowCols().getX()]->setColor(0);
	map[(int)b->getRowCols().getY()][(int)b->getRowCols().getX()] = nullptr;
}

Block* BlocksMap::handleCollisions(SDL_Rect& ballRect, Vector2D& ballVel, Vector2D& collVector)
{
	Vector2D p0 = { (double)ballRect.x, (double)ballRect.y }; // top-left
	Vector2D p1 = { (double)(ballRect.x + ballRect.w), (double)ballRect.y }; // top-right
	Vector2D p2 = { (double)ballRect.x, (double)(ballRect.y + ballRect.h) }; // bottom-left
	Vector2D p3 = { (double)(ballRect.x + ballRect.w), (double)(ballRect.y + ballRect.h) }; // bottom-right
	Block* b = nullptr;
	if (ballVel.getX() < 0 && ballVel.getY() < 0) {
		if ((b = findBlock(p0, ballRect))) {
			if ((b->getY() + b->getH() - p0.getY()) <= (b->getX() + b->getW() - p0.getX()))
				collVector = { 0,1 }; // Borde inferior mas cerca de p0
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = findBlock(p1, ballRect))) {
			collVector = { 0,1 };
		}
		else if ((b = findBlock(p2, ballRect))) collVector = { 1,0 };
	}
	else if (ballVel.getX() >= 0 && ballVel.getY() < 0) {
		if ((b = findBlock(p1, ballRect))) {
			if (((b->getY() + b->getH() - p1.getY()) <= (p1.getX() - b->getX())) || ballVel.getX() == 0)
				collVector = { 0,1 }; // Borde inferior mas cerca de p1
			else
				collVector = { -1,0 }; // Borde izqdo mas cerca de p1
		}
		else if ((b = findBlock(p0, ballRect))) {
			collVector = { 0,1 };
		}
		else if ((b = findBlock(p3, ballRect))) collVector = { -1,0 };
	}
	else if (ballVel.getX() > 0 && ballVel.getY() > 0) {
		if ((b = findBlock(p3, ballRect))) {
			if (((p3.getY() - b->getY()) <= (p3.getX() - b->getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p3
			else
				collVector = { -1,0 }; // Borde dcho mas cerca de p3
		}
		else if ((b = findBlock(p2, ballRect))) {
			collVector = { 0,-1 };
		}
		else if ((b = findBlock(p1, ballRect))) collVector = { -1,0 };
	}
	else if (ballVel.getX() < 0 && ballVel.getY() > 0) {
		if ((b = findBlock(p2, ballRect))) {
			if (((p2.getY() - b->getY()) <= (b->getX() + b->getW() - p2.getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p2
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = findBlock(p3, ballRect))) {
			collVector = { 0,-1 };
		}
		else if ((b = findBlock(p0, ballRect))) collVector = { 1,0 };
	}
	return b;
}

void BlocksMap::deleteMap()
{
	for (int i = 0; i < _heigth; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			delete map[i][j];
			map[i][j] = nullptr;
		}

		delete map[i];
		map[i] = nullptr;
	}
}

BlocksMap::~BlocksMap()
{
	
	deleteMap();

	delete map;
	map = nullptr;

}
