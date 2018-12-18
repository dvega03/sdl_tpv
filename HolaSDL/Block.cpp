#include "Block.h"


void Block::setColor(int color)
{
	_color = color;
}

void Block::setRowCols(int row, int cols)
{
	_row = row;
	_column = cols;
}

void Block::render()
{
	_texture->renderFrame(getRect(), _rowImage, _columnImage);
}

void Block::update() {}

void Block::handleEvent() {}

void Block::loadFromFile(ifstream& levelFile) {};

void Block::saveToFile(std::ofstream& file) {};



Block::~Block()
{
}
