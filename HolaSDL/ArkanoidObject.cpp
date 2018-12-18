#include "ArkanoidObject.h"



ArkanoidObject::ArkanoidObject()
{
	_position = Vector2D();
	_width = _heigth = 0;
	_texture = nullptr;
}

ArkanoidObject::ArkanoidObject(Vector2D& position, int width, int heigth, Texture* texture)
{
	_position = position;
	_width = width;
	_heigth = heigth;
	_texture = texture;

}

SDL_Rect ArkanoidObject::getRect()
{
	SDL_Rect newRect;
	newRect.x = _position.getX(); newRect.y = _position.getY();
	newRect.w = _width; newRect.h = _heigth;
	return newRect;
}
 
void ArkanoidObject::render()
{
	_texture->render( getRect(),SDL_FLIP_NONE);
}


ArkanoidObject::~ArkanoidObject()
{
}
