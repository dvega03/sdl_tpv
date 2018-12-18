#include "Reward.h"


void Reward::loadFromFile(ifstream& levelFile)
{
}

void Reward::saveToFile(std::ofstream& file)
{
	file << type << " " << _position.getX() << " " << _position.getY() << " " << _width << " " << _heigth << endl;
}


void Reward::render()
{
	_texture->renderFrame(ArkanoidObject::getRect(), _rowImage, (frame % ANIM_FRAME));
	frame++;
}
 
void Reward::update()
{
	MovingObject::update();
}

Reward::~Reward()
{
}
