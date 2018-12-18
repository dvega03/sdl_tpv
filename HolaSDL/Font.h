#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "checkML.h"

class Font
{
private:
	TTF_Font* font = nullptr;
public:
	Font();
	Font(const char* filename, int size);

	bool load(const char* filename, int size);
	
	void clean();

	

	SDL_Surface* generateSurface(const char* text, SDL_Color color) const;

	~Font() { clean(); };

};

