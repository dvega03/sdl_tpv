#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void render() = 0; //renderiza un GameObject a partir de su textura
	virtual void update() = 0; //actualiza la posicion de un objeto
	virtual void handleEvent() = 0;//maneja los eventos de un objeto
};

